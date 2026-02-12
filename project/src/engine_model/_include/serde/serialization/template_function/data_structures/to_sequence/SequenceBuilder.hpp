#pragma once

#include "serde/template_utils/dependent_false_v.hpp"

namespace serde::srlz::func {

    template<typename T>
    struct SequenceBuilder {
        //static T parse(const std::vector<T>& input);
        static_assert(dependent_false_v<T>,
            "SequenceBuilder for this type is not implemented");
    };
}