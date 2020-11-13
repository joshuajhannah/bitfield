# bitfield
A tiny header file for representing bitfields in C++20.

# Documentation
Types that wish to be represented as bitfields should inherit from the `BitField` type, declared as

    template<typename UnderlyingT>
    class BitField;
    
where UnderlyingT is the unsigned integer you wish to sit your bitfield atop.

From here, we declare the bitfield members in our type using the following type and corresponding macro

    template<typename T, uint8_t Index, uint8_t Length>
    class _Field;
    
    #define Field [[no_unique_address]] _Field

# Examples
## Single underlying
Here's a simple example representing a hardware register with a single underlying element.

    #include "bitfield.h"
    
    struct rx_register : public BitField<uint64_t>
    {
      Field<0, 12> id;
      Field<12, 16> user_flags;
      Field<16, 20> peripheral_flags;
      Field<12, 20> all_flags;
      Field<60, 64> type;
    };
    
    static_assert(sizeof(rx_register) == 8);
    
This example illustrates that we can have overlapping fields as well as gaps in our bitwise representation.

## Multiple underlying
We can even nest multiple bitfields

        #include "bitfield.h"
        
        struct foo {
        struct : public BitField<uint16_t> {
            Field<0, 9> header_type;
            Field<9, 7> header_meta;
        } __attribute__((packed));
        struct : public BitField<uint16_t> {
            Field<0, 4> payload_type;
            Field<4, 12> payload_target;
        } __attribute__((packed));
        struct : public BitField<uint32_t> {
            Field<0, 9> index;
            Field<9, 12> data;
            Field<21, 11> mask;
        } __attribute__((packed));
    } __attribute__((packed));
    
    static_assert(sizeof(foo) == 8);

# Caveats
- This optimisation we rely on is not guaranteed by the standard, so this code could break on a standard-compliant compiler.
- You won't be able to represent the same bit region with two different members, as they will have the same type and thus won't be optimised to sit at the same address.
