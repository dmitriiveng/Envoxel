#pragma once

#include "serde/serialization/mapper/ISrlzFuncMapper.hpp"
#include <string>
#include <map>

namespace serde::srlz {
    template <typename OutputV>
    using StringKeySrlzFuncMapper = ISrlzFuncMapper<OutputV, std::string>;
}