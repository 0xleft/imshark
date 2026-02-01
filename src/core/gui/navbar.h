#ifndef IMSHARK_NAVBAR_H
#define IMSHARK_NAVBAR_H

#include <vector>

#include "drawable.h"

namespace imshark::configs
{
    std::vector<
}

namespace imshark::core::gui
{
    class navbar : public drawable
    {
    public:
        void draw() override;
    };
}

#endif //IMSHARK_NAVBAR_H
