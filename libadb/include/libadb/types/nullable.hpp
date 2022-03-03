#pragma once

#include <memory>

namespace adb::types
{
    template <class Type>
    using Nullable = std::shared_ptr<Type>;
}
