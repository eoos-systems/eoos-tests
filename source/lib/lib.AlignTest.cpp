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
    Align<T> a;
    T v;
    return sizeof(a) == sizeof(v);
}

/**
 * @relates lib_AlignTest
 * @brief Tests sizeof types.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Get size of T and sizeof Align<T>.
 *
 * @b Assert:
 *      - Test size of types are equal to each other.
 */
TEST_F(lib_AlignTest, Sizeof)
{
    EXPECT_TRUE(testSizeof<int8_t>())   << "Fatal: Size of int8_t types are not equal";  
    EXPECT_TRUE(testSizeof<int16_t>())  << "Fatal: Size of int16_t types are not equal";
    EXPECT_TRUE(testSizeof<int32_t>())  << "Fatal: Size of int32_t types are not equal";
    EXPECT_TRUE(testSizeof<int64_t>())  << "Fatal: Size of int64_t types are not equal";
    EXPECT_TRUE(testSizeof<uint8_t>())  << "Fatal: Size of uint8_t types are not equal";
    EXPECT_TRUE(testSizeof<uint16_t>()) << "Fatal: Size of uint16_t types are not equal";
    EXPECT_TRUE(testSizeof<uint32_t>()) << "Fatal: Size of uint32_t types are not equal";
    EXPECT_TRUE(testSizeof<uint64_t>()) << "Fatal: Size of uint64_t types are not equal";
}
    
/**
 * @brief Tests sum of two variables of T types and Align<T> types.
 *
 * @tparam T Base type to test.
 * @param o1 A variable to sum.
 * @param o2 A variable to sum.
 * @return Comparation result. 
 */
template<typename T, typename R>
bool_t testSum(T const o1, T const o2)
{
    Align<T> const a1( o1 );
    Align<T> const a2( o2 );
    Align<R> const ares( a1 + a2 );
    R const ores( o1 + o2 );
    return ares == ores;
}

/**
 * @relates lib_AlignTest
 * @brief Tests sum of variables.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Sum two variables of T types and Align<T> types.
 *
 * @b Assert:
 *      - Test sums are equal to each other.
 */
TEST_F(lib_AlignTest, Sum)
{
    bool_t res( false );
    res = testSum<int8_t,int32_t>(-1,2);
    EXPECT_TRUE( res )  << "Fatal: Sums are not equal";
    res = testSum<int16_t,int32_t>(-1,2);
    EXPECT_TRUE( res ) << "Fatal: Sums are not equal";
    res = testSum<int32_t,int64_t>(-1,2);
    EXPECT_TRUE( res ) << "Fatal: Sums are not equal";
}

/**
 * @brief Tests sum of two variables of T types and Align<T> types.
 *
 * @tparam T Base type to test.
 * @param o1 A variable to sum.
 * @param o2 A variable to sum.
 * @return Comparation result. 
 */
template<typename T>
T getTypecast(T const o1)
{
    Align<T> const a1( o1 );
    T const c1( a1 );
    return c1;
}
    
/**
 * @relates lib_AlignTest
 * @brief Tests of typecast.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Sum two variables of T types and Align<T> types.
 *
 * @b Assert:
 *      - Test sums are equal to each other.
 */
