#include "packet_parser.h"

namespace imshark::core::net
{
    packet_parser* packet_parser::instance = nullptr;

    packet_parser* packet_parser::get_instance()
    {
        if (instance == nullptr)
        {
            instance = new packet_parser{};
        }
        return instance;
    }
}