#pragma once

#include <string>

#include "serde/serialization/template_function/srlz/Serializer.hpp"
#include "serde/string_utils/floating_point/floating_point_to_string.hpp"

namespace serde::srlz::func{
    template<>
    struct Serializer<int, std::string> {
        static std::string serialize(const int input) {
            return std::to_string(input);
        }
    };

    template<>
    struct Serializer<float, std::string> {
        static std::string serialize(const float& input) {
            return str_utils::floating_point_to_string(input);
        }
    };

    template<>
    struct Serializer<double, std::string> {
        static std::string serialize(const double& input) {
            return str_utils::floating_point_to_string(input);
        }
    };

    template<>
    struct Serializer<std::string, std::string> {
        static std::string serialize(const std::string& input) {
            return '"' + input + '"';
        }
    };
}
