#pragma once

#include <boost/pfr.hpp>

struct PFRFieldsGetter {
    template <typename Aggregate, typename Func>
    void for_each_field(Aggregate& aggr, Func&& f) const {
        boost::pfr::for_each_field(aggr, std::forward<Func>(f));
    }
};