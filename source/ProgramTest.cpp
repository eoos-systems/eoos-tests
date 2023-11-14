/**
 * @file      ProrgamTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020-2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `Program`. 
 */
#include "Program.hpp"
#include "System.hpp"
#include "lib.String.hpp"
#include "lib.ArgumentParser.hpp"

namespace eoos
{

static const int32_t PROGRAM_OK             (777); ///< Correct program exit code.
static const int32_t PROGRAM_WRONG_ARGS     (666); ///< Wrong program exit code.
static const int32_t PROGRAM_ERROR_ARGUMENT (555);  ///< Error of a function argument.

/**
 * @copydoc eoos::Program::start(int32_t, char_t**)
 */
int32_t Program::start(int32_t argc, char_t* argv[])
{
    lib::ArgumentParser<char_t,0> parser(argc, argv);
    if( !parser.isConstructed() )
    {
        return PROGRAM_ERROR_ARGUMENT;
    }
    api::List<api::String<char_t>*>& args( parser.getArguments() ); 
    int32_t error(PROGRAM_WRONG_ARGS);
    switch( args.getLength() )
    {
        case 0:
        {
            error = PROGRAM_OK;
            break;
        }
        case 2:
        {
            lib::String str0( args.get(0)->getChar() );
            lib::String str1( args.get(1)->getChar() );
            if( (str0 == "ARG0") && (str1 == "ARG1") )
            {
                error = static_cast<int32_t>( args.getLength() );
            }
            break;
        }            
    }
    return error;
}

/**
 * @class glb_ProgramTest
 * @test Call
 * @brief Tests an application on EOOS starts sucessfully.
 */
class glb_ProgramTest : public ::testing::Test
{

protected:
    
    System eoos; ///< EOOS Operating System.    
};
    

/**
 * @relates glb_ProgramTest
 * @brief Tests the system is constructed.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Build eoos object.
 *
 * @b Assert:
 *      - Test the system is constructed.
 */
TEST_F(glb_ProgramTest, isConstructed)
{
    ASSERT_TRUE(eoos.isConstructed())     << "Error: EOOS was not constructed";
}

/**
 * @relates glb_ProgramTest
 * @brief Tests the system starts a user program and is initialiezed.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Execute the test program.
 *
 * @b Assert:
 *      - Test the program is executed with correcet exit code.
 */
TEST_F(glb_ProgramTest, execute)
{
    ASSERT_EQ(eoos.execute(), PROGRAM_OK) << "Fatal: Program is not executed";
}

/**
 * @relates glb_ProgramTest
 * @brief Tests the system starts a user program and is initialiezed.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Execute the test program.
 *
 * @b Assert:
 *      - Test the program is executed with correcet exit code.
 */
TEST_F(glb_ProgramTest, execute_args0)
{    
    char_t* argv[] = {NULLPTR};
    int32_t argc( 0 );
    ASSERT_EQ(eoos.execute(argc, argv), PROGRAM_OK) << "Fatal: Program is not executed";
}
    
/**
 * @relates glb_ProgramTest
 * @brief Tests the system starts a user program and is initialiezed.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Execute the test program.
 *
 * @b Assert:
 *      - Test the program is executed with correcet exit code.
 */
TEST_F(glb_ProgramTest, execute_args1)
{    
    char_t ARG0[] = {"ARG0"};
    char_t* argv[] = {ARG0, NULLPTR};
    int32_t argc( 1 );
    ASSERT_EQ(eoos.execute(argc, argv), PROGRAM_WRONG_ARGS) << "Fatal: Program arguments is not wrong";
}

/**
 * @relates glb_ProgramTest
 * @brief Tests the system starts a user program and is initialiezed.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Execute the test program.
 *
 * @b Assert:
 *      - Test the program is executed with correcet exit code.
 */
TEST_F(glb_ProgramTest, execute_args2)
{    
    char_t ARG0[] = {"ARG0"};
    char_t ARG1[] = {"ARG1"};
    char_t* argv[] = {ARG0, ARG1, NULLPTR};
    int32_t argc( 2 );
    ASSERT_EQ(eoos.execute(argc, argv), argc) << "Fatal: Program arguments is not wrong";
}
    
/**
 * @relates glb_ProgramTest
 * @brief Tests the system starts a user program and is initialiezed.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Execute the test program.
 *
 * @b Assert:
 *      - Test the program is executed with correcet exit code.
 */
TEST_F(glb_ProgramTest, execute_negativeArgv)
{    
    char_t ARG0[] = {"ARG0"};
    char_t ARG1[] = {"ARG1"};
    char_t* argv[] = {ARG0, ARG1, NULLPTR};
    int32_t argc( -2 );
    ASSERT_EQ(eoos.execute(argc, argv), PROGRAM_ERROR_ARGUMENT) << "Fatal: Program no argumnets error";
}

/**
 * @relates glb_ProgramTest
 * @brief Tests the system starts a user program and is initialiezed.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Execute the test program.
 *
 * @b Assert:
 *      - Test the program is executed with correcet exit code.
 */
TEST_F(glb_ProgramTest, execute_wrongArgv)
{    
    char_t ARG0[] = {"ARG0"};
    char_t ARG1[] = {"ARG1"};
    char_t* argv[] = {ARG0, ARG1, NULLPTR};
    int32_t argc( 5 );
    ASSERT_EQ(eoos.execute(argc, argv), PROGRAM_ERROR_ARGUMENT) << "Fatal: Program no argumnets error";
}
    
/**
 * @relates glb_ProgramTest
 * @brief Tests the system starts a user program and is initialiezed.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Execute the test program.
 *
 * @b Assert:
 *      - Test the system is initialized.
 *      - Test the program is executed with correcet exit code.
 */
TEST_F(glb_ProgramTest, execute_wrongArgc)
{    
    char_t ARG0[] = {"ARG0"};
    char_t ARG2[] = {"ARG2"};
    char_t* argv[] = {ARG0, NULLPTR, ARG2, NULLPTR};
    int32_t argc( 3 );
    ASSERT_EQ(eoos.execute(argc, argv), PROGRAM_ERROR_ARGUMENT) << "Fatal: Program no argumnets error";
}

/**
 * @relates glb_ProgramTest
 * @brief Tests the system starts a user program and is initialiezed.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Execute the test program.
 *
 * @b Assert:
 *      - Test the program is executed with correcet exit code.
 */
TEST_F(glb_ProgramTest, execute_noNullTerminatedArgc)
{    
    // @note Involve ARGX to be sure a previous call with possible NULL on the same possition overrided.
    char_t ARGX[] = {"ARGX"};    
    char_t ARG0[] = {"ARG0"};
    char_t ARG1[] = {"ARG1"};
    char_t* argv[] = {ARG0, ARG1, ARGX};
    int32_t argc( 2 );
    ASSERT_EQ(eoos.execute(argc, argv), PROGRAM_ERROR_ARGUMENT) << "Fatal: Program no argumnets error";
}

/**
 * @relates glb_ProgramTest
 * @brief Tests the system starts a user program and is initialiezed.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Execute the test program.
 *
 * @b Assert:
 *      - Test the program is executed with correcet exit code.
 */
TEST_F(glb_ProgramTest, execute_nullArgc)
{    
    int32_t argc( 2 );
    ASSERT_EQ(eoos.execute(argc, NULLPTR), PROGRAM_ERROR_ARGUMENT) << "Fatal: Program no argumnets error";
}

} // namespace eoos
