#include "window_manager.h"

#include "imgui.h"
#include "../net/packet_manager.h"

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
        ImGui::Begin("Diff viewer");
        ImGui::Text("Diff viewer");

        ImGui::End();
    }
}
