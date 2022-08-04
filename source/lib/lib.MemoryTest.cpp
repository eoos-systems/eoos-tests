/**
 * @file      lib.MemoryTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Memory`. 
 */
#include "lib.Memory.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{
    
/**
 * @class lib_MemoryTest
 * @test Memory
 * @brief Tests Memory class functionality.
 */
class lib_MemoryTest : public ::testing::Test
{
};    

/**
 * @relates lib_MemoryTest
 * @brief Tests memory copy operation.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass address of two variables.
 *
 * @b Assert:
 *      - Test value of the variables correct. 
 */
TEST_F(lib_MemoryTest, memcpy)
{
    const uint32_t VALUE( 0x89ABCDEF );
    void* res;
    uint32_t src;
    uint32_t dst;
    
    src = VALUE;
    dst = 0;
    res = Memory::memcpy(&dst, &src, sizeof(uint32_t));
    EXPECT_EQ(src, dst) << "Fatal: Memory is not copied";
    EXPECT_EQ(res, &dst) << "Fatal: Returned memory address is wrong";
    
    dst = VALUE;
    res = Memory::memcpy(&dst, NULLPTR, sizeof(uint32_t));
    EXPECT_EQ(dst, VALUE) << "Fatal: Memory is changed";
    EXPECT_EQ(res, NULLPTR) << "Fatal: Returned memory address is wrong";
    
    src =  VALUE;
    res = Memory::memcpy(NULLPTR, &src, sizeof(uint32_t));
    EXPECT_EQ(src, VALUE) << "Fatal: Memory is changed";
    EXPECT_EQ(res, NULLPTR) << "Fatal: Returned memory address is wrong";

    res = Memory::memcpy(NULLPTR, NULLPTR, sizeof(uint32_t));
    EXPECT_EQ(res, NULLPTR) << "Fatal: Returned memory address is wrong";   
    
    src = 0x11111111;
    dst = 0x22222222;
    res = Memory::memcpy(&dst, &src, 0);
    EXPECT_NE(src, dst) << "Fatal: Memory is copied";
    EXPECT_EQ(src, 0x11111111) << "Fatal: Source memory is wrong";
    EXPECT_EQ(dst, 0x22222222) << "Fatal: Destination memory is wrong";    
    EXPECT_EQ(res, &dst) << "Fatal: Returned memory address is wrong";
}

/**
 * @relates lib_MemoryTest
 * @brief Tests memory set operation.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass address of variables.
 *
 * @b Assert:
 *      - Test value of the variable correct. 
 */
TEST_F(lib_MemoryTest, memset)
{
    const uint32_t VALUE( 0x5A5A5A5A );
    void* res;
    uint32_t dst;
    
    dst = 0;
    res = Memory::memset(&dst, 0x5A, sizeof(uint32_t));
    EXPECT_EQ(dst, VALUE) << "Fatal: Memory is not copied";
    EXPECT_EQ(res, &dst) << "Fatal: Returned memory address is wrong";

    res = Memory::memset(NULLPTR, 0x5A, sizeof(uint32_t));
    EXPECT_EQ(res, NULLPTR) << "Fatal: Returned memory address is wrong";

    dst = 0x22222222;
    res = Memory::memset(&dst, 0x5A, 0);
    EXPECT_EQ(dst, 0x22222222) << "Fatal: Destination memory is wrong";    
    EXPECT_EQ(res, &dst) << "Fatal: Returned memory address is wrong";
}


/**
 * @relates lib_MemoryTest
 * @brief Tests C-string length.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass C-string.
 *
 * @b Assert:
 *      - Test length is correct. 
 */
TEST_F(lib_MemoryTest, strlen)
{
    size_t len(0);
    len = Memory::strlen("Hello, World!");
    EXPECT_EQ(len, 13) << "Fatal: C-string length is wrong";

    len = 0xFFFFFFFF;
    len = Memory::strlen("");
    EXPECT_EQ(len, 0) << "Fatal: C-string length is wrong";

    len = 0xFFFFFFFF;
    len = Memory::strlen(NULLPTR);
    EXPECT_EQ(len, 0) << "Fatal: C-string length is wrong";
}

/**
 * @relates lib_MemoryTest
 * @brief Tests C-string copy operation.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass address of two C-string.
 *
 * @b Assert:
 *      - Test C-string content is correct. 
 */
