#ifndef IMSHARK_PACKET_PARSER_H
#define IMSHARK_PACKET_PARSER_H


namespace imshark::core::net
{
    class packet_parser
    {
        static packet_parser* instance;

    public:
        static packet_parser* get_instance();
    };
}


#endif //IMSHARK_PACKET_PARSER_H