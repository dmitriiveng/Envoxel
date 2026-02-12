#pragma once

#include "serde/template_utils/dependent_false_v.hpp"

namespace serde::dsrlz::func {

    template<typename InputValue>
    struct AssociativeParser {
        //static std::map<InputValue, InputValue> parse(const InputValue& input);
        static_assert(dependent_false_v<InputValue>,
            "AssociativeParser for this type is not implemented");
    };
}