TEST_F(lib_MemoryTest, strcpy)
{
    char_t* res( NULLPTR );    
    char_t dst[64] = {'\0'};
    char_t src[64] = {'a','b','c','\0'};
    const char_t* const SRC( "Hello, World!" );
    
    res = Memory::strcpy(dst, SRC);
    EXPECT_STREQ(dst, SRC) << "Fatal: C-string is not copied";
    EXPECT_EQ(res, dst) << "Fatal: Returned C-string address is wrong";    

    res = Memory::strcpy(dst, src);
    EXPECT_STREQ(dst, "abc") << "Fatal: C-string is not copied";
    EXPECT_EQ(res, dst) << "Fatal: Returned C-string address is wrong";    

    res = Memory::strcpy(dst, SRC);
    res = Memory::strcpy(dst, NULLPTR);
    EXPECT_STREQ(dst, SRC) << "Fatal: C-string is changed";
    EXPECT_EQ(res, NULLPTR) << "Fatal: Returned C-string address is wrong";
    
    res = Memory::strcpy(NULLPTR, src);
    EXPECT_STREQ(src, "abc") << "Fatal: C-string is changed";
    EXPECT_EQ(res, NULLPTR) << "Fatal: Returned C-string address is wrong";

    res = Memory::strcpy(NULLPTR, NULLPTR);
    EXPECT_EQ(res, NULLPTR) << "Fatal: Returned C-string address is wrong";
}

/**
 * @relates lib_MemoryTest
 * @brief Tests C-string concatenation operation.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass address of two C-string.
 *
 * @b Assert:
 *      - Test C-string content is correct. 
 */
TEST_F(lib_MemoryTest, strcat)
{
    char_t* res( NULLPTR );    
    char_t dst[64] = {'a','b','c','\0'};
    char_t src[64] = {'d','e','f','\0'};
    
    res = Memory::strcat(dst, src);
    EXPECT_STREQ(dst, "abcdef") << "Fatal: C-string is not copied";
    EXPECT_EQ(res, dst) << "Fatal: Returned C-string address is wrong";    

    res = Memory::strcpy(dst, "abc");
    res = Memory::strcat(dst, NULLPTR);
    EXPECT_STREQ(dst, "abc") << "Fatal: C-string is changed";
    EXPECT_EQ(res, NULLPTR) << "Fatal: Returned C-string address is wrong";
    
    res = Memory::strcat(NULLPTR, src);
    EXPECT_STREQ(src, "def") << "Fatal: C-string is changed";
    EXPECT_EQ(res, NULLPTR) << "Fatal: Returned C-string address is wrong";

    res = Memory::strcat(NULLPTR, NULLPTR);
    EXPECT_EQ(res, NULLPTR) << "Fatal: Returned C-string address is wrong";
}

/**
 * @relates lib_MemoryTest
 * @brief Tests C-string comparison operation.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass address of two C-string.
 *
 * @b Assert:
 *      - Test C-string content is similar. 
 */
TEST_F(lib_MemoryTest, strcmp)
{    
    int32_t res( -1 );
    res = Memory::strcmp("abc", "abc");
    EXPECT_EQ(res, 0) << "Fatal: C-strings are not similar";

    res = Memory::strcmp("abc", "abcd");
    EXPECT_LT(res, 0) << "Fatal: C-string1 are not shorter than the string 2";    

    res = Memory::strcmp("abC", "abc");
    EXPECT_LT(res, 0) << "Fatal: C-string1 are not shorter than the string 2";    

    res = Memory::strcmp("abcd", "abc");
    EXPECT_GT(res, 0) << "Fatal: C-string1 are not longer than the string 2";    

    res = Memory::strcmp("abc", "abC");
    EXPECT_GT(res, 0) << "Fatal: C-string1 are not longer than the string 2";    

    res = Memory::strcmp(NULLPTR, "abc");
    EXPECT_EQ(res, static_cast<int32_t>( 0x80000000U )) << "Fatal: No errors detected";    

    res = Memory::strcmp("abc", NULLPTR);
    EXPECT_EQ(res, static_cast<int32_t>( 0x80000000U )) << "Fatal: No errors detected";    

    res = Memory::strcmp(NULLPTR, NULLPTR);
    EXPECT_EQ(res, static_cast<int32_t>( 0x80000000U )) << "Fatal: No errors detected";    
}

/**
 * @relates lib_MemoryTest
 * @brief Tests convertion integer to C-string.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass integer.
 *
 * @b Assert:
 *      - Test number in C-string is compare. 
 */
