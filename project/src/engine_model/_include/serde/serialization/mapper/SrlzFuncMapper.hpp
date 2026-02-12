#pragma once

#include <string>
#include <stdexcept>

#include "serde/mapper/SerDeFuncMapper.hpp"
#include "serde/serialization/template_function/srlz/type_erased_srlz_func.hpp"

namespace serde::srlz {
    template <typename OutputV, typename Key>
    using SrlzFuncMapper = SerDeFuncMapper<type_erased_srlz_func<OutputV>, Key>;
}