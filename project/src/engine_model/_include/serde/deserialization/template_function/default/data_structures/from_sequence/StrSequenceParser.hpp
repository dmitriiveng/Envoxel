#pragma once

#include "serde/deserialization/template_function/data_structures/from_sequence/from_sequence.hpp"

#include <string>
#include <vector>
#include "serde/string_utils/from_structure/split_by_tokens_sequence.hpp"

template<>
struct serde::dsrlz::func::SequenceParser<std::string> {
    static std::vector<std::string> parse(const std::string& input)
    {
        auto it_pair_begin = input.begin();
        auto it_pair_end = input.end();

        std::vector<std::string> result =
            str_utils::split_by_tokens_sequence<decltype(it_pair_begin), decltype(it_pair_end)>(
                it_pair_begin,
                it_pair_end,
                '[', ']', '"'
                );
        return result;
    }
};
