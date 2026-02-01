#ifndef IMSHARK_MAIN_FILTER_H
#define IMSHARK_MAIN_FILTER_H

#include "drawable.h"
#include "../net/packet_receiver.h"

namespace imshark::core::gui
{
    class main_filter_window : public drawable
    {
        net::packet* selected_packet = nullptr;

    public:
        void draw() override;
    };
}

#endif //IMSHARK_MAIN_FILTER_H
