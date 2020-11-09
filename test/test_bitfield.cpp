#include "../bitfield.h"
#include <gtest/gtest.h>

struct BUI8Normal : public BitField<uint8_t>
{
    Field<0, 6> foo{};
    Field<6, 2> bar{};
};
static_assert(sizeof(BUI8Normal) == 1, "[[no_unique_address]] not optimising as expected.");

TEST(BITFIELD, TestUInt8Constructor)
{
    BUI8Normal bits{71};

    EXPECT_EQ(bits.foo, 7);
    EXPECT_EQ(bits.bar, 1);
}

TEST(BITFIELD, TestUInt8Normal)
{
    BUI8Normal bits;
    bits.foo = 7;
    bits.bar = 1;

    EXPECT_EQ(static_cast<uint8_t>(bits), 71);
    EXPECT_EQ(bits.foo, 7);
    EXPECT_EQ(bits.bar, 1);
}


struct BUI8Whole : public BitField<uint8_t>
{
    Field<0, 8> foo{};
};

TEST(BITFIELD, TestUInt8Whole)
{
    BUI8Whole bits;
    bits.foo = 255;

    EXPECT_EQ(bits.foo, 255);
    EXPECT_EQ(bits, 255);
}

struct BUI8Overlap : public BitField<uint8_t>
{
    Field<0, 6> foo{};
    Field<2, 6> bar{};
};

TEST(BITFIELD, TestUInt8OverlapConstruct)
{
    BUI8Overlap bits{157};

    EXPECT_EQ(bits.foo, 29);
    EXPECT_EQ(bits.bar, 39);
}

TEST(BITFIELD, TestUInt8OverlapAssign)
{
    BUI8Overlap bits;
    bits.foo = 29;
    bits.bar = 39;

    EXPECT_EQ(bits, 157);
    EXPECT_EQ(bits.foo, 29);
    EXPECT_EQ(bits.bar, 39);
}

struct BUI8Many : public BitField<uint8_t>
{
    Field<0, 1> field1{};
    Field<1, 1> field2{};
    Field<2, 1> field3{};
    Field<3, 1> field4{};
    Field<4, 1> field5{};
    Field<5, 1> field6{};
    Field<6, 1> field7{};
    Field<7, 1> field8{};
};

TEST(BITFIELD, TestUInt8ManyConstruct)
{
    BUI8Many bits{157};

    EXPECT_EQ(bits.field1, 1);
    EXPECT_EQ(bits.field2, 0);
    EXPECT_EQ(bits.field3, 1);
    EXPECT_EQ(bits.field4, 1);
    EXPECT_EQ(bits.field5, 1);
    EXPECT_EQ(bits.field6, 0);
    EXPECT_EQ(bits.field7, 0);
    EXPECT_EQ(bits.field8, 1);
}

TEST(BITFIELD, TestUInt8ManyAssign)
{
    BUI8Many bits{};
    bits.field1 = 1;
    bits.field2 = 0;
    bits.field3 = 1;
    bits.field4 = 1;
    bits.field5 = 1;
    bits.field6 = 0;
    bits.field7 = 0;
    bits.field8 = 1;

    EXPECT_EQ(bits, 157);
}

struct BUI64Normal : public BitField<uint64_t>
{
    Field<0, 48> foo{};
    Field<48, 16> bar{};
};
static_assert(sizeof(BUI8Normal) == 1, "[[no_unique_address]] not optimising as expected.");

TEST(BITFIELD, TestUInt64Constructor)
{
    uint64_t underlying = (71ULL << 48) + 678934ULL;
    BUI64Normal bits{underlying};

    EXPECT_EQ(bits.foo, 678934);
    EXPECT_EQ(bits.bar, 71);
}

TEST(BITFIELD, TestUInt64Normal)
{
    BUI64Normal bits;
    bits.foo = 678934ULL;
    bits.bar = 71;

    EXPECT_EQ(static_cast<uint64_t>(bits), (71ULL << 48) + 678934ULL);
    EXPECT_EQ(bits.foo, 678934ULL);
    EXPECT_EQ(bits.bar, 71);
}


