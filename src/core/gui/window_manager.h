#ifndef IMSHARK_WINDOW_MANAGER_H
#define IMSHARK_WINDOW_MANAGER_H
#include "../net/packet_receiver.h"

namespace imshark::core::gui
{
    class window_manager
    {
        static window_manager* instance;

    public:
        static window_manager* get_instance();
        void draw();
    };
}

#endif //IMSHARK_WINDOW_MANAGER_H
