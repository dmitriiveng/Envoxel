#include "serde/serialization/mapper/StringSerializationFunctionsMapper.hpp"

#include <stdexcept>


std::function<std::string(const void*)> StringSerializationFunctionsMapper::get_function(
    const std::type_info& type_info_v) const
{
    const std::type_index type_index_v(type_info_v);
    const auto it = data.find(type_index_v);
    if (it == data.end()) {
        throw std::logic_error(std::string("No deserialization function for type: ") + type_info_v.name());
    }
    return it->second;
}

void StringSerializationFunctionsMapper::add_function(
    const std::type_info& type_info_v,
    const std::function<std::string(const void*)>& function)
{
    const std::type_index type_index_v(type_info_v);
    if (data.contains(type_index_v)) {
        throw std::logic_error(std::string("type already has serialization function") + type_info_v.name());
    }

    data.emplace(type_index_v, function);
}
