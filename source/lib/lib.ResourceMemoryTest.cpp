/**
 * @file      lib.ResourceMemoryTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2024, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::ResourceMemory`.
 */
#include "lib.ResourceMemory.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{

/**
 * @class lib_ResourceMemoryTest
 * @test ResourceMemory
 * @brief Tests ResourceMemory class functionality.
 */
class lib_ResourceMemoryTest : public ::testing::Test
{

private:
    
    System eoos_; ///< EOOS Operating System.
};    

/**
 * @relates lib_ResourceMemoryTest
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
TEST_F(lib_ResourceMemoryTest, Constructor)
{
}

} // namespace lib
} // namespace eoos
