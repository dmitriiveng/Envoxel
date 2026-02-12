#pragma once

#include <map>

#include "serde/deserialization/template_function/default/data_structures/from_associative/StrAssociativeParser.hpp"
#include "serde/deserialization/template_function/dsrlz/Deserializer.hpp"

template<typename K, typename V>
struct serde::dsrlz::func::Deserializer<std::string, std::map<K, V>> {
    static std::map<K, V> deserialize(const std::string& input) {
        std::map<K, V> result;
        for (const std::pair<std::string, std::string> str : from_associative<std::string>(input)) {
            result.insert(
                std::pair<K, V>(
                Deserializer<std::string, K>::deserialize(str.first),
                Deserializer<std::string, V>::deserialize(str.second))
                );
        }

        return result;
    }
};
