#pragma once

#include <string>

#include "serde/deserialization/template_function/dsrlz/Deserializer.hpp"
#include "serde/string_utils/from_structure/copy_quoted.hpp"

namespace serde::dsrlz::func{
    template<>
    struct Deserializer<std::string, int> {
        static int deserialize(const std::string& input) {
            return std::stoi(input);
        }
    };

    template<>
    struct Deserializer<std::string, float> {
        static float deserialize(const std::string& input) {
            return std::stof(input);
        }
    };

    template<>
    struct Deserializer<std::string, double> {
        static double deserialize(const std::string& input) {
            return std::stod(input);
        }
    };

    template<>
    struct Deserializer<std::string, std::string> {
        static std::string deserialize(const std::string& input) {
            auto b = input.begin();
            const auto e = input.end();
            const std::optional<std::string> result = str_utils::copy_quoted(b, e, '"');
            if (!result.has_value()) {
                throw std::runtime_error("Could not deserialize string: " + input + " to string");
            }
            std::string res_str = result.value();
            res_str.pop_back();
            return std::string(++res_str.begin(), res_str.end());
        }
    };
}