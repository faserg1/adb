#include <libadb/api/utils/fill-reason.hpp>

void adb::api::fillReason(cpr::Header &header, std::optional<std::string> reason)
{
    if (reason.has_value())
        header.insert({"X-Audit-Log-Reason", reason.value()});
}