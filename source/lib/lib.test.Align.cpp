/**
 * @file      lib.test.Align.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020-2021, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Align`. 
 */
#include "System.hpp"
#include "lib.Align.hpp"

namespace eoos
{
namespace lib
{
namespace test
{
    
class test_lib_Align : public ::testing::Test
{

protected:
    
    System eoos;    
};
    
    
template<typename T>
void testSizeof()
{
    lib::Align<T> a;
    T v;
    EXPECT_TRUE(sizeof(a) == sizeof(v));    
}

template<typename T>
void testSum(T const o1, T const o2)
{
    lib::Align<T> const a1 {o1};
    lib::Align<T> const a2 {o2};
    lib::Align<T> const ares {a1 + a2};
    T const ores {o1 + o2};
    EXPECT_TRUE(ares == ores);
}

TEST_F(test_lib_Align, Sizeof)
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

TEST_F(test_lib_Align, Sum)
{
    testSum<int8_t>(-1,2);
}

} // namespace test
} // namespace lib
} // namespace eoos
