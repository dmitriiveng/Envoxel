#pragma once

#include "serde/serialization/template_function/data_structures/to_sequence/SequenceBuilder.hpp"

#include <vector>

namespace serde::srlz::func {

    template<typename T>
    [[nodiscard]] T to_sequence(const std::vector<T>& input) {
        return SequenceBuilder<T>::build(input);
    }

}