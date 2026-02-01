#ifndef IMSHARK_PACKET_PARSER_H
#define IMSHARK_PACKET_PARSER_H

#include "packet.h"

namespace imshark::core::net
{
    class packet_parser
    {
        static packet_parser* instance;

    public:
        static packet_parser* get_instance();
        void load_configs();
        void load_configs(std::string path);

        packet parse_packet(const u_char* data);
    };
}


#endif //IMSHARK_PACKET_PARSER_H