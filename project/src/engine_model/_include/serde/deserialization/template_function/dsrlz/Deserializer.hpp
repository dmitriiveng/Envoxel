#pragma once

#include "serde/template_utils/dependent_false_v.hpp"

namespace serde::dsrlz::func {

    template<typename InputType, typename OutputType, typename = void>
    struct Deserializer {
        //static ReturnType parse(const InputValue& input)

        static_assert(dependent_false_v<OutputType>,
            "SingleTypeDeserializer for this type is not implemented"
            );

    };
}