TEST_F(lib_AlignTest, Typecast_int)
{
    {
        int8_t exp( 0x7F );
        int8_t act( getTypecast(exp) );
        EXPECT_EQ( act, exp ) << "Fatal: Type cast are not faild";
    }
    {
        uint8_t exp( 0x8F );
        uint8_t act( getTypecast(exp) );
        EXPECT_EQ( act, exp ) << "Fatal: Type cast are not faild";
    }
    {
        int16_t exp( 0x7FA5 );
        int16_t act( getTypecast(exp) );
        EXPECT_EQ( act, exp ) << "Fatal: Type cast are not faild";
    }
    {
        uint16_t exp( 0x8FA5 );
        uint16_t act( getTypecast(exp) );
        EXPECT_EQ( act, exp ) << "Fatal: Type cast are not faild";
    }
    {
        int32_t exp( 0x7FA5A5A5 );
        int32_t act( getTypecast(exp) );
        EXPECT_EQ( act, exp ) << "Fatal: Type cast are not faild";
    }
    {
        uint32_t exp( 0x8FA5A5A5 );
        uint32_t act( getTypecast(exp) );
        EXPECT_EQ( act, exp ) << "Fatal: Type cast are not faild";
    }

    {
        int64_t exp( 0x7FA5A5A5 );
        int64_t act( getTypecast(exp) );
        EXPECT_EQ( act, exp ) << "Fatal: Type cast are not faild";
    }
    {
        uint64_t exp( 0x8FA5A5A5 );
        uint64_t act( getTypecast(exp) );
        EXPECT_EQ( act, exp ) << "Fatal: Type cast are not faild";
    }    
}

/**
 * @relates lib_AlignTest
 * @brief Tests assignment.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct object.
 *
 * @b Assert:
 *      - Test for assignment.
 */
TEST_F(lib_AlignTest, operatorAssignment)
{
    {
        Align<uint32_t> a1;
        uint32_t const v2( 0x12345678 );
        a1 = v2;
        uint32_t const v1( a1 );
        EXPECT_EQ( v1, v2 ) << "Fatal: Value is not assigned";
    }
    {
        Align<uint32_t> a1;
        Align<uint32_t> const a2( 0x12345678 );
        a1 = a2;
        uint32_t const v1( a1 );
        uint32_t const v2( a2 );        
        EXPECT_EQ( v1, v2 ) << "Fatal: Value is not assigned";
    }    
}

/**
 * @relates lib_AlignTest
 * @brief Tests increment.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct object.
 *
 * @b Assert:
 *      - Test for increment.
 */
TEST_F(lib_AlignTest, operatorIncrement)
{
    {
        Align<uint32_t> a1( 0x12345678 );
        ++a1;
        uint32_t const v1( a1 );
        EXPECT_EQ( v1, 0x12345679 ) << "Fatal: Value is not assigned";
    }    
    {
        Align<uint32_t> a1( 0x12345678 );
        a1++;
        uint32_t const v1( a1 );
        EXPECT_EQ( v1, 0x12345679 ) << "Fatal: Value is not assigned";
    }    
}

/**
 * @relates lib_AlignTest
 * @brief Tests decrement.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct object.
 *
 * @b Assert:
 *      - Test for decrement.
 */
TEST_F(lib_AlignTest, operatorDecrement)
{
    {
        Align<uint32_t> a1( 0x12345678 );
        --a1;
        uint32_t const v1( a1 );
        EXPECT_EQ( v1, 0x12345677 ) << "Fatal: Value is not assigned";
    }    
    {
        Align<uint32_t> a1( 0x12345678 );
        a1--;
        uint32_t const v1( a1 );
        EXPECT_EQ( v1, 0x12345677 ) << "Fatal: Value is not assigned";
    }    
}

/**
 * @relates lib_AlignTest
 * @brief Tests comparison.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct two objects.
 *
 * @b Assert:
 *      - Test for comparison.
 */
TEST_F(lib_AlignTest, comparison)
{
    {
        Align<uint32_t> const a1( 0x12345678 );
        Align<uint32_t> const a2( 0x12345678 );
        EXPECT_TRUE( a1 == a2 ) << "Fatal: Values don't equal";
        EXPECT_FALSE( a1 != a2 ) << "Fatal: Values don't equal";        
    }
    {
        Align<uint32_t> const a1( 0x12345678 );
        Align<uint32_t> const a2( 0x78563412 );
        EXPECT_TRUE( a1 != a2 ) << "Fatal: Values equal";
        EXPECT_FALSE( a1 == a2 ) << "Fatal: Values equal";                
    }    
}
    
} // namespace lib
} // namespace eoos
