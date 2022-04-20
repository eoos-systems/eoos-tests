/**
 * @file      lib.BufferTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Buffer`. 
 */
#include "lib.Buffer.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{
    
/**
 * @class lib_BufferTest
 * @test Buffer
 * @brief Tests Buffer class functionality.
 */
class lib_BufferTest : public ::testing::Test
{
protected:

    typedef int32_t Type;

private:
    
    System eoos_; ///< EOOS Operating System.    
};    

/**
 * @relates lib_BufferTest
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
TEST_F(lib_BufferTest, Constructor)
{
    Buffer<Type,3> obj;
    EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";    
}

} // namespace lib
} // namespace eoos
