/**
 * @file      lib.BaseStringDynamicTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020-2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::BaseString<char_t,0>`. 
 */
#include "lib.String.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{
    
/**
 * @class lib_BaseStringDynamicTest_char_t
 * @test String
 * @brief Tests String class functionality.
 */
class lib_BaseStringDynamicTest_char_t : public ::testing::Test
{

private:
    
    System eoos_; ///< EOOS Operating System.    
};

namespace
{

const char_t* const ALPHABET( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" );

/**
 * @class TestBaseString<T,0>
 *
 * @brief Class to provide protect functions to public scope.
 */
template <typename T>
class TestBaseString : public BaseString<T,0>
{
    typedef BaseString<T,0> Parent;

public:

    TestBaseString()
        : BaseString<T,0>() {
    }

    TestBaseString(T const* const source)
        : BaseString<T,0>(source) {
    }

    TestBaseString(BaseString<T,0> const& source)
        : BaseString<T,0>(source) {
    }

    void setConstructed(bool_t const flag)
    {
        Parent::setConstructed(flag);
    }    
};

/**
 * @class Test String
 * @brief Test String type for chars with default allocator.
 *
 * The dynamic string for any numbers of characters with a default allocator
 * used to allocate an internal container to contain the characters
 */
typedef TestBaseString<char_t> TestString;

} // namespace

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests the class constructor.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is constructed.
 */
TEST_F(lib_BaseStringDynamicTest_char_t, Constructor)
{
    {
        String const obj;
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: String is not constructed";
    }
    {
        String const obj( "ABC" );
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: String is not constructed";
    }
    {
        String const obj( 1234567890 );
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: String is not constructed";
    }
    {
        String const obj( 1234567890, Number::BASE_2 );
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: String is not constructed";
    }
    {
        String const obj( 12345678, Number::BASE_8 );
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: String is not constructed";
    }
    {
        String const obj( 12345678, Number::BASE_10 );
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: String is not constructed";
    }
    {
        String const obj( 12345678, Number::BASE_16 );
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: String is not constructed";
    }
    {
        String const obj( 12345678, static_cast<Number::Base>(32) );
        EXPECT_FALSE(obj.isConstructed()) << "Fatal: String is constructed";
    }    
    {
        String const tmp( "ABC" );
        api::String<char_t> const& itmp( tmp );
        String const obj( itmp );
        EXPECT_TRUE(tmp.isConstructed()) << "Fatal: String is not constructed";
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: String is not constructed";        
    }    
    {
        String const tmp( "ABC" );
        String const obj( tmp );
        EXPECT_TRUE(tmp.isConstructed()) << "Fatal: String is not constructed";        
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: String is not constructed";
    }
    {
        BaseString<char_t,0,CharTrait<char_t>,NullAllocator> const obj( "ABC" );
        EXPECT_FALSE(obj.isConstructed()) << "Fatal: String is constructed";
    }
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests copy constructor.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class with user defined construct.
 *      - Consctuct an object of the class with copy construct. 
 *
 * @b Assert:
 *      - Test the objects are constructed.
 */
TEST_F(lib_BaseStringDynamicTest_char_t, CopyConstructor)
{
    {
        String const tmp( ALPHABET );
        String const obj( tmp );
        EXPECT_TRUE(tmp.isConstructed())      << "Fatal: String is not constructed";
        EXPECT_STREQ(tmp.getChar(), ALPHABET) << "Fatal: String has wrong characters";
        EXPECT_EQ(tmp.getLength(), 26)        << "Fatal: String has wrong length";
        EXPECT_FALSE(tmp.isEmpty())           << "Fatal: String is empty";                                
        EXPECT_TRUE(obj.isConstructed())      << "Fatal: String is not constructed";
        EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String has wrong characters";
        EXPECT_EQ(obj.getLength(), 26)        << "Fatal: String has wrong length";
        EXPECT_FALSE(obj.isEmpty())           << "Fatal: String is empty";                        
        EXPECT_NE(obj.getChar(), tmp.getChar()) << "Fatal: String addresses are the same";        
    }
    {
        TestString tmp( ALPHABET );
        tmp.setConstructed(false);
        String const obj( tmp );
        EXPECT_FALSE(tmp.isConstructed())    << "Fatal: String is constructed";
        EXPECT_STREQ(tmp.getChar(), NULLPTR) << "Fatal: String is not null";
        EXPECT_EQ(tmp.getLength(), 0)        << "Fatal: String length is not 0";
        EXPECT_TRUE(tmp.isEmpty())           << "Fatal: String is not empty";
        EXPECT_FALSE(obj.isConstructed())    << "Fatal: String is constructed";
        EXPECT_STREQ(obj.getChar(), NULLPTR) << "Fatal: String is not null";
        EXPECT_EQ(obj.getLength(), 0)        << "Fatal: String length is not 0";
        EXPECT_TRUE(obj.isEmpty())           << "Fatal: String is not empty";
    }
    {
        String const tmp( ALPHABET );
        TestString obj( tmp );
        obj.setConstructed(false);        
        EXPECT_TRUE(tmp.isConstructed())      << "Fatal: String is not constructed";
        EXPECT_STREQ(tmp.getChar(), ALPHABET) << "Fatal: String has wrong characters";
        EXPECT_EQ(tmp.getLength(), 26)        << "Fatal: String has wrong length";
        EXPECT_FALSE(tmp.isEmpty())           << "Fatal: String is empty";                                
        EXPECT_FALSE(obj.isConstructed())     << "Fatal: String is constructed";
        EXPECT_STREQ(obj.getChar(), NULLPTR)  << "Fatal: String is not null";
        EXPECT_EQ(obj.getLength(), 0)         << "Fatal: String length is not 0";
        EXPECT_TRUE(obj.isEmpty())            << "Fatal: String is not empty";
    }
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Test copy assignment.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct an object 1, 2, and 3.
 *      - Assign the object 1 to the object 2.
 *      - Assign the object 1 to the object 3. 
 *
 * @b Assert:
 *      - Test the objects are constructed.
 *      - Test the pointer are correct. 
 */
TEST_F(lib_BaseStringDynamicTest_char_t, CopyAssignment)
{
    {
        String const obj1( ALPHABET );
        String obj2;
        String obj3( "ABCDEFGHIJKLM" );        
        obj2 = obj1;
        obj3 = obj1;

        EXPECT_TRUE(obj1.isConstructed())      << "Fatal: String is not constructed";
        EXPECT_STREQ(obj1.getChar(), ALPHABET) << "Fatal: String has wrong characters";
        EXPECT_EQ(obj1.getLength(), 26)        << "Fatal: String has wrong length";
        EXPECT_FALSE(obj1.isEmpty())           << "Fatal: String is empty";

        EXPECT_TRUE(obj2.isConstructed())      << "Fatal: String is not constructed";
        EXPECT_STREQ(obj2.getChar(), ALPHABET) << "Fatal: String has wrong characters";
        EXPECT_EQ(obj2.getLength(), 26)        << "Fatal: String has wrong length";
        EXPECT_FALSE(obj2.isEmpty())           << "Fatal: String is empty";

        EXPECT_TRUE(obj3.isConstructed())      << "Fatal: String is not constructed";
        EXPECT_STREQ(obj3.getChar(), ALPHABET) << "Fatal: String has wrong characters";
        EXPECT_EQ(obj3.getLength(), 26)        << "Fatal: String has wrong length";
        EXPECT_FALSE(obj3.isEmpty())           << "Fatal: String is empty";

        EXPECT_NE(obj1.getChar(), obj2.getChar()) << "Fatal: String addresses are the same";
        EXPECT_NE(obj1.getChar(), obj3.getChar()) << "Fatal: String addresses are the same";
    }    
    {
        TestString obj1( ALPHABET );
        obj1.setConstructed(false);
        String obj2;
        obj2 = obj1;
        EXPECT_FALSE(obj1.isConstructed())    << "Fatal: String is constructed";
        EXPECT_STREQ(obj1.getChar(), NULLPTR) << "Fatal: String is not null";
        EXPECT_EQ(obj1.getLength(), 0)        << "Fatal: String length is not 0";
        EXPECT_TRUE(obj1.isEmpty())           << "Fatal: String is not empty";
        EXPECT_FALSE(obj2.isConstructed())    << "Fatal: String is constructed";
        EXPECT_STREQ(obj2.getChar(), NULLPTR) << "Fatal: String is not null";
        EXPECT_EQ(obj2.getLength(), 0)        << "Fatal: String length is not 0";
        EXPECT_TRUE(obj2.isEmpty())           << "Fatal: String is not empty";
    }
    {
        String obj1( ALPHABET );
        TestString obj2;
        obj2.setConstructed(false);
        obj2 = obj1;
        EXPECT_TRUE(obj1.isConstructed())      << "Fatal: String is not constructed";
        EXPECT_STREQ(obj1.getChar(), ALPHABET) << "Fatal: String has wrong characters";
        EXPECT_EQ(obj1.getLength(), 26)        << "Fatal: String has wrong length";
        EXPECT_FALSE(obj1.isEmpty())           << "Fatal: String is empty";
        EXPECT_FALSE(obj2.isConstructed())     << "Fatal: String is constructed";
        EXPECT_STREQ(obj2.getChar(), NULLPTR)  << "Fatal: String is not null";
        EXPECT_EQ(obj2.getLength(), 0)         << "Fatal: String length is not 0";
        EXPECT_TRUE(obj2.isEmpty())            << "Fatal: String is not empty";
    }
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests move constructor.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct an object 2 with casting an object 1.
 *
 * @b Assert:
 *      - Test the object 2 is constructed.
 *      - Test the object 1 is not constructed after the casting.
 */
TEST_F(lib_BaseStringDynamicTest_char_t, MoveConstructor)
{
    {
        String tmp( ALPHABET );
        String obj( move(tmp) );
        EXPECT_FALSE(tmp.isConstructed())     << "Fatal: String is constructed";
        EXPECT_STREQ(tmp.getChar(), NULLPTR)  << "Fatal: String is not null";
        EXPECT_EQ(tmp.getLength(), 0)         << "Fatal: String has wrong length";
        EXPECT_TRUE(tmp.isEmpty())            << "Fatal: String is not empty";
        EXPECT_TRUE(obj.isConstructed())      << "Fatal: String is not constructed";
        EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String has wrong characters";
        EXPECT_EQ(obj.getLength(), 26)        << "Fatal: String has wrong length";
        EXPECT_FALSE(obj.isEmpty())           << "Fatal: String is empty";                        
    }
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Test move assignment.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct objects.
 *      - Move assign objects to objects using NRVO and casting.
 *
 * @b Assert:
 *      - Test new objects are constructed.
 *      - Test released objects are not constructed.
 */
TEST_F(lib_BaseStringDynamicTest_char_t, MoveAssignment)
{
    {
        String tmp( ALPHABET );
        String obj;
        obj = move(tmp);
        EXPECT_FALSE(tmp.isConstructed())     << "Fatal: String is constructed";
        EXPECT_STREQ(tmp.getChar(), NULLPTR)  << "Fatal: String is not null";
        EXPECT_EQ(tmp.getLength(), 0)         << "Fatal: String has wrong length";
        EXPECT_TRUE(tmp.isEmpty())            << "Fatal: String is not empty";
        EXPECT_TRUE(obj.isConstructed())      << "Fatal: String is not constructed";
        EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String has wrong characters";
        EXPECT_EQ(obj.getLength(), 26)        << "Fatal: String has wrong length";
        EXPECT_FALSE(obj.isEmpty())           << "Fatal: String is empty";                        
    }
    {       
        String tmp( ALPHABET );
        String obj( "ABCDEFGHIJKLM" );
        obj = move(tmp);
        EXPECT_FALSE(tmp.isConstructed())     << "Fatal: String is constructed";
        EXPECT_STREQ(tmp.getChar(), NULLPTR)  << "Fatal: String is not null";
        EXPECT_EQ(tmp.getLength(), 0)         << "Fatal: String has wrong length";
        EXPECT_TRUE(tmp.isEmpty())            << "Fatal: String is not empty";
        EXPECT_TRUE(obj.isConstructed())      << "Fatal: String is not constructed";
        EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String has wrong characters";
        EXPECT_EQ(obj.getLength(), 26)        << "Fatal: String has wrong length";
        EXPECT_FALSE(obj.isEmpty())           << "Fatal: String is empty";                        
    }
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests the class string states.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_BaseStringDynamicTest_char_t, getChar_getLength_isEmpty)
{
    {
        String const obj;
        ASSERT_NE(obj.getChar(), NULLPTR) << "Fatal: String is null";
        EXPECT_STREQ(obj.getChar(), "")   << "Fatal: String has wrong characters";
        EXPECT_EQ(obj.getLength(), 0)     << "Fatal: String has wrong length";
        EXPECT_TRUE(obj.isEmpty())        << "Fatal: String is not empty";        
    }
    {
        String const obj( "ABC" );
        ASSERT_NE(obj.getChar(), NULLPTR)  << "Fatal: C-String is null";
        EXPECT_STREQ(obj.getChar(), "ABC") << "Fatal: String has wrong characters";
        EXPECT_EQ(obj.getLength(), 3)      << "Fatal: String has wrong length";
        EXPECT_FALSE(obj.isEmpty())        << "Fatal: String is empty";                        
    }
    {
        String const obj( ALPHABET );
        ASSERT_NE(obj.getChar(), NULLPTR)     << "Fatal: C-String is null";
        EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String has wrong characters";
        EXPECT_EQ(obj.getLength(), 26)        << "Fatal: String has wrong length";
        EXPECT_FALSE(obj.isEmpty())           << "Fatal: String is empty";                        
    }
    {
        String const obj( 1234567890 );
        ASSERT_NE(obj.getChar(), NULLPTR)         << "Fatal: C-String is null";
        EXPECT_STREQ(obj.getChar(), "1234567890") << "Fatal: String has wrong characters";
        EXPECT_EQ(obj.getLength(), 10)            << "Fatal: String has wrong length";
        EXPECT_FALSE(obj.isEmpty())               << "Fatal: String is empty";                        
    }    
    {
        String const obj( 2147483647, Number::BASE_2 );
        ASSERT_NE(obj.getChar(), NULLPTR)         << "Fatal: C-String is null";
        EXPECT_STREQ(obj.getChar(), "1111111111111111111111111111111") << "Fatal: String has wrong characters";
        EXPECT_EQ(obj.getLength(), 31)            << "Fatal: String has wrong length";
        EXPECT_FALSE(obj.isEmpty())               << "Fatal: String is empty";                        
    }
    {
        String const obj( 2147483647, Number::BASE_8 );
        ASSERT_NE(obj.getChar(), NULLPTR)          << "Fatal: C-String is null";
        EXPECT_STREQ(obj.getChar(), "17777777777") << "Fatal: String has wrong characters";
        EXPECT_EQ(obj.getLength(), 11)             << "Fatal: String has wrong length";
        EXPECT_FALSE(obj.isEmpty())                << "Fatal: String is empty";                        
    }
    {
        String const obj( 2147483647, Number::BASE_10 );
        ASSERT_NE(obj.getChar(), NULLPTR)         << "Fatal: C-String is null";
        EXPECT_STREQ(obj.getChar(), "2147483647") << "Fatal: String has wrong characters";
        EXPECT_EQ(obj.getLength(), 10)            << "Fatal: String has wrong length";
        EXPECT_FALSE(obj.isEmpty())               << "Fatal: String is empty";                        
    }
    {
        String const obj( 2147483647, Number::BASE_16 );
        ASSERT_NE(obj.getChar(), NULLPTR)       << "Fatal: C-String is null";
        EXPECT_STREQ(obj.getChar(), "7fffffff") << "Fatal: String has wrong characters";
        EXPECT_EQ(obj.getLength(), 8)           << "Fatal: String has wrong length";
        EXPECT_FALSE(obj.isEmpty())             << "Fatal: String is empty";                        
    }
    {
        String const tmp( ALPHABET );
        api::String<char_t> const& itmp( tmp );
        String const obj( itmp );
        ASSERT_NE(obj.getChar(), NULLPTR)     << "Fatal: C-String is null";
        EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String has wrong characters";
        EXPECT_EQ(obj.getLength(), 26)        << "Fatal: String has wrong length";
        EXPECT_FALSE(obj.isEmpty())           << "Fatal: String is empty";                        
    }
    {
        String const tmp( ALPHABET );
        String const obj( tmp );
        ASSERT_NE(obj.getChar(), NULLPTR)     << "Fatal: C-String is null";
        EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String has wrong characters";
        EXPECT_EQ(obj.getLength(), 26)        << "Fatal: String has wrong length";
        EXPECT_FALSE(obj.isEmpty())           << "Fatal: String is empty";                        
    }
    {
        char_t str[4] = {'A','B','C','\0'};
        String const obj( str );
        ASSERT_NE(obj.getChar(), NULLPTR)  << "Fatal: C-String is null";
        EXPECT_STREQ(obj.getChar(), "ABC") << "Fatal: String has wrong characters";  
        EXPECT_NE(obj.getChar(), str)      << "Fatal: String addresses are the same";
        EXPECT_EQ(obj.getLength(), 3)      << "Fatal: String has wrong length";
        EXPECT_FALSE(obj.isEmpty())        << "Fatal: String is empty";
    }
    {
        TestString obj;
        obj.setConstructed(false);
        ASSERT_EQ(obj.getChar(), NULLPTR) << "Fatal: String is null";
        EXPECT_EQ(obj.getLength(), 0)     << "Fatal: String has wrong length";
        EXPECT_TRUE(obj.isEmpty())        << "Fatal: String is not empty";
    }
    {
        TestString obj( "ABC" );
        obj.setConstructed(false);
        ASSERT_EQ(obj.getChar(), NULLPTR) << "Fatal: String is null";
        EXPECT_EQ(obj.getLength(), 0)     << "Fatal: String has wrong length";
        EXPECT_TRUE(obj.isEmpty())        << "Fatal: String is not empty";
    }
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests the class string copping.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_BaseStringDynamicTest_char_t, copy)
{
    bool_t res( false );
    {
        String dst;
        String const src( "ABC" );
        res = dst.copy(src);
        EXPECT_TRUE(res) << "Fatal: Copy is not done";
        EXPECT_STREQ(dst.getChar(), "ABC") << "Fatal: String has wrong characters";
        EXPECT_STREQ(src.getChar(), "ABC") << "Fatal: String has wrong characters";
        EXPECT_EQ(dst.getLength(), 3)      << "Fatal: String has wrong length";
        EXPECT_EQ(src.getLength(), 3)      << "Fatal: String has wrong length";
        EXPECT_FALSE(dst.isEmpty())        << "Fatal: String is empty";
        EXPECT_FALSE(src.isEmpty())        << "Fatal: String is empty";
        EXPECT_NE(dst.getChar(), src.getChar()) << "Fatal: String addresses are the same";
    }
    {
        String dst( "ABC" );        
        String const src( "DEFG" );
        res = dst.copy(src);
        EXPECT_TRUE(res) << "Fatal: Copy is not done";
        EXPECT_STREQ(dst.getChar(), "DEFG") << "Fatal: String has wrong characters";
        EXPECT_STREQ(src.getChar(), "DEFG") << "Fatal: String has wrong characters";
        EXPECT_EQ(dst.getLength(), 4)       << "Fatal: String has wrong length";
        EXPECT_EQ(src.getLength(), 4)       << "Fatal: String has wrong length";
        EXPECT_FALSE(dst.isEmpty())         << "Fatal: String is empty";
        EXPECT_FALSE(src.isEmpty())         << "Fatal: String is empty";        
        EXPECT_NE(dst.getChar(), src.getChar()) << "Fatal: String addresses are the same";
    }
    {
        String dst("ABC");
        String const src( "DEFGHIJKLMNOPQRSTUVWXYZ" );
        res = dst.copy(src);
        EXPECT_TRUE(res) << "Fatal: Copy is not done";
        EXPECT_STREQ(dst.getChar(), "DEFGHIJKLMNOPQRSTUVWXYZ") << "Fatal: String has wrong characters";
        EXPECT_STREQ(src.getChar(), "DEFGHIJKLMNOPQRSTUVWXYZ") << "Fatal: String has wrong characters";
        EXPECT_EQ(dst.getLength(), 23)     << "Fatal: String has wrong length";
        EXPECT_EQ(src.getLength(), 23)      << "Fatal: String has wrong length";
        EXPECT_FALSE(dst.isEmpty())        << "Fatal: String is empty";
        EXPECT_FALSE(src.isEmpty())        << "Fatal: String is empty";
        EXPECT_NE(dst.getChar(), src.getChar()) << "Fatal: String addresses are the same";        
    }
    {
        String dst("ABCDEFGHIJKLM");
        String const src( "NOPQRSTUVWXYZ" );
        res = dst.copy(src);
        EXPECT_TRUE(res) << "Fatal: Copy is not done";
        EXPECT_STREQ(dst.getChar(), "NOPQRSTUVWXYZ") << "Fatal: String has wrong characters";
        EXPECT_STREQ(src.getChar(), "NOPQRSTUVWXYZ") << "Fatal: String has wrong characters";
        EXPECT_EQ(dst.getLength(), 13)     << "Fatal: String has wrong length";
        EXPECT_EQ(src.getLength(), 13)      << "Fatal: String has wrong length";
        EXPECT_FALSE(dst.isEmpty())        << "Fatal: String is empty";
        EXPECT_FALSE(src.isEmpty())        << "Fatal: String is empty";
        EXPECT_NE(dst.getChar(), src.getChar()) << "Fatal: String addresses are the same";        
    }
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests the class string copping.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_BaseStringDynamicTest_char_t, copy_unconstructed)
{
    bool_t res( false );
    {
        TestString dst;
        dst.setConstructed(false);
        String const src( "ABC" );        
        res = dst.copy(src);
        EXPECT_FALSE(res) << "Fatal: Copy is done";
        EXPECT_STREQ(dst.getChar(), NULLPTR) << "Fatal: String is copied";
        EXPECT_STREQ(src.getChar(), "ABC")   << "Fatal: String is changed";
        EXPECT_EQ(dst.getLength(), 0)        << "Fatal: String has wrong length";
        EXPECT_EQ(src.getLength(), 3)        << "Fatal: String has wrong length";
        EXPECT_TRUE(dst.isEmpty())           << "Fatal: String is not empty";
        EXPECT_FALSE(src.isEmpty())          << "Fatal: String is empty";        
        EXPECT_NE(dst.getChar(), src.getChar()) << "Fatal: String addresses are the same";        
    }
    {
        String dst( "ABC" );
        TestString src( "DEF" );
        src.setConstructed(false);
        res = dst.copy(src);
        EXPECT_FALSE(res) << "Fatal: Copy is done";
        EXPECT_STREQ(dst.getChar(), "ABC")   << "Fatal: String is copied";
        EXPECT_STREQ(src.getChar(), NULLPTR) << "Fatal: String is changed";
        EXPECT_EQ(dst.getLength(), 3)        << "Fatal: String has wrong length";
        EXPECT_EQ(src.getLength(), 0)        << "Fatal: String has wrong length";
        EXPECT_FALSE(dst.isEmpty())          << "Fatal: String is empty";
        EXPECT_TRUE(src.isEmpty())           << "Fatal: String is empty";        
        EXPECT_NE(dst.getChar(), src.getChar()) << "Fatal: String addresses are the same";        
    }
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests the class string copping.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_BaseStringDynamicTest_char_t, copy_banana)
{
    // The '🍌' character in:
    // UTF-8  Encoding: 0xF0 0x9F 0x8D 0x8C
    // UTF-16 Encoding: 0xD83C 0xDF4C
    // UTF-32 Encoding: 0x0001F34C    
    bool_t res( false );      
    String dst;
    String const src( "🍌" );
    res = dst.copy(src);
    EXPECT_TRUE(res) << "Fatal: Copy is not done";
    EXPECT_STREQ(dst.getChar(), "🍌") << "Fatal: String is wrong or the source file not in UTF-8";
    EXPECT_STREQ(src.getChar(), "🍌") << "Fatal: String has wrong characters";
    EXPECT_EQ(dst.getLength(), 4)     << "Fatal: String has wrong length";
    EXPECT_EQ(src.getLength(), 4)     << "Fatal: String has wrong length";
    EXPECT_FALSE(dst.isEmpty())       << "Fatal: String is empty";
    EXPECT_FALSE(src.isEmpty())       << "Fatal: String is empty";    
    EXPECT_NE(dst.getChar(), src.getChar()) << "Fatal: String addresses are the same";
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests the class string concatenation.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_BaseStringDynamicTest_char_t, concatenate)
{
    bool_t res( false );
    {
        String dst;
        String const src( "ABC" );
        res = dst.concatenate(src);
        EXPECT_TRUE(res) << "Fatal: Concatenation is not done";
        EXPECT_STREQ(dst.getChar(), "ABC") << "Fatal: String has wrong characters";
        EXPECT_STREQ(src.getChar(), "ABC") << "Fatal: String has wrong characters";
        EXPECT_EQ(dst.getLength(), 3)     << "Fatal: String has wrong length";
        EXPECT_EQ(src.getLength(), 3)     << "Fatal: String has wrong length";
        EXPECT_FALSE(dst.isEmpty())       << "Fatal: String is empty";
        EXPECT_FALSE(src.isEmpty())       << "Fatal: String is empty";
        EXPECT_NE(dst.getChar(), src.getChar()) << "Fatal: String addresses are the same";        
    }
    {
        String dst( "A" );
        String const src( "BC" );
        res = dst.concatenate(src);
        EXPECT_TRUE(res) << "Fatal: Concatenation is not done";
        EXPECT_STREQ(dst.getChar(), "ABC") << "Fatal: String has wrong characters";
        EXPECT_STREQ(src.getChar(), "BC") << "Fatal: String has wrong characters";
        EXPECT_EQ(dst.getLength(), 3)      << "Fatal: String has wrong length";
        EXPECT_EQ(src.getLength(), 2)      << "Fatal: String has wrong length";
        EXPECT_FALSE(dst.isEmpty())        << "Fatal: String is empty";
        EXPECT_FALSE(src.isEmpty())        << "Fatal: String is empty";        
        EXPECT_NE(dst.getChar(), src.getChar()) << "Fatal: String addresses are the same";
    }
    {
        String dst("ABC");
        String const src( "DEFGHIJKLMNOPQRSTUVWXYZ" );
        res = dst.concatenate(src);
        EXPECT_TRUE(res) << "Fatal: Concatenation is not done";
        EXPECT_STREQ(dst.getChar(), "ABCDEFGHIJKLMNOPQRSTUVWXYZ") << "Fatal: String has wrong characters";
        EXPECT_STREQ(src.getChar(), "DEFGHIJKLMNOPQRSTUVWXYZ") << "Fatal: String has wrong characters";
        EXPECT_EQ(dst.getLength(), 26)     << "Fatal: String has wrong length";
        EXPECT_EQ(src.getLength(), 23)      << "Fatal: String has wrong length";
        EXPECT_FALSE(dst.isEmpty())        << "Fatal: String is empty";
        EXPECT_FALSE(src.isEmpty())        << "Fatal: String is empty";
        EXPECT_NE(dst.getChar(), src.getChar()) << "Fatal: String addresses are the same";        
    }
    {
        String dst("ABCDEFGHIJKLM");
        String const src( "NOPQRSTUVWXYZ" );
        res = dst.concatenate(src);
        EXPECT_TRUE(res) << "Fatal: Concatenation is not done";
        EXPECT_STREQ(dst.getChar(), "ABCDEFGHIJKLMNOPQRSTUVWXYZ") << "Fatal: String has wrong characters";
        EXPECT_STREQ(src.getChar(), "NOPQRSTUVWXYZ") << "Fatal: String has wrong characters";
        EXPECT_EQ(dst.getLength(), 26)     << "Fatal: String has wrong length";
        EXPECT_EQ(src.getLength(), 13)      << "Fatal: String has wrong length";
        EXPECT_FALSE(dst.isEmpty())        << "Fatal: String is empty";
        EXPECT_FALSE(src.isEmpty())        << "Fatal: String is empty";
        EXPECT_NE(dst.getChar(), src.getChar()) << "Fatal: String addresses are the same";        
    }    
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests the class string concatenation.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_BaseStringDynamicTest_char_t, concatenation_unconstructed)
{
    bool_t res( false );
    {
        TestString dst;
        dst.setConstructed(false);
        String const src( "ABC" );        
        res = dst.concatenate(src);
        EXPECT_FALSE(res) << "Fatal: Concatenation is done";
        EXPECT_STREQ(dst.getChar(), NULLPTR) << "Fatal: String is copied";
        EXPECT_STREQ(src.getChar(), "ABC")   << "Fatal: String is changed";
        EXPECT_EQ(dst.getLength(), 0)        << "Fatal: String has wrong length";
        EXPECT_EQ(src.getLength(), 3)        << "Fatal: String has wrong length";
        EXPECT_TRUE(dst.isEmpty())           << "Fatal: String is not empty";
        EXPECT_FALSE(src.isEmpty())          << "Fatal: String is empty";        
        EXPECT_NE(dst.getChar(), src.getChar()) << "Fatal: String addresses are the same";        
    }
    {
        String dst( "AB" );
        TestString src( "CD" );
        src.setConstructed(false);
        res = dst.concatenate(src);
        EXPECT_FALSE(res) << "Fatal: Concatenation is done";
        EXPECT_STREQ(dst.getChar(), "AB")   << "Fatal: String is copied";
        EXPECT_STREQ(src.getChar(), NULLPTR) << "Fatal: String is changed";
        EXPECT_EQ(dst.getLength(), 2)        << "Fatal: String has wrong length";
        EXPECT_EQ(src.getLength(), 0)        << "Fatal: String has wrong length";
        EXPECT_FALSE(dst.isEmpty())          << "Fatal: String is empty";
        EXPECT_TRUE(src.isEmpty())           << "Fatal: String is empty";        
        EXPECT_NE(dst.getChar(), src.getChar()) << "Fatal: String addresses are the same";        
    }
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests the class string copping.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_BaseStringDynamicTest_char_t, concatenation_banana)
{
    // The '🍌' character in:
    // UTF-8  Encoding: 0xF0 0x9F 0x8D 0x8C
    // UTF-16 Encoding: 0xD83C 0xDF4C
    // UTF-32 Encoding: 0x0001F34C    
    bool_t res( false );      
    String dst( "\xF0\x9F" );
    String const src( "\x8D\x8C" );
    res = dst.concatenate(src);
    EXPECT_TRUE(res) << "Fatal: Concatenation is not done";
    EXPECT_STREQ(dst.getChar(), "🍌") << "Fatal: String is wrong or the source file not in UTF-8";
    EXPECT_EQ(dst.getLength(), 4)     << "Fatal: String has wrong length";
    EXPECT_FALSE(dst.isEmpty())       << "Fatal: String is empty";
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests the class string equal to other string.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_BaseStringDynamicTest_char_t, isEqualTo)
{
    bool_t res( false );
    {
        String const dst;
        String const src( "CD" );
        res = dst.isEqualTo(src);
        EXPECT_FALSE(res) << "Fatal: Strings equal to each other";
        EXPECT_STRNE(dst.getChar(), src.getChar()) << "Fatal: Strings equal to each other";
    }
    {
        String const dst( "AB" );
        String const src;
        res = dst.isEqualTo(src);
        EXPECT_FALSE(res) << "Fatal: Strings equal to each other";
        EXPECT_STRNE(dst.getChar(), src.getChar()) << "Fatal: Strings equal to each other";
    }    
    {
        String const dst( "AB" );
        String const src( "CD" );
        res = dst.isEqualTo(src);
        EXPECT_FALSE(res) << "Fatal: Strings equal to each other";
        EXPECT_STRNE(dst.getChar(), src.getChar()) << "Fatal: Strings equal to each other";
    }
    {
        String const dst( "AB" );
        String const src( "AB" );
        res = dst.isEqualTo(src);
        EXPECT_TRUE(res) << "Fatal: Strings don't equal to each other";
        EXPECT_STREQ(dst.getChar(), src.getChar()) << "Fatal: String don't equal to each other";
    }
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests the class string equal to other string.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_BaseStringDynamicTest_char_t, isEqualTo_unconstructed)
{   
    bool_t res( false );
    {
        TestString dst( "AB" );
        dst.setConstructed(false);
        String src( "AB" );
        res = dst.isEqualTo(src);
        EXPECT_FALSE(res) << "Fatal: Strings equal to each other";
        EXPECT_STRNE(dst.getChar(), src.getChar()) << "Fatal: Strings equal to each other";
    }
    {
        String dst( "AB" );
        TestString src( "AB" );
        src.setConstructed(false);        
        res = dst.isEqualTo(src);
        EXPECT_FALSE(res) << "Fatal: Strings equal to each other";
        EXPECT_STRNE(dst.getChar(), src.getChar()) << "Fatal: Strings equal to each other";
    }
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests convertion integer to String.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass integer.
 *
 * @b Assert:
 *      - Test number in String is compare. 
 */
TEST_F(lib_BaseStringDynamicTest_char_t, convert_int8)
{
    String obj;
    bool_t res( false );

    int8_t val( 0 );
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "0") << "Fatal: String is wrong";    

    val = 1;
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "1") << "Fatal: String is wrong";    

    val = -1;
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "-1") << "Fatal: String is wrong";    

    val = 0x7A;
    res = obj.convert(val, Number::BASE_16);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "7a") << "Fatal: String is wrong";    

    val = 127;
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "127") << "Fatal: String is wrong";    
    res = obj.convert(val, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "7f") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "177") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "1111111") << "Fatal: String is wrong";

    val = -127;
    res = obj.convert(val, Number::BASE_10);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "-127") << "Fatal: String is wrong";

    obj = String(ALPHABET);    
    val = 123;
    res = obj.convert(val, static_cast<Number::Base>(32));
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";        

    // Test the Exception 1
    val = -128;
    res = obj.convert(val, Number::BASE_10);
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";
   
    // Test the Exception 2
    val = -127;    
    res = obj.convert(val, Number::BASE_16);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_8);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_2);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests convertion integer to String.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass integer.
 *
 * @b Assert:
 *      - Test number in String is compare. 
 */