struct BUI64Whole : public BitField<uint64_t>
{
    Field<0, 64> foo{};
};

TEST(BITFIELD, TestUInt64Whole)
{
    BUI64Whole bits;
    bits.foo = 12479023097409273ULL;

    EXPECT_EQ(bits.foo, 12479023097409273ULL);
    EXPECT_EQ(bits, 12479023097409273ULL);
}

struct BUI64Overlap : public BitField<uint64_t>
{
    Field<0, 48> foo{};
    Field<16, 48> bar{};
};

TEST(BITFIELD, TestUInt64OverlapConstruct)
{
    uint64_t underlying = 2555933;
    BUI64Overlap bits{underlying};

    EXPECT_EQ(bits.foo, 2555933);
    EXPECT_EQ(bits.bar, 39);
}

TEST(BITFIELD, TestUInt64OverlapAssign)
{
    BUI64Overlap bits;
    bits.foo = 2555933;
    bits.bar = 39;

    uint64_t underlying = 2555933;
    EXPECT_EQ(bits, underlying);
    EXPECT_EQ(bits.foo, 2555933);
    EXPECT_EQ(bits.bar, 39);
}

struct BUI64Many : public BitField<uint64_t>
{
    Field<0, 1> field1{};
    Field<1, 1> field2{};
    Field<2, 1> field3{};
    Field<3, 1> field4{};
    Field<4, 1> field5{};
    Field<5, 1> field6{};
    Field<6, 1> field7{};
    Field<7, 1> field8{};
    Field<8, 1> field9{};
    Field<9, 1> field10{};
    Field<29, 1> field30{};
    Field<30, 1> field31{};
    Field<31, 1> field32{};
    Field<32, 1> field33{};
    Field<33, 1> field34{};
    Field<34, 1> field35{};
    Field<35, 1> field36{};
    Field<36, 1> field37{};
    Field<37, 1> field38{};
    Field<38, 1> field39{};
    Field<39, 1> field40{};
    Field<60, 1> field61{};
    Field<61, 1> field62{};
    Field<62, 1> field63{};
    Field<63, 1> field64{};
};

TEST(BITFIELD, TestUInt64ManyConstruct)
{
    BUI64Many bits{12297829382473034410ULL};

    EXPECT_EQ(bits.field1, 0);
    EXPECT_EQ(bits.field2, 1);
    EXPECT_EQ(bits.field3, 0);
    EXPECT_EQ(bits.field4, 1);
    EXPECT_EQ(bits.field5, 0);
    EXPECT_EQ(bits.field6, 1);
    EXPECT_EQ(bits.field7, 0);
    EXPECT_EQ(bits.field8, 1);
    EXPECT_EQ(bits.field9, 0);
    EXPECT_EQ(bits.field10, 1);
    EXPECT_EQ(bits.field30, 1);
    EXPECT_EQ(bits.field31, 0);
    EXPECT_EQ(bits.field32, 1);
    EXPECT_EQ(bits.field33, 0);
    EXPECT_EQ(bits.field34, 1);
    EXPECT_EQ(bits.field35, 0);
    EXPECT_EQ(bits.field36, 1);
    EXPECT_EQ(bits.field37, 0);
    EXPECT_EQ(bits.field38, 1);
    EXPECT_EQ(bits.field39, 0);
    EXPECT_EQ(bits.field40, 1);
    EXPECT_EQ(bits.field61, 0);
    EXPECT_EQ(bits.field62, 1);
    EXPECT_EQ(bits.field63, 0);
    EXPECT_EQ(bits.field64, 1);
}

TEST(BITFIELD, TestUInt64ManyAssign)
{
    BUI64Many bits{};
    bits.field1 = 1;
    bits.field2 = 0;
    bits.field3 = 1;
    bits.field4 = 1;
    bits.field5 = 1;
    bits.field6 = 0;
    bits.field7 = 0;
    bits.field8 = 1;
    bits.field61 = 1;
    bits.field62 = 1;
    bits.field63 = 1;
    bits.field64 = 1;

    EXPECT_EQ(static_cast<uint64_t>(bits), 17293822569102704797ULL);
}