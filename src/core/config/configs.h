#ifndef IMSHARK_CONFIGS_H
#define IMSHARK_CONFIGS_H
#include <string>
#include <vector>

namespace imshark::core::config
{
    enum link_layer_config
    {
        ETH,
        BEACON
    };

    enum network_layer_config
    {
        IP
    };

    enum transport_layer_config
    {
        TCP,
        UDP
    };
}

#endif //IMSHARK_CONFIGS_H
