/**
 * @file      lib.MutexGuardTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::MutexGuard`. 
 */
#include "lib.MutexGuard.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{
    
/**
 * @class lib_MutexGuardTest
 * @test MutexGuard
 * @brief Tests MutexGuard class functionality.
 */
class lib_MutexGuardTest : public ::testing::Test
{

private:
    
    System eoos_; ///< EOOS Operating System.    
};    

/**
 * @relates lib_MutexGuardTest
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
TEST_F(lib_MutexGuardTest, Constructor)
{
}

} // namespace lib
} // namespace eoos
