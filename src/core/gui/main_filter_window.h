#ifndef IMSHARK_MAIN_FILTER_H
#define IMSHARK_MAIN_FILTER_H

#include "drawable.h"
#include "../config/configs.h"
#include "../net/packet_receiver.h"

namespace imshark::core::gui
{
    class main_filter_window : public drawable
    {
        std::shared_ptr<net::packet> selected_packet = nullptr;
        config::link_layer_config selected_link_layer_config_;

    public:
        main_filter_window()
        {
            selected_link_layer_config_ = config::ETH;
        }

        [[nodiscard]] config::link_layer_config get_selected_link_layer_config() const;
        void draw() override;
    };
}

#endif //IMSHARK_MAIN_FILTER_H
