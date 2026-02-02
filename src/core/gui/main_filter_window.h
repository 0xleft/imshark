#ifndef IMSHARK_MAIN_FILTER_H
#define IMSHARK_MAIN_FILTER_H

#include "drawable.h"
#include "packet_configs.h"
#include "../net/packet_receiver.h"

namespace imshark::core::gui
{
    class main_filter_window : public drawable
    {
        std::shared_ptr<net::packet> selected_packet = nullptr;
        configs::config selected_root_config;

    public:
        main_filter_window()
        {
            selected_root_config = configs::ROOT_PACKET_CONFIGS[0];
        }

        const configs::config& get_selected_root_config();
        void draw() override;
    };
}

#endif //IMSHARK_MAIN_FILTER_H
