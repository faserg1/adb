#pragma once

#include <algorithm>
#include <type_traits>
#include <string>
#include <libadb/types/snowflake.hpp>

namespace adb::api
{
    template <typename ContainerType>
    concept Container = requires(ContainerType a, const ContainerType b)
    {
        { a.begin() } -> std::same_as<typename ContainerType::iterator>;
        { a.end() } -> std::same_as<typename ContainerType::iterator>;
        { b.begin() } -> std::same_as<typename ContainerType::const_iterator>;
        { b.end() } -> std::same_as<typename ContainerType::const_iterator>;
    };

    template <typename Type>
    concept Entity = requires(Type entity)
    {
        { entity.id } -> std::convertible_to<adb::types::SFID>;
    };

    template <typename Type>
    concept ObjectWithCustomId = requires(Type object)
    {
        { object.customId } -> std::convertible_to<std::string>;
    };

    template <typename Type>
    concept ObjectWithName = requires(Type object)
    {
        { object.name } -> std::convertible_to<std::string>;
    };

    // By Id

    template<template<class, class...> class ContainerType, class EntityType, class ...ContainerArgs>
    requires Container<ContainerType<EntityType, ContainerArgs...>> && Entity<EntityType>
    ContainerType<EntityType, ContainerArgs...>::iterator findIterByName(ContainerType<EntityType, ContainerArgs...> &container, const std::string &name)
    {
        return std::find_if(container.begin(), container.end(), [&name](const auto &entity)
        {
            return entity.name == name;
        });
    }

    template<template<class, class...> class ContainerType, class EntityType, class ...ContainerArgs>
    requires Container<ContainerType<EntityType, ContainerArgs...>> && Entity<EntityType>
    ContainerType<EntityType, ContainerArgs...>::const_iterator findIterByName(const ContainerType<EntityType, ContainerArgs...> &container, const std::string &name)
    {
        return std::find_if(container.begin(), container.end(), [&name](const auto &entity)
        {
            return entity.name == name;
        });
    }

    template<template<class, class...> class ContainerType, class EntityType, class ...ContainerArgs>
    requires Container<ContainerType<EntityType, ContainerArgs...>> && Entity<EntityType>
    EntityType *findByName(ContainerType<EntityType, ContainerArgs...> &container, const std::string &name)
    {
        auto result = findIterByName(container, name);
        if (result == container.end())
            return nullptr;
        return &(*result);
    }

    template<template<class, class...> class ContainerType, class EntityType, class ...ContainerArgs>
    requires Container<ContainerType<EntityType, ContainerArgs...>> && Entity<EntityType>
    EntityType *const findByName(const ContainerType<EntityType, ContainerArgs...> &container, const std::string &name)
    {
        auto result = findIterByName(container, name);
        if (result == container.end())
            return nullptr;
        return &(*result);
    }

    // By name

    template<template<class, class...> class ContainerType, class ObjectType, class ...ContainerArgs>
    requires Container<ContainerType<ObjectType, ContainerArgs...>> && ObjectWithName<ObjectType>
    ContainerType<ObjectType, ContainerArgs...>::iterator findIterByName(ContainerType<ObjectType, ContainerArgs...> &container, const std::string &name)
    {
        return std::find_if(container.begin(), container.end(), [&name](const auto &object)
        {
            return object.name == name;
        });
    }

    template<template<class, class...> class ContainerType, class ObjectType, class ...ContainerArgs>
    requires Container<ContainerType<ObjectType, ContainerArgs...>> && ObjectWithName<ObjectType>
    ContainerType<ObjectType, ContainerArgs...>::const_iterator findIterByName(const ContainerType<ObjectType, ContainerArgs...> &container, const std::string &name)
    {
        return std::find_if(container.begin(), container.end(), [&name](const auto &object)
        {
            return object.name == name;
        });
    }

    template<template<class, class...> class ContainerType, class ObjectType, class ...ContainerArgs>
    requires Container<ContainerType<ObjectType, ContainerArgs...>> && ObjectWithName<ObjectType>
    ObjectType *findByName(ContainerType<ObjectType, ContainerArgs...> &container, const std::string &name)
    {
        auto result = findIterByName(container, name);
        if (result == container.end())
            return nullptr;
        return &(*result);
    }

    template<template<class, class...> class ContainerType, class ObjectType, class ...ContainerArgs>
    requires Container<ContainerType<ObjectType, ContainerArgs...>> && ObjectWithName<ObjectType>
    ObjectType *const findByName(const ContainerType<ObjectType, ContainerArgs...> &container, const std::string &name)
    {
        auto result = findIterByName(container, name);
        if (result == container.end())
            return nullptr;
        return &(*result);
    }
}