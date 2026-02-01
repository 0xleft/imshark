#include "select_interface_window.h"

#include <iostream>

#include "imgui.h"
#include "window_manager.h"

namespace imshark::core::gui
{
    void select_interface_window::draw()
    {
        auto action_errored = false;

        if (ImGui::BeginListBox("select_interface"))
        {
            for (const auto& device : this->devices)
            {
                assert(!device.empty());
                if (ImGui::Selectable(device.c_str()))
                {
                    if (window_manager::get_instance()->set_selected_device(device) != -1)
                    {
                        window_manager::get_instance()->set_gui_state(MAIN_FILTER);
                    }
                    else
                    {
                        action_errored = true;
                    }
                }
            }
            ImGui::EndListBox();
        }

        if (ImGui::BeginPopupModal("Error occurred", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::TextColored(ImColor::HSV(356, 85, 93), "%s",
                               window_manager::get_instance()->get_packet_receiver()->get_error_message().c_str());
            if (ImGui::Button("Close"))
            {
                action_errored = false;
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        if (action_errored)
        {
            ImGui::OpenPopup("Error occurred");
        }
    }
}
