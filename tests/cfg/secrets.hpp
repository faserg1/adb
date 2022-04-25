#pragma once

#include <string>
#include <libadb/types/snowflake.hpp>
#include <libadb/cfg/secrets.hpp>


class Secrets final
{
public:
    Secrets() = delete;

    static const adb::cfg::SecretsData &getSecrets()
    {
        return data_;
    }
private:
    static adb::cfg::SecretsData data_;
};