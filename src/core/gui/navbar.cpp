#include "navbar.h"

#include <cstdlib>

#include "imgui.h"
#include "window_manager.h"

namespace imshark::core::gui
{
    void navbar::draw()
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Capture"))
            {
                const auto packet_receiver = window_manager::get_instance()->get_packet_receiver();

                if (ImGui::MenuItem("Restart"))
                {
                    if (packet_receiver && window_manager::get_instance()->get_gui_state() == MAIN_FILTER)
                    {
                        packet_receiver->stop_receiving();
                        packet_receiver->start_receiving(packet_receiver->get_current_device(),
                                                         window_manager::get_instance()->get_main_filter_window().
                                                         get_selected_root_config());
                        packet_receiver->clear_captured_packet_list();
                    }
                }

                if (ImGui::MenuItem("Close"))
                {
                    if (packet_receiver)
                    {
                        packet_receiver->stop_receiving();
                    }
                    window_manager::get_instance()->set_gui_state(CHOOSE_INTERFACES);
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
    }
}
