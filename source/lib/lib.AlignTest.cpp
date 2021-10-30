/**
 * @file      lib.AlignTest.cpp
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
    
class AlignTest : public ::testing::Test
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

template<typename T, typename R>
void testSum(T const o1, T const o2)
{
    lib::Align<T> const a1 {o1};
    lib::Align<T> const a2 {o2};
    lib::Align<R> const ares {a1 + a2};
    R const ores {o1 + o2};
    EXPECT_TRUE(ares == ores);
}

TEST_F(AlignTest, Sizeof)
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

TEST_F(AlignTest, Sum)
{
    testSum<int8_t,int32_t>(-1,2);
    testSum<int16_t,int32_t>(-1,2);
    testSum<int32_t,int64_t>(-1,2);
}

} // namespace lib
} // namespace eoos
