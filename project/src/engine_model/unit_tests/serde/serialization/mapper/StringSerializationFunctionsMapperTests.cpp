#include <gtest/gtest.h>
#include "serde/serialization/mapper/StringSerializationFunctionsMapper.hpp"

namespace {
    std::string func_int(const void* ptr) {
        const int* i = reinterpret_cast<const int*>(ptr);
        return std::to_string(*i);
    }

    std::string func_double(const void* ptr) {
        const double* d = reinterpret_cast<const double*>(ptr);
        return std::to_string(*d);
    }
}

TEST(StringSerializationFunctionsMapper, AddGetFunction) {
    StringSerializationFunctionsMapper mapper;

    mapper.add_function(typeid(int),func_int);
    mapper.add_function(typeid(double), func_double);

    int a = 42;
    double b = 3.14;

    auto f_int = mapper.get_function(typeid(int));
    auto f_double = mapper.get_function(typeid(double));

    EXPECT_EQ(f_int(&a), func_int(&a));
    EXPECT_EQ(f_double(&b), func_double(&b));
}

TEST(StringSerializationFunctionsMapper, AddSameTypeException) {
    StringSerializationFunctionsMapper mapper;

    mapper.add_function(typeid(int), func_int);

    EXPECT_THROW(mapper.add_function(typeid(int), func_int), std::logic_error);
}

TEST(StringSerializationFunctionsMapper, GetUnknownTypeException) {
    StringSerializationFunctionsMapper mapper;

    EXPECT_THROW(mapper.get_function(typeid(float)), std::logic_error);
}