TEST_F(lib_BaseStringDynamicTest_char_t, convert_uint8)
{
    String obj;
    bool_t res( false );

    uint8_t val( 0 );
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "0") << "Fatal: String is wrong";    

    val = 1;
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "1") << "Fatal: String is wrong";    

    val = 0xAB;
    res = obj.convert(val, Number::BASE_16);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "ab") << "Fatal: String is wrong";    

    val = 127;
    res = obj.convert(val);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "127") << "Fatal: String is wrong";    
    res = obj.convert(val, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "7f") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "177") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "1111111") << "Fatal: String is wrong";

    val = 255;
    res = obj.convert(val, Number::BASE_10);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "255") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "ff") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "377") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "11111111") << "Fatal: String is wrong";

    obj = String(ALPHABET);
    val = 123;
    res = obj.convert(val, static_cast<Number::Base>(32));
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";        
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests convertion integer to String.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass integer.
 *
 * @b Assert:
 *      - Test number in String is compare. 
 */
TEST_F(lib_BaseStringDynamicTest_char_t, convert_int16)
{
    String obj;
    bool_t res( false );

    int16_t val( 0 );
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "0") << "Fatal: String is wrong";    

    val = 1;
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "1") << "Fatal: String is wrong";    

    val = -1;
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "-1") << "Fatal: String is wrong";    

    val = 0x7ABC;
    res = obj.convert(val, Number::BASE_16);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "7abc") << "Fatal: String is wrong";    

    val = 32767;
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "32767") << "Fatal: String is wrong";    
    res = obj.convert(val, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "7fff") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "77777") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "111111111111111") << "Fatal: String is wrong";

    val = -32767;
    res = obj.convert(val, Number::BASE_10);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "-32767") << "Fatal: String is wrong";
    
    obj = String(ALPHABET);    
    val = 123;
    res = obj.convert(val, static_cast<Number::Base>(32));
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";        

    // Test the Exception 1
    val = -32768;
    res = obj.convert(val, Number::BASE_10);
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";
   
    // Test the Exception 2
    val = -32767;    
    res = obj.convert(val, Number::BASE_16);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_8);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_2);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests convertion integer to String.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass integer.
 *
 * @b Assert:
 *      - Test number in String is compare. 
 */
