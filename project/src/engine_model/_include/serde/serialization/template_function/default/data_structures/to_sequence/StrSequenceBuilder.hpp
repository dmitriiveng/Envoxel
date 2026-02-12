#pragma once

#include "serde/serialization/template_function/data_structures/to_sequence/to_sequence.hpp"

#include <string>
#include <vector>
#include "serde/string_utils/to_structure/make_sequence_of_tokens.hpp"

template<>
struct serde::srlz::func::SequenceBuilder<std::string> {
    static std::string build(const std::vector<std::string>& input){
        std::string result =
            str_utils::make_sequence_of_tokens(
                input,
                '[', ']'
                );
        return result;
    }
};
