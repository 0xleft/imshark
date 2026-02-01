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

    void packet_parser::load_configs()
    {
    }

    void packet_parser::load_configs(std::string path)
    {
    }

    packet packet_parser::parse_packet(const u_char* data)
    {
        auto parsed_packet = packet{};

        return parsed_packet;
    }
}
