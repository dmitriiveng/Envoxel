#pragma once
#include <functional>
#include <typeindex>

/**
 * @brief Interface for a serialization functions mapper.
 *
 * Maps keys of type KeyType to serialization functions that take a void pointer
 * to an object and return a value of type ReturnV.
 * This is typically used for field-level serialization in aggregates.
 *
 * @tparam ReturnV The return type of the serialization function.
 * @tparam KeyType The type used to identify the serialized object.
 */
template<typename ReturnV, typename KeyType>
class ISerializationFunctionsMapper {
public:
    virtual ~ISerializationFunctionsMapper() = default;

    /**
     * @brief Retrieve the serialization function associated with a key.
     *
     * @param key The key identifying the object.
     * @return A std::function that takes a const void* pointer to the object and returns a ReturnV.
     * @throws std::logic_error if the key is not found.
     */
    virtual std::function<ReturnV(const void*)> get_function(const KeyType& key) const = 0;

    /**
     * @brief Register a serialization function for a given key.
     *
     * @param key The key identifying the object.
     * @param function The serialization function that takes a const void* and returns ReturnV.
     *
     * @note The function should be valid for the lifetime of the mapper usage.
     */
    virtual void add_function(
        const KeyType& key,
        const std::function<ReturnV(const void*)>& function
        ) = 0;
};
