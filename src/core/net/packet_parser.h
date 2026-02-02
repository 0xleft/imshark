#ifndef IMSHARK_PACKET_PARSER_H
#define IMSHARK_PACKET_PARSER_H

#include "packet.h"
#include <packet_configs.h>

namespace imshark::core::net
{
    class packet_parser
    {
        static packet_parser* instance;

    public:
        static packet_parser* get_instance();

        static packet parse_packet(const u_char* data, const configs::config& root_layer_config);
    };
}


#endif //IMSHARK_PACKET_PARSER_H