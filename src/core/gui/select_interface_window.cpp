#include "select_interface_window.h"

#include "imgui.h"
#include "window_manager.h"

namespace imshark::core::gui
{
    void select_interface_window::draw()
    {
        if (ImGui::BeginListBox("Select interface")) {
            for (const auto& device : this->devices) {
                assert(!device.empty());
                if (ImGui::Selectable(device.c_str())) {
                    window_manager::get_instance()->get_selected_devices().clear();
                    window_manager::get_instance()->get_selected_devices().push_back(device);
                    window_manager::get_instance()->set_gui_state(MAIN_FILTER);
                }
            }
            ImGui::EndListBox();
        }
    }
}
