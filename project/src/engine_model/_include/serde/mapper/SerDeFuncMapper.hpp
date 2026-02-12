#pragma once

#include <string>
#include <stdexcept>

#include "serde/deserialization/mapper/IDsrlzFuncMapper.hpp"

namespace serde {
    template <typename Func, typename Key>
    class SerDeFuncMapper final : public ISerDeFuncMapper<Func, Key> {
        std::unordered_map<Key, Func> data;

    public:

        [[nodiscard]] Func get_function(const Key& key) const override {
            const auto it = data.find(key);
            if (it == data.end()){
                throw std::logic_error("No deserialization function");
            }
            return it->second;
        }

        void add_function(const Key& key, Func function) override {
            if (data.contains(key)) {
                throw std::logic_error("type already has deserialization function");
            }

            data.emplace(key, std::move(function));
        }

        void replace_function(const Key& key, Func function) override {
            const auto it = data.find(key);
            if (it == data.end()) {
                throw std::logic_error("No deserialization function");
            }
            it->second = std::move(function);
        }
    };
}