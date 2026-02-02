#ifndef IMSHARK_PACKET_SEND_POPUP_H
#define IMSHARK_PACKET_SEND_POPUP_H
#include "drawable.h"

namespace imshark::core::gui
{
    class packet_send_popup : public drawable
    {
    public:
        void draw() override;
    };
}

#endif //IMSHARK_PACKET_SEND_POPUP_H
