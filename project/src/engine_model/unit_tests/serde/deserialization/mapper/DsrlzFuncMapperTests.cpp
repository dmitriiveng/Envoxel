#include <gtest/gtest.h>

#include "serde/deserialization/mapper/DsrlzFuncMapper.hpp"
#include "serde/type_erasure/VoidPtrAny.hpp"

using namespace serde::dsrlz;

namespace {

    using Mapper = DsrlzFuncMapper<std::string, std::string>;

    TEST(DsrlzFuncMapperTest, AddAndGetFunction) {
        Mapper mapper;

        mapper.add_function("int", [](const std::string& str) {
            return VoidPtrAny(std::stoi(str));
        });

        auto func = mapper.get_function("int");
        VoidPtrAny result = func("41");

        EXPECT_EQ(result.get_value<int>(), 41);
    }

    TEST(DsrlzFuncMapperTest, AddDuplicateThrows) {
        Mapper mapper;

        mapper.add_function("int", [](const std::string& str) {
            return VoidPtrAny(std::stoi(str));
        });

        EXPECT_THROW(
            mapper.add_function("int", [](const std::string& str) {
                return VoidPtrAny(std::stoi(str));
            }),
            std::logic_error
        );
    }

    TEST(DsrlzFuncMapperTest, GetMissingThrows) {
        const Mapper mapper;

        EXPECT_THROW(
            auto f = mapper.get_function("missing"),
            std::logic_error
        );
    }

    TEST(DsrlzFuncMapperTest, ReplaceFunction) {
        Mapper mapper;

        mapper.add_function("int", [](const std::string& str) {
            return VoidPtrAny(std::stoi(str));
        });

        auto func = mapper.get_function("int");
        VoidPtrAny result = func("21");
        EXPECT_EQ(result.get_value<int>(), 21);

        mapper.replace_function("int", [](const std::string& str) {
            return VoidPtrAny(std::stoi(str) * 2);
        });

        func = mapper.get_function("int");
        result = func("21");
        EXPECT_EQ(result.get_value<int>(), 42);
    }

    TEST(DsrlzFuncMapperTest, ReplaceMissingThrows) {
        Mapper mapper;

        EXPECT_THROW(
            mapper.replace_function("int", [](const std::string& str) {
                return VoidPtrAny(std::stoi(str));
            }),
            std::logic_error
        );
    }
}
