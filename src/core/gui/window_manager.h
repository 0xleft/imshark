#ifndef IMSHARK_WINDOW_MANAGER_H
#define IMSHARK_WINDOW_MANAGER_H

#include <algorithm>
#include <iostream>
#include <shared_mutex>
#include <vector>

#include "gui_state.h"
#include "main_filter_window.h"
#include "navbar.h"
#include "packet_send_popup.h"
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
        gui_state gui_state_ = CHOOSE_INTERFACES;

        std::shared_ptr<packet_send_popup> packet_send_popup_ = nullptr;
        std::shared_ptr<net::packet_receiver> packet_receiver_;

        std::atomic<bool> executing_main_action{false};
    public:
        static window_manager* get_instance();

        main_filter_window& get_main_filter_window();
        int set_selected_device(const std::string& device);
        std::shared_ptr<net::packet_receiver>& get_packet_receiver();
        gui_state& get_gui_state();
        void set_gui_state(gui_state new_state);
        void draw() override;

        template<typename F>
        void try_execute_main_action(F func);
    };

    template <typename F>
    void window_manager::try_execute_main_action(F func)
    {
        if (executing_main_action.load()) return;
        executing_main_action.store(true);

        std::thread t([this, func]()
        {
            func();

            executing_main_action.store(false);
        });

        t.detach();
    }
}

#endif //IMSHARK_WINDOW_MANAGER_H
