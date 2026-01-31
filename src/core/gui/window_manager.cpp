#include "window_manager.h"

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

    std::vector<std::shared_ptr<net::packet_receiver>>& window_manager::get_packet_receivers()
    {
        return this->packet_receivers_;
    }

    gui_state& window_manager::get_gui_state()
    {
        return this->gui_state_;
    }

    void window_manager::draw()
    {
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("Main", nullptr,
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDecoration);

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

        for (auto& popup : this->packet_detail_popups_)
        {
            popup.draw();
        }

        ImGui::Text("Draw");

        ImGui::End();
    }
}
