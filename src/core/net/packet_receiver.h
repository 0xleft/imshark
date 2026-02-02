#ifndef IMSHARK_PACKET_MANAGER_H
#define IMSHARK_PACKET_MANAGER_H
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "packet.h"
#include "packet_configs.h"
#include "pcap/pcap.h"

namespace imshark::core::net
{
    class packet_receiver
    {
        pcap_t* capture_handle = nullptr;
        std::thread capture_thread;

        std::string error_message;
        bool receiving = false;

        std::mutex packet_list_mtx;
        std::string current_device;
        std::vector<packet> captured_packet_list;

        std::vector<packet> filtered_packet_list;
        std::string filter_str;
    public:
        /**
         * @return true it successfully initialized, false otherwise
         */
        [[nodiscard]] bool is_receiving() const;
        int start_receiving(const std::string& device, const configs::config& root_layer_config);
        int stop_receiving();
        int get_possible_devices(std::vector<std::string>& devices);
        std::string get_error_message();
        void clear_error_message();
        void set_filter(const std::string& filter);
        bool does_fit_filter(packet& packet);
        void filter_packets();
        std::vector<packet>& get_captured_packets();
        std::vector<packet>& get_filtered_packets();
        void clear_captured_packet_list();
        std::string get_current_device();

        ~packet_receiver()
        {
            if (!capture_handle)
            {
                return;
            }

            pcap_close(capture_handle);
        }
    };
}

#endif //IMSHARK_PACKET_MANAGER_H
