#include "main_filter_window.h"

#include "imgui.h"
#include "window_manager.h"

namespace imshark::core::gui
{
    void main_filter_window::draw()
    {
        static char filter_str[1024] = "";
        ImGui::InputText("Filter", filter_str, IM_ARRAYSIZE(filter_str));

        const ImVec2 avail = ImGui::GetContentRegionAvail();
        ImGui::BeginChild("packet_display", ImVec2(avail.x * 0.6f, avail.y), true);

        if (auto packet_receiver = window_manager::get_instance()->get_packet_receiver())
        {
            for (auto& p : window_manager::get_instance()->get_packet_receiver()->get_captured_packets())
            {
                ImGui::Text("packet");
            }
        }

        ImGui::EndChild();

        ImGui::SameLine();

        ImGui::BeginChild("packet_dissect", ImVec2(avail.x * 0.4f, avail.y), true);



        ImGui::EndChild();
    }
}
