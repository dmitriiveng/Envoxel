#pragma once

#include "serde/serialization/template_function/srlz/serialize.hpp"
#include "serde/serialization/template_function/srlz/type_erased_srlz_func.hpp"

namespace serde::srlz {
    template<
        typename InputV,
        typename OutputV
    >
    [[nodiscard]] type_erased_srlz_func<OutputV>
    gen_simple_type_srlz_func() {
        auto serialization = [](const void* input) {
            OutputV result = func::serialize<InputV, OutputV>(*static_cast<const InputV*>(input));
            return result;
        };
        return serialization;
    }
}