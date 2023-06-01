/**
 * @file      MainTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit of `main`. 
 */
#include "Program.hpp"
#include "System.hpp"

namespace eoos
{

/**
 * @copydoc eoos::Object::Program::start(const api::List<char_t*>*)
 */
int32_t Program::start(int32_t argc, char_t* argv[])
{
    return 0;
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
    ::testing::InitGoogleTest(&argc, argv);
    int const error( RUN_ALL_TESTS() );
    return error;
}
