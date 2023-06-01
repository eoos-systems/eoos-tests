/**
 * @file      lib.ArgumentParserTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::ArgumentParser`.
 */
#include "lib.ArgumentParser.hpp"
#include "System.hpp"
#include "lib.String.hpp"

#include "lib.Stream.hpp"


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
        char_t* argv[] = {NULLPTR};
        int32_t argc( 0 );
        ArgumentParser<char_t,0> const obj(argc, argv);
        EXPECT_TRUE(obj.isConstructed())  << "Fatal: Object is not constructed";
    }
    {
        char_t ARG0[] = {"ARG0"};
        char_t* argv[] = {ARG0, NULLPTR};
        int32_t argc( 1 );
        ArgumentParser<char_t,0> const obj(argc, argv);
        EXPECT_TRUE(obj.isConstructed())  << "Fatal: Object is not constructed";
    }
    {
        char_t ARG0[] = {"ARG0"};
        char_t ARG1[] = {"ARG1"};
        char_t* argv[] = {ARG0, ARG1, NULLPTR};
        int32_t argc( 2 );
        ArgumentParser<char_t,0> const obj(argc, argv);
        EXPECT_TRUE(obj.isConstructed())  << "Fatal: Object is not constructed";
    }
    {
        char_t ARG0[] = {"ARG0"};
        char_t ARG1[] = {"ARG1"};
        char_t* argv[] = {ARG0, ARG1, NULLPTR};
        int32_t argc( -2 );
        ArgumentParser<char_t,0> const obj(argc, argv);
        EXPECT_FALSE(obj.isConstructed())  << "Fatal: Object is constructed";
    }
    {
        char_t ARG0[] = {"ARG0"};
        char_t ARG1[] = {"ARG1"};
        char_t* argv[] = {ARG0, ARG1, NULLPTR};
        int32_t argc( 5 );
        ArgumentParser<char_t,0> const obj(argc, argv);
        EXPECT_FALSE(obj.isConstructed())  << "Fatal: Object is constructed";
    }
    {
        char_t ARG0[] = {"ARG0"};
        char_t ARG2[] = {"ARG2"};
        char_t* argv[] = {ARG0, NULLPTR, ARG2, NULLPTR};
        int32_t argc( 3 );
        ArgumentParser<char_t,0> const obj(argc, argv);
        EXPECT_FALSE(obj.isConstructed())  << "Fatal: Object is constructed";
    }
    {
        // @note Involve ARGX to be sure a previous call with possible NULL on the same possition overrided.
        char_t ARGX[] = {"ARGX"};    
        char_t ARG0[] = {"ARG0"};
        char_t ARG1[] = {"ARG1"};
        char_t* argv[] = {ARG0, ARG1, ARGX};
        int32_t argc( 2 );
        ArgumentParser<char_t,0> const obj(argc, argv);
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

static volatile int i_ = 0;

TEST_F(lib_ArgumentParserTest, DISABLED_getArguments)
{
    {
        char_t* argv[] = {NULLPTR};
        int32_t argc( 0 );
        ArgumentParser<char_t,0> obj(argc, argv);
        EXPECT_EQ(obj.getArguments().getLength(), 0)  << "Fatal: Wrong argumnet number";
    }
    {
        char_t ARG0[] = {"ARG0"};
        char_t* argv[] = {ARG0, NULLPTR};
        int32_t argc( 1 );
        ArgumentParser<char_t,0> obj(argc, argv);
        EXPECT_EQ(obj.getArguments().getLength(), 1)  << "Fatal: Wrong argumnet number";
        EXPECT_STREQ(obj.getArguments().get(0)->getChar(), "ARG0") << "Fatal: Argument has wrong characters";
    }
    {
        char_t ARG0[] = {"ARG0"};
        char_t ARG1[] = {"ARG1"};
        char_t* argv[] = {ARG0, ARG1, NULLPTR};
        int32_t argc( 2 );
        ArgumentParser<char_t,0> obj(argc, argv);
        EXPECT_EQ(obj.getArguments().getLength(), 2)  << "Fatal: Wrong argumnet number";
        EXPECT_STREQ(obj.getArguments().get(0)->getChar(), "ARG0") << "Fatal: Argument has wrong characters";
        i_++;
        EXPECT_STREQ(obj.getArguments().get(1)->getChar(), "ARG1") << "Fatal: Argument has wrong characters";
        i_++;
    }    
}

/**
 * @relates lib_ArgumentParserTest
 * @brief Debug a failure. 
 */
TEST_F(lib_ArgumentParserTest, debug)
{
    char_t ARG0[] = {"ARG0"};
    char_t ARG1[] = {"ARG1"};
    char_t* argv[] = {ARG0, ARG1, NULLPTR};
    int32_t argc( 2 );

    ArgumentParser<char_t,0> obj(argc, argv);
    
    api::List< api::String<char_t>* >* /*volatile*/ args( &obj.getArguments() );
    
    const char* ch( args->get(1)->getChar() ) ;
    
    ASSERT_STREQ(ch, "ARG1") << "Fatal: Argument has wrong characters";        
}

} // namespace lib
} // namespace eoos
