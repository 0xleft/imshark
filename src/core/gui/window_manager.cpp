#include "window_manager.h"

#include <iostream>

#include "imgui.h"

namespace imshark::core::gui
{
    window_manager* window_manager::instance = nullptr;

    window_manager* window_manager::get_instance()
    {
        if (instance == nullptr)
        {
            instance = new window_manager();
        }

        return instance;
    }

    main_filter_window& window_manager::get_main_filter_window()
    {
        return this->main_filter_window_;
    }

    int window_manager::set_selected_device(const std::string& device)
    {
        const auto new_receiver = std::make_shared<net::packet_receiver>();
        this->packet_receiver_ = new_receiver;
        if (new_receiver->start_receiving(device, main_filter_window_.get_selected_link_layer_config()) == -1)
        {
            return -1;
        }

        return 0;
    }

    std::shared_ptr<net::packet_receiver>& window_manager::get_packet_receiver()
    {
        return this->packet_receiver_;
    }

    gui_state& window_manager::get_gui_state()
    {
        return this->gui_state_;
    }

    void window_manager::set_gui_state(const gui_state new_state)
    {
        this->gui_state_ = new_state;
    }

    void window_manager::draw()
    {
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("main", nullptr,
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDecoration);

        if (executing_main_action.load())
        {
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            ImGui::ProgressBar(-1.0f * static_cast<float>(ImGui::GetTime()), ImVec2(0.0f, 0.0f), "Executing...");
        }

        this->navbar_.draw();

        switch (gui_state_)
        {
        case MAIN_FILTER:
            this->main_filter_window_.draw();
            break;
        case CHOOSE_INTERFACES:
            this->select_interface_window_.draw();
            break;
        }

        if (packet_send_popup_)
        {
            packet_send_popup_->draw();
        }

        ImGui::End();
    }
}
