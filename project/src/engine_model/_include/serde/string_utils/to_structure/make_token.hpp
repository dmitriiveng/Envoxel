#pragma once

#include <optional>
#include <stdexcept>

namespace str_utils {
    inline std::string make_token(
        const std::string& token,
        const char begin_of_token,
        const char end_of_token
    ){
        std::string result = begin_of_token + token + end_of_token;
        return result;
    }
}