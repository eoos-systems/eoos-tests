/**
 * @file      lib.MemoryTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Memory`. 
 */
#include "lib.Memory.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{
    
/**
 * @class lib_MemoryTest
 * @test Memory
 * @brief Tests Memory class functionality.
 */
class lib_MemoryTest : public ::testing::Test
{
};    

/**
 * @relates lib_MemoryTest
 * @brief Tests memory operations.
 *
 * @b Arrange:
 *
 * @b Act:
 *
 * @b Assert:
 */
TEST_F(lib_MemoryTest, memcpy)
{
    uint32_t src (0x89ABCDEF);
    uint32_t dst;
    Memory::memcpy(&dst, &src, sizeof(uint32_t));
    EXPECT_EQ(src, dst) << "Fatal: Memory is not copied";
}

} // namespace lib
} // namespace eoos
