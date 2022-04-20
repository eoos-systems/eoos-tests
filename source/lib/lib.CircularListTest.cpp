/**
 * @file      lib.CircularListTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::CircularList`. 
 */
#include "lib.CircularList.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{
    
/**
 * @class lib_CircularListTest
 * @test CircularList
 * @brief Tests CircularList class functionality.
 */
class lib_CircularListTest : public ::testing::Test
{
protected:

    typedef int32_t Type;

private:
    
    System eoos_; ///< EOOS Operating System.    
};    

/**
 * @relates lib_CircularListTest
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
TEST_F(lib_CircularListTest, Constructor)
{
    CircularList<Type> obj;
    EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
}

} // namespace lib
} // namespace eoos
