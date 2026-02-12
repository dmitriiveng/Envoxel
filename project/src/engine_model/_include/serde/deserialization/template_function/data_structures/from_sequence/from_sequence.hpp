#pragma once

#include "serde/deserialization/template_function/data_structures/from_sequence/SequenceParser.hpp"

#include <vector>

namespace serde::dsrlz::func {

    template<typename InputValue>
    [[nodiscard]] std::vector<InputValue> from_sequence(const InputValue& input) {
        return SequenceParser<InputValue>::parse(input);
    }

}