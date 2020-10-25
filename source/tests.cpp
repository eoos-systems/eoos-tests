#include "gtest/gtest.h"

TEST(EoosCommonTest, ConstChar)
{
    const char* const expected {"Hello, World!"}; 
    const char* const actual {"Hello, World!"};
    EXPECT_STREQ(expected, actual);
}

TEST(EoosCommonTest, Int)
{
    int const expected {5};
    int actual {5};
    EXPECT_EQ(expected, actual);
}
