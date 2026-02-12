#pragma once

#include "serde/deserialization/template_function/data_structures/from_associative/AssociativeParser.hpp"

#include <map>

namespace serde::dsrlz::func {

    template<typename InputValue>
    [[nodiscard]] std::map<InputValue, InputValue> from_associative(const InputValue& input) {
        return AssociativeParser<InputValue>::parse(input);
    }

}