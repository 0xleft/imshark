#include "navbar.h"

#include <cstdlib>

#include "imgui.h"

namespace imshark::core::gui
{
    void navbar::draw()
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Close"))
                {
                    exit(0);
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
    }
}
