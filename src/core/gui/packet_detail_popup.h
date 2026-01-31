#ifndef IMSHARK_PACKET_DETAIL_H
#define IMSHARK_PACKET_DETAIL_H
#include "drawable.h"

namespace imshark::core::gui
{
    class packet_detail_popup : public drawable
    {
    public:
        void draw() override;
    };
}

#endif //IMSHARK_PACKET_DETAIL_H
