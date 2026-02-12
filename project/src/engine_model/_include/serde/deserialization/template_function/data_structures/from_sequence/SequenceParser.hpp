#pragma once

#include "serde/template_utils/dependent_false_v.hpp"

namespace serde::dsrlz::func {

    template<typename InputValue>
    struct SequenceParser {
        //static std::vector<InputValue> parse(const InputValue& input);
        static_assert(dependent_false_v<InputValue>,
            "SequenceParser for this type is not implemented");
    };
}