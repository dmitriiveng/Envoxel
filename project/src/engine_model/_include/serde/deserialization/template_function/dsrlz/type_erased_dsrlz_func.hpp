#pragma once

#include "serde/type_erasure/VoidPtrAny.hpp"

#include <functional>

namespace serde::dsrlz {
    template <typename InputV>
    using type_erased_dsrlz_func = std::function<VoidPtrAny(const InputV&)>;
}