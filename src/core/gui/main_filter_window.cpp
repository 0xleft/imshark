#include "main_filter_window.h"

#include "imgui.h"
#include "window_manager.h"

namespace imshark::core::gui
{
    config::link_layer_config main_filter_window::get_selected_link_layer_config() const
    {
        return this->selected_link_layer_config_;
    }

    void main_filter_window::draw()
    {
        static char filter_str[1024] = "";
        ImGui::InputText("Filter", filter_str, IM_ARRAYSIZE(filter_str));

        const ImVec2 avail = ImGui::GetContentRegionAvail();
        ImGui::BeginChild("packet_display", ImVec2(avail.x * 0.6f, avail.y), true);

        if (const auto packet_receiver = window_manager::get_instance()->get_packet_receiver())
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
                    auto p = filtered_packets[i];

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
                        selected_packet = std::make_shared<net::packet>(p);
                    }

                    ImGui::PopID();
                }

                ImGui::EndTable();
            }
        }

        ImGui::EndChild();

        ImGui::SameLine();

        ImGui::BeginChild("packet_dissect", ImVec2(avail.x * 0.4f, avail.y), true);

        if (!selected_packet)
        {
            ImGui::Text("Select a packet to view and its details will be displayed here");
        }
        else
        {
            ImGui::Text("Source: %s", selected_packet->src.c_str());
            ImGui::Text("Destination: %s", selected_packet->dst.c_str());
            ImGui::Text("Top protocol: %s", selected_packet->top_protocol.c_str());

            // todo display raw hex data

            for (const auto& feature : selected_packet->structured_data)
            {
                // todo
            }
        }

        ImGui::EndChild();
    }
}