TEST_F(lib_BaseStringDynamicTest_char_t, convert_uint16)
{
    String obj;
    bool_t res( false );

    uint16_t val( 0 );
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "0") << "Fatal: String is wrong";    

    val = 1;
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "1") << "Fatal: String is wrong";    

    val = 0xABCD;
    res = obj.convert(val, Number::BASE_16);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "abcd") << "Fatal: String is wrong";    

    val = 32767;
    res = obj.convert(val);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "32767") << "Fatal: String is wrong";    
    res = obj.convert(val, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "7fff") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "77777") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "111111111111111") << "Fatal: String is wrong";

    val = 65535;
    res = obj.convert(val, Number::BASE_10);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "65535") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "ffff") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "177777") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "1111111111111111") << "Fatal: String is wrong";

    obj = String(ALPHABET);
    val = 123;
    res = obj.convert(val, static_cast<Number::Base>(32));
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";        
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests convertion integer to String.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass integer.
 *
 * @b Assert:
 *      - Test number in String is compare. 
 */
TEST_F(lib_BaseStringDynamicTest_char_t, convert_int32)
{
    String obj;
    bool_t res( false );

    int32_t val( 0 );
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "0") << "Fatal: String is wrong";    

    val = 1;
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "1") << "Fatal: String is wrong";    

    val = -1;
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "-1") << "Fatal: String is wrong";    

    val = 0x00ABCDEF;
    res = obj.convert(val, Number::BASE_16);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "abcdef") << "Fatal: String is wrong";    

    val = 2147483647;
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "2147483647") << "Fatal: String is wrong";    
    res = obj.convert(val, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "7fffffff") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "17777777777") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "1111111111111111111111111111111") << "Fatal: String is wrong";

    val = -2147483647;
    res = obj.convert(val, Number::BASE_10);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "-2147483647") << "Fatal: String is wrong";
    
    obj = String(ALPHABET);    
    val = 123;
    res = obj.convert(val, static_cast<Number::Base>(32));
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";        

    // Test the Exception 1
    val = -2147483648;
    res = obj.convert(val, Number::BASE_10);
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";
   
    // Test the Exception 2
    val = -2147483647;    
    res = obj.convert(val, Number::BASE_16);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_8);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_2);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests convertion integer to String.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass integer.
 *
 * @b Assert:
 *      - Test number in String is compare. 
 */