TEST_F(lib_MemoryTest, itoa_int8)
{
    char_t str[256] = {'\0'};
    bool_t res( false );

    int8_t val( 0 );
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "0") << "Fatal: C-string is wrong";    

    val = 1;
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "1") << "Fatal: C-string is wrong";    

    val = -1;
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "-1") << "Fatal: C-string is wrong";    

    val = 0x7A;
    res = Memory::itoa(val, str, Number::BASE_16);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "7a") << "Fatal: C-string is wrong";    

    val = 127;
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "127") << "Fatal: C-string is wrong";    
    res = Memory::itoa(val, str, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "7f") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "177") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "1111111") << "Fatal: C-string is wrong";

    val = -127;
    res = Memory::itoa(val, str, Number::BASE_10);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "-127") << "Fatal: C-string is wrong";
    
    val = 123;
    res = Memory::itoa(val, str, static_cast<Number::Base>(32));
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";        

    // Test the Exception 1
    val = -128;
    res = Memory::itoa(val, str, Number::BASE_10);
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";
   
    // Test the Exception 2
    val = -127;    
    res = Memory::itoa(val, str, Number::BASE_16);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_8);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_2);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";
}

/**
 * @relates lib_MemoryTest
 * @brief Tests convertion integer to C-string.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass integer.
 *
 * @b Assert:
 *      - Test number in C-string is compare. 
 */
TEST_F(lib_MemoryTest, itoa_uint8)
{
    char_t str[256] = {'\0'};
    bool_t res( false );

    uint8_t val( 0 );
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "0") << "Fatal: C-string is wrong";    

    val = 1;
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "1") << "Fatal: C-string is wrong";    

    val = 0xAB;
    res = Memory::itoa(val, str, Number::BASE_16);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "ab") << "Fatal: C-string is wrong";    

    val = 127;
    res = Memory::itoa(val, str);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "127") << "Fatal: C-string is wrong";    
    res = Memory::itoa(val, str, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "7f") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "177") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "1111111") << "Fatal: C-string is wrong";

    val = 255;
    res = Memory::itoa(val, str, Number::BASE_10);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "255") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "ff") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "377") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "11111111") << "Fatal: C-string is wrong";

    val = 123;
    res = Memory::itoa(val, str, static_cast<Number::Base>(32));
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";        
}

/**
 * @relates lib_MemoryTest
 * @brief Tests convertion integer to C-string.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass integer.
 *
 * @b Assert:
 *      - Test number in C-string is compare. 
 */
TEST_F(lib_MemoryTest, itoa_int16)
{
    char_t str[256] = {'\0'};
    bool_t res( false );

    int16_t val( 0 );
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "0") << "Fatal: C-string is wrong";    

    val = 1;
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "1") << "Fatal: C-string is wrong";    

    val = -1;
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "-1") << "Fatal: C-string is wrong";    

    val = 0x7ABC;
    res = Memory::itoa(val, str, Number::BASE_16);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "7abc") << "Fatal: C-string is wrong";    

    val = 32767;
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "32767") << "Fatal: C-string is wrong";    
    res = Memory::itoa(val, str, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "7fff") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "77777") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "111111111111111") << "Fatal: C-string is wrong";

    val = -32767;
    res = Memory::itoa(val, str, Number::BASE_10);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "-32767") << "Fatal: C-string is wrong";
    
    val = 123;
    res = Memory::itoa(val, str, static_cast<Number::Base>(32));
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";        

    // Test the Exception 1
    val = -32768;
    res = Memory::itoa(val, str, Number::BASE_10);
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";
   
    // Test the Exception 2
    val = -32767;    
    res = Memory::itoa(val, str, Number::BASE_16);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_8);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_2);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";
}

/**
 * @relates lib_MemoryTest
 * @brief Tests convertion integer to C-string.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass integer.
 *
 * @b Assert:
 *      - Test number in C-string is compare. 
 */
TEST_F(lib_MemoryTest, itoa_uint16)
{
    char_t str[256] = {'\0'};
    bool_t res( false );

    uint16_t val( 0 );
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "0") << "Fatal: C-string is wrong";    

    val = 1;
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "1") << "Fatal: C-string is wrong";    

    val = 0xABCD;
    res = Memory::itoa(val, str, Number::BASE_16);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "abcd") << "Fatal: C-string is wrong";    

    val = 32767;
    res = Memory::itoa(val, str);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "32767") << "Fatal: C-string is wrong";    
    res = Memory::itoa(val, str, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "7fff") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "77777") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "111111111111111") << "Fatal: C-string is wrong";

    val = 65535;
    res = Memory::itoa(val, str, Number::BASE_10);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "65535") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "ffff") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "177777") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "1111111111111111") << "Fatal: C-string is wrong";

    val = 123;
    res = Memory::itoa(val, str, static_cast<Number::Base>(32));
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";        
}

