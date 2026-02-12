#pragma once

#include "serde/template_utils/dependent_false_v.hpp"

namespace serde::srlz::func {

    template<typename InputType, typename OutputType, typename = void>
    struct Serializer {
        //static OutputType serialize(const InputType& input)

        static_assert(dependent_false_v<OutputType>,
            "SingleTypeDeserializer for this type is not implemented"
            );

    };
}