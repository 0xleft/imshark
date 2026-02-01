#include "main_filter_window.h"

#include "imgui.h"
#include "window_manager.h"

namespace imshark::core::gui
{
    void main_filter_window::draw()
    {
        net::packet selected_packet;

        static char filter_str[1024] = "";
        ImGui::InputText("Filter", filter_str, IM_ARRAYSIZE(filter_str));

        const ImVec2 avail = ImGui::GetContentRegionAvail();
        ImGui::BeginChild("packet_display", ImVec2(avail.x * 0.6f, avail.y), true);

        if (auto packet_receiver = window_manager::get_instance()->get_packet_receiver())
        {
            packet_receiver->set_filter(filter_str);

            if (ImGui::BeginTable("packet_table", 4,
                                  ImGuiTableFlags_ScrollY | ImGuiTableFlags_Resizable |
                                  ImGuiTableFlags_NoBordersInBodyUntilResize))
            {
                ImGui::TableSetupColumn("Source");
                ImGui::TableSetupColumn("Destination");
                ImGui::TableSetupColumn("Top protocol");
                ImGui::TableSetupColumn("Actions");
                ImGui::TableHeadersRow();

                auto filtered_packets = window_manager::get_instance()->get_packet_receiver()->get_filtered_packets();

                for (int i = 0; i < filtered_packets.size(); ++i)
                {
                    const auto& p = filtered_packets[i];

                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text("%s", p.src.c_str());
                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("%s", p.dst.c_str());
                    ImGui::TableSetColumnIndex(2);
                    ImGui::Text("%s", p.top_protocol.c_str());
                    ImGui::TableSetColumnIndex(3);

                    ImGui::PushID(std::to_string(i).c_str());
                    if (ImGui::Button("View"))
                    {
                        selected_packet = p;
                    }
                    ImGui::PopID();
                }

                ImGui::EndTable();
            }
        }

        ImGui::EndChild();

        ImGui::SameLine();

        ImGui::BeginChild("packet_dissect", ImVec2(avail.x * 0.4f, avail.y), true);


        ImGui::EndChild();
    }
}
