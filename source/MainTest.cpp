/**
 * @file      MainTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020-2021, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `main`. 
 */
#include "Program.hpp"
#include "System.hpp"

namespace eoos
{

static const int32_t PROGRAM_OK           {777}; ///< Correct program exit code.
static const int32_t PROGRAM_WRONG_ARGS   {666}; ///< Wrong program exit code.

/**
 * @copydoc eoos::Object::Program::start(const api::List<char_t*>*)
 */
int32_t Program::start(api::List<char_t*> const* args)
{
    if(args->getLength() != 0)
    {
        return PROGRAM_WRONG_ARGS;
    }
    return PROGRAM_OK;
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
TEST_F(glb_MainTest, execute)
{
    int32_t const error { eoos.execute() };
    ASSERT_TRUE(eoos.isInitialized())  << "Error: EOOS was not initialized";
    ASSERT_EQ(PROGRAM_OK, error)       << "Fatal: Program was not started";
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
    // Output of C++ Language.
    #if   EOOS_CPP_STANDARD == 1998
        std::cout << "LANGUAGE: C++98" << std::endl;
    #elif EOOS_CPP_STANDARD == 2011
        std::cout << "LANGUAGE: C++11" << std::endl;
    #elif EOOS_CPP_STANDARD == 2014
        std::cout << "LANGUAGE: C++14" << std::endl;
    #elif EOOS_CPP_STANDARD 2017
        std::cout << "LANGUAGE: C++17" << std::endl;
    #elif EOOS_CPP_STANDARD 2020
        std::cout << "LANGUAGE: C++20" << std::endl;
    #else        
        std::cout << "LANGUAGE: unknown" << std::endl;
    #endif
    
    // Output of Data Model of a hardware system.  
    #if defined (EOOS_TYPE_STDLIB)
        std::cout << "DATA MODEL: C++ Standard Library types" << std::endl;
    #elif defined (EOOS_TYPE_WIDTH_LP32)
        std::cout << "DATA MODEL: LP32 or 2/4/4 (int is 16-bit, long and pointer are 32-bit)" << std::endl;
    #elif defined (EOOS_TYPE_WIDTH_ILP32)
        std::cout << "DATA MODEL: ILP32 or 4/4/4 (int, long, and pointer are 32-bit)" << std::endl;
    #elif defined (EOOS_TYPE_WIDTH_LLP64)
        std::cout << "DATA MODEL: LLP64 or 4/4/8 (int and long are 32-bit, pointer is 64-bit)" << std::endl;
    #elif defined (EOOS_TYPE_WIDTH_LP64)
        std::cout << "DATA MODEL: LP64 or 4/8/8 (int is 32-bit, long and pointer are 64-bit)" << std::endl;
    #else
        std::cout << "DATA MODEL: C++ standard" << std::endl;
    #endif

    // MISRA-C++:2008 rules restrictions.  
    #if defined (EOOS_NO_STRICT_MISRA_RULES)
        std::cout << "MISRA-C++:2008 rules are not strict" << std::endl;
    #endif
    
    ::testing::InitGoogleTest(&argc, argv);
    int const error { RUN_ALL_TESTS() };
    return error;
}
