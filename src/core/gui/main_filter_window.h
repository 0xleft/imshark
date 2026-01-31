#ifndef IMSHARK_MAIN_FILTER_H
#define IMSHARK_MAIN_FILTER_H
#include "drawable.h"

namespace imshark::core::gui
{
    class main_filter_window : public drawable
    {
    public:
        void draw() override;
    };
}

#endif //IMSHARK_MAIN_FILTER_H
