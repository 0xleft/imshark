#ifndef IMSHARK_PACKET_H
#define IMSHARK_PACKET_H
#include <string>
#include <unordered_map>

namespace imshark::core::net
{
    struct packet
    {
        std::unordered_map<std::string, const u_char*> structured_data;
        std::string top_protocol;
        std::string src;
        std::string dst;
    };
}

#endif //IMSHARK_PACKET_H
