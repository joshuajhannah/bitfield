#pragma once

#include <cstdint>
#include <type_traits>

namespace detail {
    template<typename T, uint8_t Index, uint8_t Length> requires std::is_unsigned_v<T>
    class Field {
        static_assert(Index + Length <= sizeof(T) * 8, "Bit region is longer than the underlying type.");
        static_assert(Length > 0, "Cannot represent zero-width length");

        static constexpr T mask = Length == sizeof(T) * 8 ? ~T{0} : (T{1} << Length) - 1;
    public:
        operator T() const
        {
            T repr = *reinterpret_cast<T const*>(this);
            return (repr >> Index) & mask;
        }

        constexpr T operator=(T value)
        {
            T& repr = *reinterpret_cast<T*>(this);
            repr &= ~(mask << Index);
            repr |= (value & mask) << Index;

            return repr;
        }
    };
}

template<typename T> requires std::is_unsigned_v<T>
class BitField {
public:
    template<uint8_t Index, uint8_t Length>
    using _Field = detail::Field<T, Index, Length>;
    BitField() = default;
    BitField(T underlying) : _underlying(underlying) {}
    operator T() const { return _underlying; }

protected:
    T _underlying{0};
};

#define Field [[no_unique_address]] _Field
