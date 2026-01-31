#ifndef IMSHARK_SELECT_INTERFACE_H
#define IMSHARK_SELECT_INTERFACE_H

#include "drawable.h"

namespace imshark::core::gui
{
    class select_interface_window : public drawable
    {
    public:
        void draw() override;
    };
}

#endif //IMSHARK_SELECT_INTERFACE_H
