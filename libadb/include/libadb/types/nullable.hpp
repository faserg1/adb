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
        Nullable(const Nullable<Type> &old)
        {
            value_ = old.value_;
        }
        Nullable(Nullable<Type> &&old)
        {
            value_ = std::move(old.value_);
        }
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
        Nullable *operator=(const Nullable<Type> other)
        {
            value_ = other.value_;
            return this;
        }
    private:
        std::shared_ptr<Type> value_;
    };
}
