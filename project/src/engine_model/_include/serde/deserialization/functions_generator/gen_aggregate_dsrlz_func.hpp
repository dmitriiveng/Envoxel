#pragma once
#include <vector>
#include <any>
#include <stdexcept>
#include <type_traits>

#include "serde/deserialization/template_function/dsrlz/deserialize.hpp"
#include "serde/deserialization/template_function/data_structures/from_sequence/from_sequence.hpp"
#include "serde/deserialization/template_function/dsrlz/type_erased_dsrlz_func.hpp"
#include "serde/type_erasure/VoidPtrAny.hpp"

namespace serde::dsrlz {

    template<
        typename InputV,
        typename OutputV,
        typename AggregateFieldsGetter
    >
    requires std::is_aggregate_v<OutputV>
    [[nodiscard]] type_erased_dsrlz_func<InputV> gen_aggregate_dsrlz_func() {

        auto deserialization = [](const InputV& input) -> VoidPtrAny {
            std::vector<InputV> input_vector;
            try {
                input_vector = func::from_sequence<InputV>(input);
            }
            catch (std::runtime_error& e) {
                throw std::runtime_error(std::string("Failed to deserialize aggregate: ") + e.what());
            }

            constexpr std::size_t fields_count = AggregateFieldsGetter::template field_count<OutputV>();

            if (input_vector.size() != fields_count) {
                throw std::logic_error(
                    std::string(std::string("Input size (") + std::to_string(input_vector.size()) + ") does not match number of fields (" + std::to_string(fields_count) + ") in aggregate of type: ") + typeid(OutputV).name()
                );
            }

            // Getting tuple type for field of OutputV
            using TupleType = AggregateFieldsGetter::template tuple_type<OutputV>;

            // Making a tuple of fields from a vector of InputV
            auto tuple_filled = [&]<std::size_t... I>(std::index_sequence<I...>) {
                // Deserialize function should be declared for needed type
                return std::make_tuple(
                    func::deserialize<
                        InputV,
                        std::remove_cv_t<std::remove_reference_t<std::tuple_element_t<I, TupleType>>>
                    >(input_vector[I])...
                );
            }(std::make_index_sequence<fields_count>{});

            // Using aggregate constructor
            OutputV aggregate_result = std::apply([](auto&&... args) {
                return OutputV{std::forward<decltype(args)>(args)...};
            }, tuple_filled);

            return VoidPtrAny(std::move(aggregate_result));
        };

        return deserialization;
    }

}

