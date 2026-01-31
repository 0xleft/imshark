#ifndef IMSHARK_PACKET_MANAGER_H
#define IMSHARK_PACKET_MANAGER_H
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "pcap/pcap.h"

namespace imshark::core::net
{
    class packet_manager
    {
        static packet_manager* instance;

        pcap_t* capture_handle = nullptr;
        std::thread capture_thread;

        std::string error_message;
        bool last_action_error = false;
        bool receiving = false;

        std::mutex packet_list_mtx;
        std::vector<const u_char*> captured_packet_list;

    public:
        static packet_manager* get_instance();
        /**
         * @return true it successfully initialized, false otherwise
         */
        [[nodiscard]] bool is_receiving() const;
        void start_receiving(const std::string& device);
        void stop_receiving();
        std::vector<std::string> get_possible_devices();
        std::string get_error_message();
        [[nodiscard]] bool is_last_action_error() const;
        void clear_error_message();
        std::string set_filter(std::string filter);
        std::vector<const u_char*> get_captured_packets();
        void clear_captured_packet_list();

        ~packet_manager()
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
