#pragma once

#include <concepts>

template <typename FG, typename Aggregate, typename Func>
concept CFieldsGetter = requires(FG fg, Aggregate& aggr, Func f) {
    { fg.for_each_field(aggr, f) };
};