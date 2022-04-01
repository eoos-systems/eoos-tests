/**
 * @file      lib.AlignTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020-2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Align`. 
 */
#include "lib.Align.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{
    
/**
 * @class lib_AlignTest
 * @test Align
 * @brief Tests Align class functionality.
 */
class lib_AlignTest : public ::testing::Test
{

private:
    
    System eoos_; ///< EOOS Operating System.    
};

/**
 * @brief Tests size of T and size of lib::Align<T>.
 *
 * @tparam T Base type to test.
 * @return Comparation result. 
 */
template<typename T>
bool_t testSizeof()
{
    lib::Align<T> a;
    T v;
    return sizeof(a) == sizeof(v);
}

/**
 * @brief Tests sum of two variables of T types and lib::Align<T> types.
 *
 * @tparam T Base type to test.
 * @param o1 A variable to sum.
 * @param o2 A variable to sum.
 * @return Comparation result. 
 */
template<typename T, typename R>
bool_t testSum(T const o1, T const o2)
{
    lib::Align<T> const a1 {o1};
    lib::Align<T> const a2 {o2};
    lib::Align<R> const ares {a1 + a2};
    R const ores {o1 + o2};
    return ares == ores;
}

/**
 * @relates lib_AlignTest
 * @brief Tests sizeof types.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Get size of T and sizeof lib::Align<T>.
 *
 * @b Assert:
 *      - Test size of types are equal to each other.
 */
TEST_F(lib_AlignTest, Sizeof)
{
    EXPECT_TRUE(testSizeof<int8_t>())   << "Error: Size of int8_t types are not equal";  
    EXPECT_TRUE(testSizeof<int16_t>())  << "Error: Size of int16_t types are not equal";
    EXPECT_TRUE(testSizeof<int32_t>())  << "Error: Size of int32_t types are not equal";
    EXPECT_TRUE(testSizeof<int64_t>())  << "Error: Size of int64_t types are not equal";
    EXPECT_TRUE(testSizeof<uint8_t>())  << "Error: Size of uint8_t types are not equal";
    EXPECT_TRUE(testSizeof<uint16_t>()) << "Error: Size of uint16_t types are not equal";
    EXPECT_TRUE(testSizeof<uint32_t>()) << "Error: Size of uint32_t types are not equal";
    EXPECT_TRUE(testSizeof<uint64_t>()) << "Error: Size of uint64_t types are not equal";
}

/**
 * @relates lib_AlignTest
 * @brief Tests sum of variables.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Sum two variables of T types and lib::Align<T> types.
 *
 * @b Assert:
 *      - Test sums are equal to each other.
 */
TEST_F(lib_AlignTest, Sum)
{
    bool_t res {testSum<int8_t,int32_t>(-1,2)};
    EXPECT_TRUE( res )  << "Error: Sums are not equal";
    res = testSum<int16_t,int32_t>(-1,2);
    EXPECT_TRUE( res ) << "Error: Sums are not equal";
    res = testSum<int32_t,int64_t>(-1,2);
    EXPECT_TRUE( res ) << "Error: Sums are not equal";
}

} // namespace lib
} // namespace eoos
