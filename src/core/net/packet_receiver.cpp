#include "packet_receiver.h"

#include <iostream>

#include "packet_parser.h"

namespace imshark::core::net
{
    bool packet_receiver::is_receiving() const
    {
        return this->receiving;
    }

    int packet_receiver::start_receiving(const std::string& device)
    {
        clear_error_message();
        char error_buf[PCAP_ERRBUF_SIZE];

        if (capture_handle)
        {
            pcap_close(capture_handle);
        }

        capture_handle = pcap_open_live(device.c_str(), BUFSIZ, 1, 1000, error_buf);
        if (capture_handle == nullptr)
        {
            std::cout << "failed to initialize handle: " << error_buf << std::endl;
            this->error_message = error_buf;
            return -1;
        }

        this->receiving = true;
        this->current_device = device;
        this->capture_thread = std::thread([this]()
        {
            while (receiving)
            {
                pcap_pkthdr header{};
                const u_char* data = pcap_next(this->capture_handle, &header);
                if (receiving)
                {
                    this->packet_list_mtx.lock();
                    this->captured_packet_list.push_back(packet_parser::get_instance()->parse_packet(data));
                    this->packet_list_mtx.unlock();
                }
            }
        });

        return 0;
    }

    int packet_receiver::stop_receiving()
    {
        clear_error_message();
        if (!receiving)
        {
            error_message = "You are not receiving";
            return -1;
        }

        this->receiving = false;
        this->capture_thread.join();

        return 0;
    }

    int packet_receiver::get_possible_devices(std::vector<std::string>& devices)
    {
        clear_error_message();
        char error_buf[PCAP_ERRBUF_SIZE];
        pcap_if_t* device_ptr;

        if (pcap_findalldevs(&device_ptr, error_buf) == -1)
        {
            std::cout << "failed to look up all devices: " << error_buf << std::endl;
            this->error_message = error_buf;
            return -1;
        }

        while (device_ptr != nullptr)
        {
            devices.emplace_back(device_ptr->name);
            device_ptr = device_ptr->next;
        }

        return 0;
    }

    std::string packet_receiver::get_error_message()
    {
        return this->error_message;
    }

    void packet_receiver::clear_error_message()
    {
        this->error_message = "";
    }

    int packet_receiver::set_filter(const std::string& filter)
    {
        clear_error_message();

        if (!capture_handle)
        {
            this->error_message = "You are not capturing packets";
            return -1;
        }

        bpf_program fp{};

        if (pcap_compile(capture_handle, &fp, filter.c_str(), 0, PCAP_NETMASK_UNKNOWN) == -1) // todo
        {
            this->error_message = "Couldn't compile filter: " + std::string(pcap_geterr(capture_handle));
            return -1;
        }

        if (pcap_setfilter(capture_handle, &fp) == -1)
        {
            this->error_message = "Couldn't apply filter: " + std::string(pcap_geterr(capture_handle));
        }

        return 0;
    }

    std::vector<packet>& packet_receiver::get_captured_packets()
    {
        return this->captured_packet_list;
    }

    void packet_receiver::clear_captured_packet_list()
    {
        this->packet_list_mtx.lock();
        this->captured_packet_list.clear();
        this->packet_list_mtx.unlock();
    }

    std::string packet_receiver::get_current_device()
    {
        return this->current_device;
    }
}
