#pragma once

#include "serde/deserialization/template_function/dsrlz/deserialize.hpp"
#include "serde/deserialization/template_function/dsrlz/type_erased_dsrlz_func.hpp"
#include "serde/type_erasure/VoidPtrAny.hpp"

namespace serde::dsrlz {
    template<
        typename InputV,
        typename OutputV
    >
    [[nodiscard]] type_erased_dsrlz_func<InputV>
    generate_simple_type_dsrlz_function() {
        auto deserialization = [](const InputV& input) {
            OutputV result = func::deserialize<InputV, OutputV>(input);

            return VoidPtrAny(result);
        };

        return deserialization;
    }
}
