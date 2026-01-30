#pragma once

#include "serde/serialization/mapper/ISerializationFunctionsMapper.hpp"

#include <string>

class StringSerializationFunctionsMapper final
    : public ISerializationFunctionsMapper<std::string, std::type_info>
{
    std::unordered_map<std::type_index, std::function<std::string(const void*)>> data;

public:
    std::function<std::string(const void*)> get_function(const std::type_info& type_info_v) const override;
    void add_function(
        const std::type_info& type_info_v,
        const std::function<std::string(const void*)>& function
        ) override;
};
