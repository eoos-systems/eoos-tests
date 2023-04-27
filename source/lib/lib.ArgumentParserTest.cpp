/**
 * @file      lib.ArgumentParserTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::ArgumentParser`.
 */
#include "lib.ArgumentParser.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{

/**
 * @class lib_ArgumentParserTest
 * @test ArgumentParser
 * @brief Tests ArgumentParser class functionality.
 */
class lib_ArgumentParserTest : public ::testing::Test
{

private:
    
    System eoos_; ///< EOOS Operating System.
};    

/**
 * @relates lib_ArgumentParserTest
 * @brief Test if object is constructed. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct an object.
 *      - Destruct the object. 
 *
 * @b Assert:
 *      - Test if the object is constructed and destructed.
 */
TEST_F(lib_ArgumentParserTest, isConstructed)
{
    {
        char_t* args[] = {NULLPTR};
        int32_t argv( 0 );
        ArgumentParser<char_t,0> const obj(argv, args);
        EXPECT_TRUE(obj.isConstructed())  << "Fatal: Object is not constructed";
    }
    {
        char_t ARG0[] = {"ARG0"};
        char_t* args[] = {ARG0, NULLPTR};
        int32_t argv( 1 );
        ArgumentParser<char_t,0> const obj(argv, args);
        EXPECT_TRUE(obj.isConstructed())  << "Fatal: Object is not constructed";
    }
    {
        char_t ARG0[] = {"ARG0"};
        char_t ARG1[] = {"ARG1"};
        char_t* args[] = {ARG0, ARG1, NULLPTR};
        int32_t argv( 2 );
        ArgumentParser<char_t,0> const obj(argv, args);
        EXPECT_TRUE(obj.isConstructed())  << "Fatal: Object is not constructed";
    }
    {
        char_t ARG0[] = {"ARG0"};
        char_t ARG1[] = {"ARG1"};
        char_t* args[] = {ARG0, ARG1, NULLPTR};
        int32_t argv( -2 );
        ArgumentParser<char_t,0> const obj(argv, args);
        EXPECT_FALSE(obj.isConstructed())  << "Fatal: Object is constructed";
    }
    {
        char_t ARG0[] = {"ARG0"};
        char_t ARG1[] = {"ARG1"};
        char_t* args[] = {ARG0, ARG1, NULLPTR};
        int32_t argv( 5 );
        ArgumentParser<char_t,0> const obj(argv, args);
        EXPECT_FALSE(obj.isConstructed())  << "Fatal: Object is constructed";
    }
    {
        char_t ARG0[] = {"ARG0"};
        char_t ARG2[] = {"ARG2"};
        char_t* args[] = {ARG0, NULLPTR, ARG2, NULLPTR};
        int32_t argv( 3 );
        ArgumentParser<char_t,0> const obj(argv, args);
        EXPECT_FALSE(obj.isConstructed())  << "Fatal: Object is constructed";
    }
    {
        // @note Involve ARGX to be sure a previous call with possible NULL on the same possition overrided.
        char_t ARGX[] = {"ARGX"};    
        char_t ARG0[] = {"ARG0"};
        char_t ARG1[] = {"ARG1"};
        char_t* args[] = {ARG0, ARG1, ARGX};
        int32_t argv( 2 );
        ArgumentParser<char_t,0> const obj(argv, args);
        EXPECT_FALSE(obj.isConstructed())  << "Fatal: Object is constructed";
    }
    {
        ArgumentParser<char_t,0> const obj(0, NULLPTR);
        EXPECT_FALSE(obj.isConstructed())  << "Fatal: Object is constructed";
    }
    {
        ArgumentParser<char_t,0> const obj(2, NULLPTR);
        EXPECT_FALSE(obj.isConstructed())  << "Fatal: Object is constructed";
    }
}

/**
 * @relates lib_ArgumentParserTest
 * @brief Test the protected function changes constructed status of object. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct an object.
 *      - Get arguments. 
 *
 * @b Assert:
 *      - Test if passed agruments parsed correctly.
 */
TEST_F(lib_ArgumentParserTest, getArguments)
{
    {
        char_t* args[] = {NULLPTR};
        int32_t argv( 0 );
        ArgumentParser<char_t,0> obj(argv, args);
        EXPECT_EQ(obj.getArguments().getLength(), 0)  << "Fatal: Wrong argumnet number";
    }
    {
        char_t ARG0[] = {"ARG0"};
        char_t* args[] = {ARG0, NULLPTR};
        int32_t argv( 1 );
        ArgumentParser<char_t,0> obj(argv, args);
        EXPECT_EQ(obj.getArguments().getLength(), 1)  << "Fatal: Wrong argumnet number";
        EXPECT_STREQ(obj.getArguments().get(0).getChar(), "ARG0") << "Fatal: Argument has wrong characters";
    }
    {
        char_t ARG0[] = {"ARG0"};
        char_t ARG1[] = {"ARG1"};
        char_t* args[] = {ARG0, ARG1, NULLPTR};
        int32_t argv( 2 );
        ArgumentParser<char_t,0> obj(argv, args);
        EXPECT_EQ(obj.getArguments().getLength(), 2)  << "Fatal: Wrong argumnet number";        
        EXPECT_STREQ(obj.getArguments().get(0).getChar(), "ARG0") << "Fatal: Argument has wrong characters";
        EXPECT_STREQ(obj.getArguments().get(1).getChar(), "ARG1") << "Fatal: Argument has wrong characters";        
    }    
}

} // namespace lib
} // namespace eoos
