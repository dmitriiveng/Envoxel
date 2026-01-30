#include <gtest/gtest.h>
#include "serde/serialization/aggregate/PFRFieldsGetter.hpp"

namespace {
    struct A final {
        int a;
        bool b;
        double c;
    };
}

TEST(PFRFieldsGetter, GetFields) {
    PFRFieldsGetter getter;

    A a{10, true, 1.5};

    std::vector<std::string> out;
    getter.for_each_field(a, [&](auto& field) {
        out.push_back(std::to_string(field));
    });

    EXPECT_EQ(out[0], std::to_string(a.a));
    EXPECT_EQ(out[1], std::to_string(a.b));
    EXPECT_EQ(out[2], std::to_string(a.c));
}
