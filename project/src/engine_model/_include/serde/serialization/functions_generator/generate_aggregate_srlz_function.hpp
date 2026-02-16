#pragma once
#include <vector>
#include <type_traits>

#include "serde/serialization/template_function/srlz/serialize.hpp"
#include "serde/serialization/template_function/data_structures/to_sequence/to_sequence.hpp"
#include "serde/serialization/template_function/srlz/type_erased_srlz_func.hpp"

namespace serde::srlz {

    template<
        typename InputV,
        typename OutputV,
        typename AggregateFieldsGetter
    >
    requires std::is_aggregate_v<InputV>
    [[nodiscard]] type_erased_srlz_func<InputV> generate_aggregate_srlz_function() {

        auto serialization = [](const void* input) -> OutputV {
            const InputV input_v = *static_cast<const InputV*>(input);
            std::vector<OutputV> output_vector;

            AggregateFieldsGetter::for_each_field(input_v, [&output_vector](const auto& field) {
                output_vector.push_back(
                    func::serialize<decltype(field), OutputV>(field)
                );
            });

            return func::to_sequence(output_vector);
        };

        return serialization;
    }

}

