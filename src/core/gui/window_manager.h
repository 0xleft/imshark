#ifndef IMSHARK_WINDOW_MANAGER_H
#define IMSHARK_WINDOW_MANAGER_H

#include <vector>

#include "gui_state.h"
#include "main_filter_window.h"
#include "navbar.h"
#include "packet_detail_popup.h"
#include "select_interface_window.h"
#include "../net/packet_receiver.h"

namespace imshark::core::gui
{
    class window_manager : public drawable
    {
        static window_manager* instance;

        navbar navbar_;
        select_interface_window select_interface_window_;
        main_filter_window main_filter_window_;
        std::vector<packet_detail_popup> packet_detail_popups_;
        gui_state gui_state_ = CHOOSE_INTERFACES;

        std::vector<std::shared_ptr<net::packet_receiver>> packet_receivers_;
    public:
        static window_manager* get_instance();

        std::vector<std::shared_ptr<net::packet_receiver>>& get_packet_receivers();
        gui_state& get_gui_state();
        void draw() override;
    };
}

#endif //IMSHARK_WINDOW_MANAGER_H