TEST_F(lib_BaseStringDynamicTest_char_t, convert_uint32)
{
    String obj;
    bool_t res( false );

    uint32_t val( 0 );
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "0") << "Fatal: String is wrong";    

    val = 1;
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "1") << "Fatal: String is wrong";    

    val = 0x89ABCDEF;
    res = obj.convert(val, Number::BASE_16);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "89abcdef") << "Fatal: String is wrong";    

    val = 2147483647;
    res = obj.convert(val);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "2147483647") << "Fatal: String is wrong";    
    res = obj.convert(val, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "7fffffff") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "17777777777") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "1111111111111111111111111111111") << "Fatal: String is wrong";

    val = 4294967295;
    res = obj.convert(val, Number::BASE_10);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "4294967295") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "ffffffff") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "37777777777") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "11111111111111111111111111111111") << "Fatal: String is wrong";

    obj = String(ALPHABET);
    val = 123;
    res = obj.convert(val, static_cast<Number::Base>(32));
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";        
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests convertion integer to String.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass integer.
 *
 * @b Assert:
 *      - Test number in String is compare. 
 */
TEST_F(lib_BaseStringDynamicTest_char_t, convert_int64)
{
    String obj;
    bool_t res( false );

    int64_t val( 0LL );
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "0") << "Fatal: String is wrong";    

    val = 1LL;
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "1") << "Fatal: String is wrong";    

    val = -1LL;
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "-1") << "Fatal: String is wrong";    

    val = 0x1234567890ABCDEFLL;
    res = obj.convert(val, Number::BASE_16);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "1234567890abcdef") << "Fatal: String is wrong";    

    val = 9223372036854775807LL;
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "9223372036854775807") << "Fatal: String is wrong";    
    res = obj.convert(val, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "7fffffffffffffff") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "777777777777777777777") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "111111111111111111111111111111111111111111111111111111111111111") << "Fatal: String is wrong";

    val = -9223372036854775807LL;
    res = obj.convert(val, Number::BASE_10);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "-9223372036854775807") << "Fatal: String is wrong";
    
    obj = String(ALPHABET);    
    val = 123;
    res = obj.convert(val, static_cast<Number::Base>(32));
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";        

    // Test the Exception 1
    val = -9223372036854775807LL - 1LL;
    res = obj.convert(val, Number::BASE_10);
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";
   
    // Test the Exception 2
    val = -9223372036854775807LL;
    res = obj.convert(val, Number::BASE_16);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_8);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_2);
    EXPECT_FALSE(res) << "Fatal: Value is converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests convertion integer to String.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Pass integer.
 *
 * @b Assert:
 *      - Test number in String is compare. 
 */
