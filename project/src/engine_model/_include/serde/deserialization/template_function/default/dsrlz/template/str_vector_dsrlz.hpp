#pragma once

#include <vector>

#include "serde/deserialization/template_function/default/data_structures/from_sequence/StrSequenceParser.hpp"
#include "serde/deserialization/template_function/dsrlz/Deserializer.hpp"

template<typename T>
struct serde::dsrlz::func::Deserializer<std::string, std::vector<T>> {
    static std::vector<T> deserialize(const std::string& input) {
        std::vector<T> result;
        for (const std::string& str : from_sequence<std::string>(input)) {
            result.push_back(Deserializer<std::string, T>::deserialize(str));
        }

        return result;
    }
};
