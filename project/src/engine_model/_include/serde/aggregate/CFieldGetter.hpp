#pragma once

#include <concepts>

/// Should iterate throw fields in same order every time
template <typename FG, typename Aggregate, typename Func>
concept CFieldsGetter = requires(FG fg, Aggregate& aggr, Func f) {
    { fg.for_each_field(aggr, f) };
};