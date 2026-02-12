#pragma once

#include "serde/serialization/template_function/srlz/Serializer.hpp"

namespace serde::srlz::func {

    template<typename InputType, typename OutputType>
    [[nodiscard]] OutputType serialize(const InputType& input) {
        return Serializer<InputType, OutputType>::serialize(input);
    }

}