#pragma once

#include <memory>

namespace adb::types
{
    template <class Type>
    class Nullable
    {
    public:
        Nullable() = default;
        Nullable(std::nullptr_t) {}
        Nullable(Type value) : value_(std::make_shared<Type>(value))
        {
            
        }
        operator bool() const
        {
            return (bool) value_;
        }
        Type &operator*() const
        {
            return *value_;
        }
        Type *operator->() const
        {
            return &*value_;
        }
    private:
        std::shared_ptr<Type> value_;
    };
}
