#pragma once

#include "serde/deserialization/template_function/dsrlz/Deserializer.hpp"

namespace serde::dsrlz::func {

    template<typename InputType, typename OutputType>
    [[nodiscard]] OutputType deserialize(const InputType& input) {
        return Deserializer<InputType, OutputType>::deserialize(input);
    }

}