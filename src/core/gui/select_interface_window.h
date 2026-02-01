#ifndef IMSHARK_SELECT_INTERFACE_H
#define IMSHARK_SELECT_INTERFACE_H

#include <string>
#include <vector>

#include "drawable.h"
#include "../net/packet_receiver.h"

namespace imshark::core::gui
{
    class select_interface_window : public drawable
    {
        std::vector<std::string> devices;

    public:
        select_interface_window()
        {
            auto packet_receiver = net::packet_receiver{};
            packet_receiver.get_possible_devices(devices);
        }

        void draw() override;
    };
}

#endif //IMSHARK_SELECT_INTERFACE_H
