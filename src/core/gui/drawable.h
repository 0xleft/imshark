#ifndef IMSHARK_DRAWABLE_H
#define IMSHARK_DRAWABLE_H

namespace imshark::core::gui
{
    class drawable
    {
    public:
        virtual ~drawable() = default;
        virtual void draw() = 0;
    };
}

#endif //IMSHARK_DRAWABLE_H
