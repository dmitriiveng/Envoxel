#pragma once

#include <vector>

#include "serde/serialization/template_function/default/data_structures/to_sequence/StrSequenceBuilder.hpp"
#include "serde/serialization/template_function/srlz/Serializer.hpp"

template<typename T>
struct serde::srlz::func::Serializer<std::vector<T>, std::string> {
    static std::string serialize(const std::vector<T>& input) {
        std::vector<std::string> result;
        for (const T& value : input) {
            result.push_back(Serializer<T, std::string>::serialize(value));
        }

        return SequenceBuilder<std::string>::build(result);
    }
};
