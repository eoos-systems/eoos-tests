/**
 * @file      lib.MutexTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Mutex`. 
 */
#include "lib.Mutex.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{
    
/**
 * @class lib_MutexTest
 * @test Mutex
 * @brief Tests Mutex class functionality.
 */
class lib_MutexTest : public ::testing::Test
{

private:
    
    System eoos_; ///< EOOS Operating System.    
};    

/**
 * @relates lib_MutexTest
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
TEST_F(lib_MutexTest, Constructor)
{
}

} // namespace lib
} // namespace eoos
