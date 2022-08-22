/**
 * @file      MainTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020-2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `main`. 
 */
#include "Program.hpp"
#include "System.hpp"
#include "lib.Stream.hpp"
#include "lib.String.hpp"

namespace eoos
{

static const int32_t PROGRAM_OK          (777); ///< Correct program exit code.
static const int32_t PROGRAM_WRONG_ARGS  (666); ///< Wrong program exit code.

/**
 * @copydoc eoos::Object::Program::start(const api::List<char_t*>*)
 */
int32_t Program::start(api::List<char_t*>& args)
{
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
            lib::String arg0( args.get(0) );
            lib::String arg1( args.get(1) );
            if( (arg0 == "ARG0") && (arg1 == "ARG1") )
            {
                error = args.getLength();                
            }
            break;
        }            
    }
    return error;
}

/**
 * @class glb_MainTest
 * @test Call
 * @brief Tests an application on EOOS starts sucessfully.
 */
class glb_MainTest : public ::testing::Test
{

protected:
    
    System eoos; ///< EOOS Operating System.    
};
    

/**
 * @relates glb_MainTest
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
TEST_F(glb_MainTest, isConstructed)
{
    ASSERT_TRUE(eoos.isConstructed())     << "Error: EOOS was not constructed";
}

/**
 * @relates glb_MainTest
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
TEST_F(glb_MainTest, execute)
{
    ASSERT_EQ(eoos.execute(), PROGRAM_OK) << "Fatal: Program was not started";
}

/**
 * @relates glb_MainTest
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
TEST_F(glb_MainTest, execute_args0)
{    
    char_t* args[] = {NULLPTR};
    int32_t argv( 0 );
    ASSERT_EQ(eoos.execute(argv, args), PROGRAM_OK) << "Fatal: Program was not started";
}
    
/**
 * @relates glb_MainTest
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
TEST_F(glb_MainTest, execute_args1)
{    
    char_t ARG0[] = {"ARG0"};
    char_t* args[] = {ARG0, NULLPTR};
    int32_t argv( 1 );
    ASSERT_EQ(eoos.execute(argv, args), PROGRAM_WRONG_ARGS) << "Fatal: Program was not started";
}

/**
 * @relates glb_MainTest
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
TEST_F(glb_MainTest, execute_args2)
{    
    char_t ARG0[] = {"ARG0"};
    char_t ARG1[] = {"ARG1"};
    char_t* args[] = {ARG0, ARG1, NULLPTR};
    int32_t argv( 2 );
    ASSERT_EQ(eoos.execute(argv, args), argv) << "Fatal: Program was not started";
}
    
/**
 * @relates glb_MainTest
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
TEST_F(glb_MainTest, execute_negativeArgv)
{    
    char_t ARG0[] = {"ARG0"};
    char_t ARG1[] = {"ARG1"};
    char_t* args[] = {ARG0, ARG1, NULLPTR};
    int32_t argv( -2 );
    ASSERT_LT(eoos.execute(argv, args), 0) << "Fatal: Program was started";
}

/**
 * @relates glb_MainTest
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
TEST_F(glb_MainTest, execute_wrongArgv)
{    
    char_t ARG0[] = {"ARG0"};
    char_t ARG1[] = {"ARG1"};
    char_t* args[] = {ARG0, ARG1, NULLPTR};
    int32_t argv( 5 );
    ASSERT_LT(eoos.execute(argv, args), 0) << "Fatal: Program was started";
}
    
/**
 * @relates glb_MainTest
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
TEST_F(glb_MainTest, execute_wrongArgc)
{    
    char_t ARG0[] = {"ARG0"};
    char_t ARG2[] = {"ARG2"};
    char_t* args[] = {ARG0, NULLPTR, ARG2, NULLPTR};
    int32_t argv( 3 );
    ASSERT_LT(eoos.execute(argv, args), 0) << "Fatal: Program was started";
}

/**
 * @relates glb_MainTest
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
TEST_F(glb_MainTest, execute_noNullTerminatedArgc)
{    
    char_t ARG0[] = {"ARG0"};
    char_t ARG1[] = {"ARG1"};
    char_t* args[] = {ARG0, ARG1};
    int32_t argv( 2 );
    ASSERT_LT(eoos.execute(argv, args), 0) << "Fatal: Program was started";
}

/**
 * @relates glb_MainTest
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
TEST_F(glb_MainTest, execute_nullArgc)
{    
    int32_t argv( 2 );
    ASSERT_LT(eoos.execute(argv, NULLPTR), 0) << "Fatal: Program was started";
}

    
/**
 * @brief Prints EOOS global configuration.
 */
static void printConfiguration()
{
    System eoos;
    lib::Stream::cout() << "WELCOME TO EOOS UNIT TESTS\n";
    // Output of C++ Language.
    #if   EOOS_CPP_STANDARD == 1998
        lib::Stream::cout() << "LANGUAGE: C++98\n";
    #elif EOOS_CPP_STANDARD == 2011
        lib::Stream::cout() << "LANGUAGE: C++11\n";
    #elif EOOS_CPP_STANDARD == 2014
        lib::Stream::cout() << "LANGUAGE: C++14\n";
    #elif EOOS_CPP_STANDARD 2017
        lib::Stream::cout() << "LANGUAGE: C++17\n";
    #elif EOOS_CPP_STANDARD 2020
        lib::Stream::cout() << "LANGUAGE: C++20\n";
    #else        
        lib::Stream::cout() << "LANGUAGE: unknown\n";
    #endif
    
    // Output of Data Model of a hardware system.  
    #if defined (EOOS_TYPE_STDLIB)
        lib::Stream::cout() << "DATA MODEL: C++ Standard Library types\n";
    #elif defined (EOOS_TYPE_WIDTH_LP32)
        lib::Stream::cout() << "DATA MODEL: LP32 or 2/4/4 (int is 16-bit, long and pointer are 32-bit)\n";
    #elif defined (EOOS_TYPE_WIDTH_ILP32)
        lib::Stream::cout() << "DATA MODEL: ILP32 or 4/4/4 (int, long, and pointer are 32-bit)\n";
    #elif defined (EOOS_TYPE_WIDTH_LLP64)
        lib::Stream::cout() << "DATA MODEL: LLP64 or 4/4/8 (int and long are 32-bit, pointer is 64-bit)\n";
    #elif defined (EOOS_TYPE_WIDTH_LP64)
        lib::Stream::cout() << "DATA MODEL: LP64 or 4/8/8 (int is 32-bit, long and pointer are 64-bit)\n";
    #else
        lib::Stream::cout() << "DATA MODEL: C++ standard\n";
    #endif

    // MISRA-C++:2008 rules restrictions.  
    #if defined (EOOS_ENABLE_DYNAMIC_HEAP_MEMORY)
        lib::Stream::cout() << "ENABLE: Dynamic heap memory allocation\n";
    #else
        lib::Stream::cout() << "DISABLE: Dynamic heap memory allocation\n";        
    #endif
}

} // namespace eoos

/**
 * @brief The main function.
 *
 * This function starts all the testsuites and is defined here as the EOOS library may have 
 * its own main() function defined and this definition will make a linker link the main(). 
 *
 * @param argc  The number of arguments passed to the program.
 * @param argv  An array of c-string of arguments where the last one - argc + 1 is null.
 * @return Error code or zero.
 */
int main(int argc, char** const argv)
{    
    ::eoos::printConfiguration();
    ::testing::InitGoogleTest(&argc, argv);
    int const error( RUN_ALL_TESTS() );
    return error;
}
