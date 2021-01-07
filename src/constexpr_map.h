#ifndef CONSTEXPR_MAP_H
#define CONSTEXPR_MAP_H

#include <array>
#include <stdexcept>
#include <algorithm>
#include <concepts>

template<typename Key, typename Value, size_t Size>
requires std::equality_comparable<Key> class constexpr_map
{
private:
    using data_t = const std::array<std::pair<Key, Value>, Size>;
    data_t data;

public:
    explicit constexpr constexpr_map(const data_t& data_) noexcept
        : data(data_)
    {
    }

    [[nodiscard]] constexpr Value operator[](const Key& key) const { return at(key); }

    [[nodiscard]] constexpr Value at(const Key& key) const
    {
        const auto itr = std::find_if(data.cbegin(), data.cend(), [&key](const auto& v) { return v.first == key; });
        if (itr != data.cend())
        {
            return itr->second;
        }
        throw std::range_error("Not Found");
    }

    [[nodiscard]] constexpr Value at_or_default(const Key& key, const Value& val) const noexcept
    {
        const auto itr = std::find_if(data.cbegin(), data.cend(), [&key](const auto& v) { return v.first == key; });
        if (itr != data.cend())
        {
            return itr->second;
        }
        return val;
    }

    [[nodiscard]] constexpr bool contains(const Key& key) const noexcept
    {
        const auto itr = std::find_if(data.cbegin(), data.cend(), [&key](const auto& v) { return v.first == key; });
        if (itr != data.cend())
        {
            return true;
        }
        return false;
    }

    [[nodiscard]] constexpr size_t size() const noexcept { return Size; }
    [[nodiscard]] constexpr auto   cbegin() const noexcept { return data.cbegin(); }
    [[nodiscard]] constexpr auto   cend() const noexcept { return data.cend(); }
};

#endif  //CONSTEXPR_MAP_H
