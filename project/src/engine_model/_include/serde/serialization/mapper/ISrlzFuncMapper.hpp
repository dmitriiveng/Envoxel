#pragma once


#include "serde/serialization/template_function/srlz/type_erased_srlz_func.hpp"
#include "serde/mapper/ISerDeFuncMapper.hpp"

namespace serde::srlz {
    template <typename OutputV, typename Key>
    using ISrlzFuncMapper = ISerDeFuncMapper<type_erased_srlz_func<OutputV>, Key>;
}