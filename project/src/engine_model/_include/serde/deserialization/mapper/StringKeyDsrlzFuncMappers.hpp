#pragma once

#include "serde/deserialization/mapper/IDsrlzFuncMapper.hpp"
#include <string>
#include <map>

namespace serde::dsrlz {
    template <typename InputV>
    using StringKeyDeserializationMapper = IDsrlzFuncMapper<InputV, std::string>;
}