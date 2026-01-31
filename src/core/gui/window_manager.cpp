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

    void window_manager::draw()
    {
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("Main", nullptr,
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDecoration);

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Open base")) {}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("View")) {
                if (ImGui::MenuItem("Draw")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::Text("Draw");

        ImGui::End();
    }
}
