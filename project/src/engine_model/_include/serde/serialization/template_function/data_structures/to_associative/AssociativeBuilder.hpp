#pragma once

#include "serde/template_utils/dependent_false_v.hpp"

namespace serde::srlz::func {

    template<typename T>
    struct AssociativeBuilder {
        //static T parse(const std::map<T, T>& input);
        static_assert(dependent_false_v<T>,
            "AssociativeBuilder for this type is not implemented");
    };
}