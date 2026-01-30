#pragma once

#include "serde/deserialization/mapper/IDeserializationFunctionsMapper.hpp"

#include <string>
#include <any>
#include <typeindex>

class StringDeserializationFunctionsMapper final
    : public IDeserializationFunctionsMapper<std::string, std::type_info>
{
    std::unordered_map<std::type_index, std::function<std::any(const std::string& input)>> data;

public:
    std::function<std::any(const std::string& input)> get_function(
        const std::type_info& type_info_v
        ) const override;

    void add_function(
        const std::type_info& type_info_v,
        const std::function<std::any(const std::string& input)>& function
        ) override;
};