/**
 * @relates lib_MemoryTest
 * @brief Tests convertion integer to C-string.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass integer.
 *
 * @b Assert:
 *      - Test number in C-string is compare. 
 */
TEST_F(lib_MemoryTest, itoa_int32)
{
    char_t str[256] = {'\0'};
    bool_t res( false );

    int32_t val( 0 );
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "0") << "Fatal: C-string is wrong";    

    val = 1;
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "1") << "Fatal: C-string is wrong";    

    val = -1;
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "-1") << "Fatal: C-string is wrong";    

    val = 0x00ABCDEF;
    res = Memory::itoa(val, str, Number::BASE_16);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "abcdef") << "Fatal: C-string is wrong";    

    val = 2147483647;
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "2147483647") << "Fatal: C-string is wrong";    
    res = Memory::itoa(val, str, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "7fffffff") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "17777777777") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "1111111111111111111111111111111") << "Fatal: C-string is wrong";

    val = -2147483647;
    res = Memory::itoa(val, str, Number::BASE_10);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "-2147483647") << "Fatal: C-string is wrong";
    
    val = 123;
    res = Memory::itoa(val, str, static_cast<Number::Base>(32));
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";        

    // Test the Exception 1
    val = -2147483648;
    res = Memory::itoa(val, str, Number::BASE_10);
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";
   
    // Test the Exception 2
    val = -2147483647;    
    res = Memory::itoa(val, str, Number::BASE_16);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_8);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_2);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";
}

/**
 * @relates lib_MemoryTest
 * @brief Tests convertion integer to C-string.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass integer.
 *
 * @b Assert:
 *      - Test number in C-string is compare. 
 */
TEST_F(lib_MemoryTest, itoa_uint32)
{
    char_t str[256] = {'\0'};
    bool_t res( false );

    uint32_t val( 0 );
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "0") << "Fatal: C-string is wrong";    

    val = 1;
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "1") << "Fatal: C-string is wrong";    

    val = 0x89ABCDEF;
    res = Memory::itoa(val, str, Number::BASE_16);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "89abcdef") << "Fatal: C-string is wrong";    

    val = 2147483647;
    res = Memory::itoa(val, str);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "2147483647") << "Fatal: C-string is wrong";    
    res = Memory::itoa(val, str, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "7fffffff") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "17777777777") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "1111111111111111111111111111111") << "Fatal: C-string is wrong";

    val = 4294967295;
    res = Memory::itoa(val, str, Number::BASE_10);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "4294967295") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "ffffffff") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "37777777777") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "11111111111111111111111111111111") << "Fatal: C-string is wrong";

    val = 123;
    res = Memory::itoa(val, str, static_cast<Number::Base>(32));
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";        
}

/**
 * @relates lib_MemoryTest
 * @brief Tests convertion integer to C-string.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass integer.
 *
 * @b Assert:
 *      - Test number in C-string is compare. 
 */
TEST_F(lib_MemoryTest, itoa_int64)
{
    char_t str[256] = {'\0'};
    bool_t res( false );

    int64_t val( 0LL );
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "0") << "Fatal: C-string is wrong";    

    val = 1LL;
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "1") << "Fatal: C-string is wrong";    

    val = -1LL;
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "-1") << "Fatal: C-string is wrong";    

    val = 0x1234567890ABCDEFLL;
    res = Memory::itoa(val, str, Number::BASE_16);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "1234567890abcdef") << "Fatal: C-string is wrong";    

    val = 9223372036854775807LL;
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "9223372036854775807") << "Fatal: C-string is wrong";    
    res = Memory::itoa(val, str, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "7fffffffffffffff") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "777777777777777777777") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "111111111111111111111111111111111111111111111111111111111111111") << "Fatal: C-string is wrong";

    val = -9223372036854775807LL;
    res = Memory::itoa(val, str, Number::BASE_10);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "-9223372036854775807") << "Fatal: C-string is wrong";
    
    val = 123;
    res = Memory::itoa(val, str, static_cast<Number::Base>(32));
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";        

    // Test the Exception 1
    val = -9223372036854775807LL - 1LL;
    res = Memory::itoa(val, str, Number::BASE_10);
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";
   
    // Test the Exception 2
    val = -9223372036854775807LL;
    res = Memory::itoa(val, str, Number::BASE_16);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_8);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_2);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";
}

/**
 * @relates lib_MemoryTest
 * @brief Tests convertion integer to C-string.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass integer.
 *
 * @b Assert:
 *      - Test number in C-string is compare. 
 */
