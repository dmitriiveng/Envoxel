#include "serde/deserialization/mapper/StringDeserializationFunctionsMapper.hpp"

#include <stdexcept>


std::function<std::any(const std::string& input)> StringDeserializationFunctionsMapper::get_function(
    const std::type_info& type_info_v
    ) const
{
    const std::type_index type_index_v(type_info_v);
    const auto it = data.find(type_index_v);
    if (it == data.end()){
        throw std::logic_error(std::string("No deserialization function for type: ") + type_info_v.name());
    }
    return it->second;
}

void StringDeserializationFunctionsMapper::add_function(
    const std::type_info& type_info_v,
    const std::function<std::any(const std::string& input)>& function
    )
{
    const std::type_index type_index_v(type_info_v);
    if (data.contains(type_index_v)) {
        throw std::logic_error(std::string("type already has deserialization function") + type_info_v.name());
    }

    data.emplace(type_index_v, function);
}
