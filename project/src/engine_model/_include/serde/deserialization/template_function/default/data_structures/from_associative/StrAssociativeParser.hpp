#pragma once

#include "serde/deserialization/template_function/data_structures/from_associative/from_associative.hpp"
#include "serde/string_utils/from_structure/split_by_tokens_associative.hpp"

#include <string>
#include <map>

template<>
struct serde::dsrlz::func::AssociativeParser<std::string> {
    static std::map<std::string, std::string> parse(const std::string& input) {
        auto it_pair_begin = input.begin();
        auto it_pair_end = input.end();

        std::map<std::string, std::string> result =
            str_utils::split_by_tokens_associative<decltype(it_pair_begin), decltype(it_pair_end)>(
                it_pair_begin,
                it_pair_end,
                '[', ']', '"'
                );
        return result;
    }
};
