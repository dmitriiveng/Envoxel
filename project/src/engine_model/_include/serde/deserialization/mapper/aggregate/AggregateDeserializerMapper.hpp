#pragma once

#include "serde/deserialization/mapper/IDeserializationFunctionsMapper.hpp"
#include "serde/aggregate/CFieldGetter.hpp"

#include <type_traits>
#include <typeindex>
#include <vector>
#include <stdexcept>
#include <string>
#include <boost/pfr.hpp>

/**
 * @brief Maps aggregate types to deserialization functions.
 *
 * Stores functions that construct aggregate objects from a sequence of input values.
 * Each aggregate type is identified by a string key.
 *
 * @tparam InputV Input value type used for deserializing individual fields.
 */
template<typename InputV>
class AggregateDeserializerMapper final {
public:
    std::unordered_map<std::string, std::function<std::any(const std::vector<InputV>&)>> data;

public:
    /**
     * @brief Retrieve a deserialization function by key.
     *
     * @param key String identifier of the aggregate type.
     * @return Function that takes a vector of input values and returns a deserialized aggregate wrapped in std::any.
     *
     * @throws std::logic_error if no function is registered for the given key.
     */
    std::function<std::any(const std::vector<InputV>&)> get_function(const std::string& key) const
    {
        const auto it = data.find(key);
        if (it == data.end()) throw std::logic_error(std::string("doesn't have a deserialization function for key: ") + key);
        return it->second;
    }

    /**
     * @brief Register a deserialization function for an aggregate type.
     *
     * Builds a function that deserializes each field of the aggregate using
     * the provided field-level deserialization mapper.
     *
     * @tparam Aggregate Aggregate type to deserialize.
     * @tparam FG Fields getter type.
     *
     * @param key String identifier of the aggregate type.
     * @param mapper Mapper providing deserialization functions for individual field types.
     * @param fields_getter Object used to iterate over aggregate fields.
     *
     * @throws std::logic_error if a function is already registered for the given key.
     * @throws std::logic_error if the input vector size does not match the number of fields.
     *
     * @note Returned aggregate is stored in std::any.
     */
    template<typename Aggregate, typename FG>
    requires std::is_aggregate_v<Aggregate>
        && CFieldsGetter<FG, Aggregate, std::function<std::any(const InputV& input)>>
    void add_function(
        std::string key,
        const IDeserializationFunctionsMapper<InputV, std::type_info>& mapper,
        FG fields_getter
        )
    {
        if (data.contains(key)) {
            throw std::logic_error(std::string("type of key: ") + key + std::string(" already has deserialization function"));
        }

        std::unordered_map<std::type_index, std::function<std::any(const InputV& input)>> local_mapper;

        Aggregate instance{};
        fields_getter.for_each_field(instance, [&](auto& field) {
            if (!local_mapper.contains(typeid(field))) {
                local_mapper.emplace(typeid(field), mapper.get_function(typeid(field)));
            }
        });

        auto function = [key, fields_getter = std::move(fields_getter), local_mapper](const std::vector<InputV>& input) {
            Aggregate aggregate{};
            std::size_t i = 0;
            fields_getter.for_each_field(aggregate, [&](auto& field) {
                if (input.size() < i + 1) {
                    throw std::logic_error(std::string("Input size does not match number of fields in aggregate for key: ") + key);
                }

                std::function<std::any(const InputV& input)> func = local_mapper.at(std::type_index(typeid(field)));
                field = std::any_cast<std::decay_t<decltype(field)>>(func(input[i]));
                i++;
            });

            return std::any(aggregate);
        };

        data.emplace(key, std::move(function));
    }
};
