/**
 * @file      lib.NoAllocatorTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib.NoAllocator`. 
 */
#include "lib.NoAllocator.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{
    
/**
 * @class lib_NoAllocator
 * @test NoAllocator
 * @brief Tests NoAllocator class functionality.
 */
class lib_NoAllocator : public ::testing::Test
{

private:
    
    System eoos_; ///< EOOS Operating System.    
};    
    
/**
 * @relates lib_NoAllocator
 * @brief Tests no memory allocation.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Allocate memory.
 *
 * @b Assert:
 *      - Test the memory is not allocated.
 */
TEST_F(lib_NoAllocator, allocate)
{
    EXPECT_EQ(NoAllocator::allocate(0), NULLPTR) << "Fatal: Memory allocated";    
    EXPECT_EQ(NoAllocator::allocate(770), NULLPTR) << "Fatal: Memory allocated";
    NoAllocator::free(NULLPTR);
}

} // namespace lib
} // namespace eoos