TEST_F(lib_MemoryTest, itoa_uint64)
{
    char_t str[256] = {'\0'};
    bool_t res( false );

    uint64_t val( 0ULL );
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "0") << "Fatal: C-string is wrong";    

    val = 1ULL;
    res = Memory::itoa(val, str, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "1") << "Fatal: C-string is wrong";    

    val = 0x00ABCDEFULL;
    res = Memory::itoa(val, str, Number::BASE_16);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "abcdef") << "Fatal: C-string is wrong";    

    val = 9223372036854775807ULL;
    res = Memory::itoa(val, str);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "9223372036854775807") << "Fatal: C-string is wrong";    
    res = Memory::itoa(val, str, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "7fffffffffffffff") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "777777777777777777777") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "111111111111111111111111111111111111111111111111111111111111111") << "Fatal: C-string is wrong";

    val = 18446744073709551615ULL;
    res = Memory::itoa(val, str, Number::BASE_10);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "18446744073709551615") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "ffffffffffffffff") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "1777777777777777777777") << "Fatal: C-string is wrong";
    res = Memory::itoa(val, str, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "1111111111111111111111111111111111111111111111111111111111111111") << "Fatal: C-string is wrong";

    val = 123ULL;
    res = Memory::itoa(val, str, static_cast<Number::Base>(32));
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(str, "") << "Fatal: C-string is wrong";        
}

/**
 * @relates lib_MemoryTest
 * @brief Tests convertion C-string to integer.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass C-string.
 *
 * @b Assert:
 *      - Test integer is compare. 
 */
TEST_F(lib_MemoryTest, atoi)
{
    int32_t val( 0 );
    
    val = Memory::atoi<int32_t>("0", Number::BASE_10);
    EXPECT_EQ(val, 0) << "Fatal: Value is wrong";

    val = Memory::atoi<int32_t>("1", Number::BASE_10);
    EXPECT_EQ(val, 1) << "Fatal: Value is wrong";
    
    val = Memory::atoi<int32_t>("-1", Number::BASE_10);
    EXPECT_EQ(val, -1) << "Fatal: Value is wrong";        

    val = Memory::atoi<int32_t>("2147483647", Number::BASE_10);
    EXPECT_EQ(val, 2147483647) << "Fatal: Value is wrong";

    val = Memory::atoi<int32_t>("+2147483647", Number::BASE_10);
    EXPECT_EQ(val, 2147483647) << "Fatal: Value is wrong";

    val = Memory::atoi<int32_t>("-2147483648", Number::BASE_10);
    EXPECT_EQ(val, -2147483648) << "Fatal: Value is wrong";        

    val = Memory::atoi<int32_t>("\t\n\v\f\r +214748y3647", Number::BASE_10);
    EXPECT_EQ(val, 214748) << "Fatal: Value is wrong";

    val = Memory::atoi<int32_t>("1010101111001101111011110001", Number::BASE_2);
    EXPECT_EQ(val, 0xABCDEF1) << "Fatal: Value is wrong";
    val = Memory::atoi<int32_t>("00001010101111001101111011110001", Number::BASE_2);
    EXPECT_EQ(val, 0xABCDEF1) << "Fatal: Value is wrong";

    val = Memory::atoi<int32_t>("1257157361", Number::BASE_8);
    EXPECT_EQ(val, 0xABCDEF1) << "Fatal: Value is wrong";
    val = Memory::atoi<int32_t>("001257157361", Number::BASE_8);
    EXPECT_EQ(val, 0xABCDEF1) << "Fatal: Value is wrong";

    val = Memory::atoi<int32_t>("180150001");
    EXPECT_EQ(val, 0xABCDEF1) << "Fatal: Value is wrong";
    val = Memory::atoi<int32_t>("00180150001");
    EXPECT_EQ(val, 0xABCDEF1) << "Fatal: Value is wrong";

    val = Memory::atoi<int32_t>("ABCDEF1", Number::BASE_16);
    EXPECT_EQ(val, 0xABCDEF1) << "Fatal: Value is wrong";
    val = Memory::atoi<int32_t>("00ABCDEF1", Number::BASE_16);
    EXPECT_EQ(val, 0xABCDEF1) << "Fatal: Value is wrong";

    val = Memory::atoi<int32_t>("abcdef1", Number::BASE_16);
    EXPECT_EQ(val, 0xABCDEF1) << "Fatal: Value is wrong";
    val = Memory::atoi<int32_t>("00abcdef1", Number::BASE_16);
    EXPECT_EQ(val, 0xABCDEF1) << "Fatal: Value is wrong";

    val = Memory::atoi<int32_t>("123", static_cast<Number::Base>(32));
    EXPECT_EQ(val, 0) << "Fatal: Value is wrong";        
}

} // namespace lib
} // namespace eoos
