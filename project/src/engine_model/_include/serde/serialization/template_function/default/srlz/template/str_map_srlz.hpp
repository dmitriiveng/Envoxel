#pragma once

#include <map>

#include "serde/serialization/template_function/default/data_structures/to_associative/StrAssociativeBuilder.hpp"
#include "serde/serialization/template_function/srlz/Serializer.hpp"

template<typename K, typename V>
struct serde::srlz::func::Serializer<std::map<K, V>, std::string> {
    static std::string serialize(const std::map<K, V>& input) {
        std::map<std::string, std::string> str_map;
        for (const auto& pair : input) {
            str_map.emplace(
                Serializer<K, std::string>::serialize(pair.first),
                Serializer<V, std::string>::serialize(pair.second)
            );
        }

        return AssociativeBuilder<std::string>::build(str_map);
    }
};
