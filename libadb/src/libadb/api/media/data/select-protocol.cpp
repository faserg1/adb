#include <libadb/api/media/data/select-protocol.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const SelectProtocol& selectProtocol)
{
    j = nlohmann::json
    {
        {"protocol", selectProtocol.protocol},
        {"data",
            {
                {"address", selectProtocol.data.address},
                {"port", selectProtocol.data.port},
                {"mode", selectProtocol.data.mode},
            }
        }
    };
}

void adb::api::from_json(const nlohmann::json& j, SelectProtocol& selectProtocol)
{
    j.at("protocol").get_to(selectProtocol.protocol);
    j.at("data").at("address").get_to(selectProtocol.data.address);
    j.at("data").at("port").get_to(selectProtocol.data.port);
    j.at("data").at("mode").get_to(selectProtocol.data.mode);
}