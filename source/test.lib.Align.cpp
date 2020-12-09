/**
 * @brief Unit tests of `lib::Align`.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020, Sergey Baigudin, Baigudin Software
 */
#include "lib.Align.hpp"
#include "gtest/gtest.h"

namespace eoos
{
namespace lib
{
namespace test
{
    
template<typename T>
void testSizeof()
{
    lib::Align<T> a;
    T v;
    EXPECT_TRUE(sizeof(a) == sizeof(v));    
}
TEST(lib_Align, Sizeof)
{
    testSizeof<int8_t>();
    testSizeof<int16_t>();
    testSizeof<int32_t>();
    testSizeof<int64_t>();
    testSizeof<uint8_t>();
    testSizeof<uint16_t>();
    testSizeof<uint32_t>();
    testSizeof<uint64_t>();
}

template<typename T>
void testSum(T const o1, T const o2)
{
    lib::Align<T> const a1 {o1};
    lib::Align<T> const a2 {o2};
    lib::Align<T> const ar {a1 + a2};
    T const or {o1 + o2};
    EXPECT_TRUE(ar == or);
}
TEST(lib_Align, Sum)
{
    testSum<int8_t>(-1,2);
}

} // namespace test
} // namespace lib
} // namespace eoos
