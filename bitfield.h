#pragma once

#include <cstdint>
#include <type_traits>
#include <cstring>

#include <iostream>

namespace detail {
    template<typename UnderlyingT, uint8_t Index, uint8_t Length> requires std::is_unsigned_v<UnderlyingT>
    class Field {
        static_assert(Index + Length <= sizeof(UnderlyingT) * 8, "Bit region is longer than the underlying type.");
        static_assert(Length > 0, "Cannot represent zero-width length");

        static constexpr UnderlyingT mask = Length == sizeof(UnderlyingT) * 8 ? ~UnderlyingT{0} : (UnderlyingT{1} << Length) - 1;
    public:
        operator UnderlyingT() const
        {
            UnderlyingT repr = *reinterpret_cast<UnderlyingT const*>(this);
            return (repr >> Index) & mask;
        }

        constexpr UnderlyingT operator=(UnderlyingT value)
        {
            UnderlyingT* repr = reinterpret_cast<UnderlyingT*>(this);
            *repr &= ~(mask << Index);
            *repr |= (value & mask) << Index;
            return *repr;
        }
    };
}

template<typename UnderlyingT> requires std::is_unsigned_v<UnderlyingT>
class BitField {
public:
    template<uint8_t Index, uint8_t Length>
    using _Field = detail::Field<UnderlyingT, Index, Length>;

    operator UnderlyingT() const { return _underlying; }

public:
    UnderlyingT _underlying;
};

#define Field [[no_unique_address]] _Field
