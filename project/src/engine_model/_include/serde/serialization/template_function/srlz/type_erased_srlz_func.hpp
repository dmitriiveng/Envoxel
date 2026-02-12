#pragma once

#include "serde/type_erasure/VoidPtrAny.hpp"

#include <functional>

namespace serde::srlz {
    template <typename OutputV>
    using type_erased_srlz_func = std::function<OutputV(const void*)>;
}