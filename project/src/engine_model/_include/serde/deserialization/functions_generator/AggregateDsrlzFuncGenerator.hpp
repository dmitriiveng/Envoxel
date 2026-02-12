#pragma once
#include <vector>
#include <any>
#include <stdexcept>
#include <type_traits>
#include <functional>

#include "serde/deserialization/template_function/dsrlz/deserialize.hpp"
#include "serde/deserialization/template_function/data_structures/from_sequence/from_sequence.hpp"
#include "serde/deserialization/template_function/dsrlz/type_erased_dsrlz_func.hpp"
#include "serde/type_erasure/VoidPtrAny.hpp"

namespace serde::dsrlz {

    template<
        typename InputV,
        typename ReturnType,
        typename AggregateFieldsGetter
    >
    requires std::is_aggregate_v<ReturnType>
    [[nodiscard]] type_erased_dsrlz_func<InputV> generate_aggregate_dsrlz_function() {

        auto deserialization = [](const InputV& input) -> VoidPtrAny {
            std::vector<InputV> input_vector;
            try {
                input_vector = from_sequence<std::vector<InputV>>(input);
            }
            catch (std::runtime_error& e) {
                throw std::runtime_error(std::string("Failed to deserialize aggregate: ") + e.what());
            }

            constexpr std::size_t FieldsCount = AggregateFieldsGetter::template field_count<ReturnType>;

            if (input_vector.size() != FieldsCount) {
                throw std::logic_error(
                    std::string("Input size does not match number of fields in aggregate of type: ") + typeid(ReturnType).name()
                );
            }

            // Getting tuple type for field of ReturnType
            using TupleType = AggregateFieldsGetter::template tuple_type<ReturnType>;

            // Making a tuple of fields from a vector of InputV
            auto tuple_filled = [&]<std::size_t... I>(std::index_sequence<I...>) {
                // Deserialize function should be declared for needed type
                return std::make_tuple(
                    func::deserialize<
                        std::remove_cv_t<std::remove_reference_t<std::tuple_element_t<I, TupleType>>>
                    >(input_vector[I])...
                );
            }(std::make_index_sequence<FieldsCount>{});

            // Using aggregate constructor
            ReturnType aggregate_result = std::apply([](auto&&... args) {
                return ReturnType{std::forward<decltype(args)>(args)...};
            }, tuple_filled);

            return VoidPtrAny(std::move(aggregate_result));
        };

        return deserialization;
    }

}

