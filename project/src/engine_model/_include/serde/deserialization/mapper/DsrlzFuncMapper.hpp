#pragma once

#include <string>
#include <stdexcept>

#include "serde/mapper/SerDeFuncMapper.hpp"
#include "serde/deserialization/template_function/dsrlz/type_erased_dsrlz_func.hpp"

namespace serde::dsrlz {
    template <typename InputV, typename Key>
    using DsrlzFuncMapper = SerDeFuncMapper<type_erased_dsrlz_func<InputV>, Key>;
}