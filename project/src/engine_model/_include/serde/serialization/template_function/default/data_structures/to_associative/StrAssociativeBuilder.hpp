#pragma once

#include "serde/serialization/template_function/data_structures/to_associative/to_associative.hpp"
#include "serde/string_utils/to_structure/make_associative_structure_of_tokens.hpp"

#include <string>
#include <map>

template<>
struct serde::srlz::func::AssociativeBuilder<std::string> {
    static std::string build(const std::map<std::string, std::string>& input) {
        std::string result =
            str_utils::make_associative_structure_of_tokens(
                input,
                '[', ']'
                );
        return result;
    }
};
