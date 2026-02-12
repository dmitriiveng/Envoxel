#pragma once

#include "serde/serialization/template_function/data_structures/to_associative/AssociativeBuilder.hpp"

#include <map>

namespace serde::srlz::func {

    template<typename T>
    [[nodiscard]] T to_associative(const std::map<T, T>& input) {
        return AssociativeBuilder<T>::build(input);
    }

}