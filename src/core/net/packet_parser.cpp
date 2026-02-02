#include "packet_parser.h"

#include "../config/configs.h"

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

    packet packet_parser::parse_packet(const u_char* data, const config::link_layer_config link_layer_config)
    {
        auto parsed_packet = packet{
            {}, "tcp", "0.0.0.0", "0.0.0.0"
        };

        return parsed_packet;
    }
}