TEST_F(lib_BaseStringDynamicTest_char_t, convert_uint64)
{
    String obj;
    bool_t res( false );

    uint64_t val( 0ULL );
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "0") << "Fatal: String is wrong";    

    val = 1ULL;
    res = obj.convert(val, Number::BASE_10);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "1") << "Fatal: String is wrong";    

    val = 0x00ABCDEFULL;
    res = obj.convert(val, Number::BASE_16);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "abcdef") << "Fatal: String is wrong";    

    val = 9223372036854775807ULL;
    res = obj.convert(val);   
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "9223372036854775807") << "Fatal: String is wrong";    
    res = obj.convert(val, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "7fffffffffffffff") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "777777777777777777777") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "111111111111111111111111111111111111111111111111111111111111111") << "Fatal: String is wrong";

    val = 18446744073709551615ULL;
    res = obj.convert(val, Number::BASE_10);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "18446744073709551615") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_16);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "ffffffffffffffff") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_8);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "1777777777777777777777") << "Fatal: String is wrong";
    res = obj.convert(val, Number::BASE_2);
    EXPECT_TRUE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), "1111111111111111111111111111111111111111111111111111111111111111") << "Fatal: String is wrong";

    obj = String(ALPHABET);
    val = 123ULL;
    res = obj.convert(val, static_cast<Number::Base>(32));
    EXPECT_FALSE(res) << "Fatal: Value is not converted";
    EXPECT_STREQ(obj.getChar(), ALPHABET) << "Fatal: String is wrong";        
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests the class string equal to other string.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_BaseStringDynamicTest_char_t, operator_equal)
{
    {
        String const obj1(ALPHABET);
        String const obj2(ALPHABET);
        EXPECT_TRUE(obj1 == obj2) << "Fatal: Strings don't equal to each other";
    }
    {
        String const obj1(ALPHABET);
        String const obj2("ABC");
        EXPECT_FALSE(obj1 == obj2) << "Fatal: Strings equal to each other";
    }
    
    {
        String const obj1(ALPHABET);
        EXPECT_TRUE(obj1 == ALPHABET) << "Fatal: Strings don't equal to each other";
    }
    {
        String const obj1(ALPHABET);
        EXPECT_FALSE(obj1 == "ABC") << "Fatal: Strings equal to each other";
    }
    
    {
        String const obj2(ALPHABET);
        EXPECT_TRUE(ALPHABET == obj2) << "Fatal: Strings don't equal to each other";
    }
    {
        String const obj2(ALPHABET);
        EXPECT_FALSE("ABC" == obj2) << "Fatal: Strings equal to each other";
    }

    {
        String const obj1(ALPHABET);
        String const obj2(ALPHABET);
        api::String<char_t> const& ibj1( obj1 );
        api::String<char_t> const& ibj2( obj2 );
        EXPECT_TRUE(ibj1 == ibj2) << "Fatal: Strings don't equal to each other";
    }
    {
        String const obj1(ALPHABET);
        String const obj2("ABC");
        api::String<char_t> const& ibj1( obj1 );
        api::String<char_t> const& ibj2( obj2 );
        EXPECT_FALSE(ibj1 == ibj2) << "Fatal: Strings equal to each other";
    }
    
    {
        String const obj1(ALPHABET);
        api::String<char_t> const& ibj1( obj1 );
        EXPECT_TRUE(ibj1 == ALPHABET) << "Fatal: Strings don't equal to each other";
    }
    {
        String const obj1(ALPHABET);
        api::String<char_t> const& ibj1( obj1 );
        EXPECT_FALSE(ibj1 == "ABC") << "Fatal: Strings equal to each other";
    }
    
    {
        String const obj2(ALPHABET);
        api::String<char_t> const& ibj2( obj2 );        
        EXPECT_TRUE(ALPHABET == ibj2) << "Fatal: Strings don't equal to each other";
    }
    {
        String const obj2(ALPHABET);
        api::String<char_t> const& ibj2( obj2 );        
        EXPECT_FALSE("ABC" == ibj2) << "Fatal: Strings equal to each other";
    }
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests the class string does not equal to other string.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_BaseStringDynamicTest_char_t, operator_unequal)
{
    {
        String const obj1(ALPHABET);
        String const obj2(ALPHABET);
        EXPECT_FALSE(obj1 != obj2) << "Fatal: Strings don't equal to each other";
    }
    {
        String const obj1(ALPHABET);
        String const obj2("ABC");
        EXPECT_TRUE(obj1 != obj2) << "Fatal: Strings equal to each other";
    }
    
    {
        String const obj1(ALPHABET);
        EXPECT_FALSE(obj1 != ALPHABET) << "Fatal: Strings don't equal to each other";
    }
    {
        String const obj1(ALPHABET);
        EXPECT_TRUE(obj1 != "ABC") << "Fatal: Strings equal to each other";
    }
    
    {
        String const obj2(ALPHABET);
        EXPECT_FALSE(ALPHABET != obj2) << "Fatal: Strings don't equal to each other";
    }
    {
        String const obj2(ALPHABET);
        EXPECT_TRUE("ABC" != obj2) << "Fatal: Strings equal to each other";
    }

    {
        String const obj1(ALPHABET);
        String const obj2(ALPHABET);
        api::String<char_t> const& ibj1( obj1 );
        api::String<char_t> const& ibj2( obj2 );
        EXPECT_FALSE(ibj1 != ibj2) << "Fatal: Strings don't equal to each other";
    }
    {
        String const obj1(ALPHABET);
        String const obj2("ABC");
        api::String<char_t> const& ibj1( obj1 );
        api::String<char_t> const& ibj2( obj2 );
        EXPECT_TRUE(ibj1 != ibj2) << "Fatal: Strings equal to each other";
    }
    
    {
        String const obj1(ALPHABET);
        api::String<char_t> const& ibj1( obj1 );
        EXPECT_FALSE(ibj1 != ALPHABET) << "Fatal: Strings don't equal to each other";
    }
    {
        String const obj1(ALPHABET);
        api::String<char_t> const& ibj1( obj1 );
        EXPECT_TRUE(ibj1 != "ABC") << "Fatal: Strings equal to each other";
    }
    
    {
        String const obj2(ALPHABET);
        api::String<char_t> const& ibj2( obj2 );        
        EXPECT_FALSE(ALPHABET != ibj2) << "Fatal: Strings don't equal to each other";
    }
    {
        String const obj2(ALPHABET);
        api::String<char_t> const& ibj2( obj2 );        
        EXPECT_TRUE("ABC" != ibj2) << "Fatal: Strings equal to each other";
    }
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests the class string does not equal to other string.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_BaseStringDynamicTest_char_t, operator_assignment_sum)
{
    {
        String dst("ABCDEFGHIJKLM");
        String const src("NOPQRSTUVWXYZ");
        dst += src;
        EXPECT_STREQ(dst.getChar(), "ABCDEFGHIJKLMNOPQRSTUVWXYZ") << "Fatal: String has wrong characters";
        EXPECT_STREQ(src.getChar(), "NOPQRSTUVWXYZ") << "Fatal: String has wrong characters";
        EXPECT_EQ(dst.getLength(), 26) << "Fatal: String has wrong length";
        EXPECT_EQ(src.getLength(), 13) << "Fatal: String has wrong length";
        EXPECT_FALSE(dst.isEmpty())    << "Fatal: String is empty";
        EXPECT_FALSE(src.isEmpty())    << "Fatal: String is empty";
        EXPECT_NE(dst.getChar(), src.getChar()) << "Fatal: String addresses are the same";        
    }
    {
        String dst("ABCDEFGHIJKLM");
        dst += "NOPQRSTUVWXYZ";
        EXPECT_STREQ(dst.getChar(), "ABCDEFGHIJKLMNOPQRSTUVWXYZ") << "Fatal: String has wrong characters";
        EXPECT_EQ(dst.getLength(), 26) << "Fatal: String has wrong length";
        EXPECT_FALSE(dst.isEmpty())    << "Fatal: String is empty";
    }
}

