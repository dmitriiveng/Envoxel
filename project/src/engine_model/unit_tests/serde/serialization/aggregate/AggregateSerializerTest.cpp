/*
#include <gtest/gtest.h>
#include <boost/pfr.hpp>
#include "serde/serialization/mapper/ISerializationFunctionsMapper.hpp"

namespace {
    struct Aggregate final {
        int a;
        double b;
    };

    struct FieldsGetter {
        template <typename Aggregate, typename Func>
        void for_each_field(Aggregate& aggr, Func&& f) const {
            boost::pfr::for_each_field(aggr, std::forward<Func>(f));
        }
    };

    class SerializationFunctionsMapper final : public ISerializationFunctionsMapper<std::string, std::type_index> {
        std::unordered_map<std::type_index, std::function<std::string(const void*)>> data;

    public:
        std::function<std::string(const void*)> get_function(const std::type_index& type_index_v) const override
        {
            const auto it = data.find(type_index_v);
            if (it == data.end()) throw std::logic_error("doesn't have a serialization function");
            return it->second;
        }
        void add_function(
            const std::type_index& type_index_v,
            const std::function<std::string(const void*)>& function
            ) override
        {
            if (data.contains(type_index_v)) {
                throw std::logic_error("type already has serialization function");
            }

            data.emplace(type_index_v, function);
        }
    };

    std::string func_int(const void* ptr) {
        const int* i = reinterpret_cast<const int*>(ptr);
        return std::to_string(*i);
    }

    std::string func_double(const void* ptr) {
        const double* d = reinterpret_cast<const double*>(ptr);
        return std::to_string(*d);
    }
}

TEST(AggregateSerializer, GetFields) {
    FieldsGetter getter;

    Aggregate a{10, 1.5};

    SerializationFunctionsMapper mapper;
    mapper.add_function(typeid(int), func_int);
    mapper.add_function(typeid(double), func_double);

    std::vector<std::string> out =
        serialize_aggregate<std::string, Aggregate, FieldsGetter>(a, &mapper, std::move(getter));

    EXPECT_EQ(out[0], std::to_string(a.a));
    EXPECT_EQ(out[1], std::to_string(a.b));
}
*/