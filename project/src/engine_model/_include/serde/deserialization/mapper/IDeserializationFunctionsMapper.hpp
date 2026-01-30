#pragma once
#include <functional>
#include <any>

/**
 * @brief Interface for a deserialization functions mapper.
 *
 * Maps keys of type KeyType to deserialization functions that take an input
 * value of type InputV and return a deserialized object wrapped in std::any.
 *
 * std::any is used as an owning, type-erased container to provide RAII-based
 * lifetime management and exception safety for objects created during
 * deserialization.
 *
 * @tparam InputV The input type for deserialization.
 * @tparam KeyType The type used to identify the deserialized object.
 */
template<typename InputV, typename KeyType>
class IDeserializationFunctionsMapper {
public:
    virtual ~IDeserializationFunctionsMapper() = default;

    /**
     * @brief Retrieve the deserialization function associated with a key.
     *
     * @param key The key identifying the object.
     * @return A std::function that takes a const InputV& and returns a std::any.
     * @throws std::logic_error if the key is not found.
     */
    virtual std::function<std::any(const InputV& input)> get_function(
        const KeyType& key
        ) const = 0;

    /**
     * @brief Register a deserialization function for a given key.
     *
     * @param key The key identifying the object.
     * @param function The deserialization function that returns a std::any
     *        owning the constructed object.
     *
     * @throws std::logic_error if a function is already registered for the given key.
     */
    virtual void add_function(
        const KeyType& key,
        const std::function<std::any(const InputV& input)>& function
        ) = 0;
};