/**
 * @relates lib_BaseStringDynamicTest_char_t
 * @brief Tests the class string does not equal to other string.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_BaseStringDynamicTest_char_t, operator_sum)
{
    {
        String const obj1("ABCDEFGHIJKLM");
        String const obj2("NOPQRSTUVWXYZ");
        String const obj(obj1 + obj2);
        EXPECT_STREQ(obj.getChar(), "ABCDEFGHIJKLMNOPQRSTUVWXYZ") << "Fatal: String has wrong characters";
        EXPECT_EQ(obj.getLength(), 26) << "Fatal: String has wrong length";
        EXPECT_FALSE(obj.isEmpty())    << "Fatal: String is empty";
    }
    {
        String const obj1("ABCDEFGHIJKLM");
        String const obj2("NOPQRSTUVWXYZ");
        api::String<char_t> const& ibj2(obj2);        
        String const obj(obj1 + ibj2);
        EXPECT_STREQ(obj.getChar(), "ABCDEFGHIJKLMNOPQRSTUVWXYZ") << "Fatal: String has wrong characters";
        EXPECT_EQ(obj.getLength(), 26) << "Fatal: String has wrong length";
        EXPECT_FALSE(obj.isEmpty())    << "Fatal: String is empty";
    }
    {
        String const obj1("ABCDEFGHIJKLM");
        String const obj2("NOPQRSTUVWXYZ");
        api::String<char_t> const& ibj1(obj1);        
        String const obj(ibj1 + obj2);
        EXPECT_STREQ(obj.getChar(), "ABCDEFGHIJKLMNOPQRSTUVWXYZ") << "Fatal: String has wrong characters";
        EXPECT_EQ(obj.getLength(), 26) << "Fatal: String has wrong length";
        EXPECT_FALSE(obj.isEmpty())    << "Fatal: String is empty";
    }
    {
        String const obj1("ABCDEFGHIJKLM");
        String const obj(obj1 + "NOPQRSTUVWXYZ");
        EXPECT_STREQ(obj.getChar(), "ABCDEFGHIJKLMNOPQRSTUVWXYZ") << "Fatal: String has wrong characters";
        EXPECT_EQ(obj.getLength(), 26) << "Fatal: String has wrong length";
        EXPECT_FALSE(obj.isEmpty())    << "Fatal: String is empty";
    }
    {
        String const obj2("NOPQRSTUVWXYZ");
        String const obj("ABCDEFGHIJKLM" + obj2);
        EXPECT_STREQ(obj.getChar(), "ABCDEFGHIJKLMNOPQRSTUVWXYZ") << "Fatal: String has wrong characters";
        EXPECT_EQ(obj.getLength(), 26) << "Fatal: String has wrong length";
        EXPECT_FALSE(obj.isEmpty())    << "Fatal: String is empty";
    }
}

} // namespace lib
} // namespace eoos
