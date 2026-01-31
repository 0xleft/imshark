#include "navbar.h"
#include "imgui.h"

namespace imshark::core::gui
{
    void navbar::draw()
    {
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
    }
}
