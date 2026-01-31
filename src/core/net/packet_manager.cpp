#include "packet_manager.h"

#include <iostream>

namespace imshark::core::net
{
    packet_manager* packet_manager::instance = nullptr;

    packet_manager* packet_manager::get_instance()
    {
        if (instance == nullptr)
        {
            instance = new packet_manager{};
        }
        return instance;
    }

    bool packet_manager::is_receiving() const
    {
        return this->receiving;
    }

    void packet_manager::start_receiving(const std::string& device)
    {
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
            this->last_action_error = true;
            return;
        }

        this->receiving = true;
        this->capture_thread = std::thread([this]()
        {
            while (receiving)
            {
                pcap_pkthdr header{};
                const u_char* packet = pcap_next(this->capture_handle, &header);
                this->packet_list_mtx.lock();
                this->captured_packet_list.push_back(packet);
                this->packet_list_mtx.unlock();
            }
        });
    }

    void packet_manager::stop_receiving()
    {
        if (!receiving)
        {
            return;
        }

        this->receiving = false;
        this->capture_thread.join();
    }

    std::vector<std::string> packet_manager::get_possible_devices()
    {
        char error_buf[PCAP_ERRBUF_SIZE];
        pcap_if_t* device_ptr;
        auto devices_names = std::vector<std::string>();

        if (pcap_findalldevs(&device_ptr, error_buf) == -1) {
            std::cout << "failed to look up all devices: " << error_buf << std::endl;
            this->error_message = error_buf;
            this->last_action_error = true;
            return devices_names;
        }

        while (device_ptr != nullptr)
        {
            devices_names.emplace_back(device_ptr->name);
            device_ptr = device_ptr->next;
        }

        return devices_names;
    }

    std::string packet_manager::get_error_message()
    {
        return this->error_message;
    }

    bool packet_manager::is_last_action_error() const
    {
        return this->last_action_error;
    }

    void packet_manager::clear_error_message()
    {
        this->error_message = "";
        this->last_action_error = false;
    }

    void packet_manager::set_filter(const std::string& filter)
    {
        if (!capture_handle)
        {
            this->error_message = "You are not capturing packets";
            this->last_action_error = true;
            return;
        }

        bpf_program fp{};

        if (pcap_compile(capture_handle, &fp, filter.c_str(), 0, PCAP_NETMASK_UNKNOWN) == -1) // todo
        {
            this->error_message = "Couldn't compile filter: " + std::string(pcap_geterr(capture_handle));
            this->last_action_error = true;
            return;
        }

        if (pcap_setfilter(capture_handle, &fp) == -1)
        {
            this->error_message = "Couldn't apply filter: " + std::string(pcap_geterr(capture_handle));
            this->last_action_error = true;
        }
    }

    std::vector<const u_char*> packet_manager::get_captured_packets()
    {
        return this->captured_packet_list;
    }

    void packet_manager::clear_captured_packet_list()
    {
        this->packet_list_mtx.lock();
        this->captured_packet_list.clear();
        this->packet_list_mtx.unlock();
    }
}
