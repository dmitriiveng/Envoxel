#pragma once

#include "serde/serialization/mapper/ISerializationFunctionsMapper.hpp"
#include "serde/serialization/aggregate/CFieldGetter.hpp"

#include <type_traits>
#include <vector>
#include <stdexcept>
#include <string>
#include <boost/pfr.hpp>

/**
 * @brief Maps aggregate types to serialization functions.
 *
 * AggregateSerializerMapper stores serialization functions for aggregate types
 * that produce a vector of ReturnV values for each field.
 * Each aggregate type is identified by a string key.
 *
 * @tparam ReturnV The return type of the serialization function for individual fields.
 */
template<typename ReturnV>
class AggregateSerializerMapper final {
public:
    std::unordered_map<std::string, std::function<std::vector<ReturnV>(const void*)>> data;

public:
    /**
     * @brief Retrieve the serialization function for a given key.
     *
     * @param key The string identifier of the aggregate type.
     * @return A std::function that takes a const void* pointer to the aggregate
     *         and returns a vector of serialized field values.
     * @throws std::logic_error if the key is not found in the mapper.
     */
    std::function<std::vector<ReturnV>(const void*)> get_function(const std::string& key) const
    {
        const auto it = data.find(key);
        if (it == data.end()) throw std::logic_error("doesn't have a serialization function");
        return it->second;
    }

    /**
     * @brief Register a serialization function for an aggregate type.
     *
     * Generates a function that serializes each field of the aggregate using
     * the provided mapper and stores it internally with the specified key.
     *
     * @tparam Aggregate The aggregate type.
     * @tparam FG The FieldsGetter type that implements the field traversal.
     *
     * @param key The string key identifying the aggregate type.
     * @param mapper Reference to an ISerializationFunctionsMapper providing
     *               serialization functions for individual field types.
     * @param fields_getter Object implementing field traversal for the aggregate.
     *
     * @throws std::logic_error if a function is already registered for the given key.
     *
     * @note The lifetime of the mapper must outlive the call to this function.
     *       fields_getter is moved into the stored lambda, so it must be copyable or movable.
     */
    template<typename Aggregate, typename FG>
    requires std::is_aggregate_v<Aggregate>
        && CFieldsGetter<FG, Aggregate, std::function<ReturnV(Aggregate&)>>
    void add_function(
        std::string key,
        const ISerializationFunctionsMapper<ReturnV, std::type_index>& mapper,
        FG fields_getter
        )
    {
        if (data.contains(key)) {
            throw std::logic_error("type already has serialization function");
        }

        std::unordered_map<std::type_index, std::function<ReturnV(const void*)>> local_mapper;

        Aggregate instance{};
        fields_getter.for_each_field(instance, [&](auto& field) {
            if (!local_mapper.contains(typeid(field))) {
                local_mapper.emplace(typeid(field), mapper.get_function(typeid(field)));
            }
        });

        auto function = [fields_getter = std::move(fields_getter), local_mapper](const void* ptr) {
            const Aggregate& aggregate = *reinterpret_cast<const Aggregate*>(ptr);
            std::vector<ReturnV> out;

            fields_getter.for_each_field(aggregate, [&](auto& field) {
                std::function<ReturnV(const void*)> func = local_mapper.at(std::type_index(typeid(field)));
                out.push_back(func(&field));
            });

            return out;
        };

        data.emplace(key, std::move(function));
    }
};