#pragma once

#include "serde/deserialization/template_function/dsrlz/type_erased_dsrlz_func.hpp"
#include "serde/mapper/ISerDeFuncMapper.hpp"

namespace serde::dsrlz {
    template <typename InputV, typename Key>
    using IDsrlzFuncMapper = ISerDeFuncMapper<type_erased_dsrlz_func<InputV>, Key>;
}