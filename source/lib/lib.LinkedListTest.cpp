/**
 * @file      lib.LinkedListTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::LinkedList`. 
 */
#include "lib.LinkedList.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{
    
/**
 * @class lib_LinkedListTest
 * @test LinkedList
 * @brief Tests LinkedList class functionality.
 */
class lib_LinkedListTest : public ::testing::Test
{

protected:

    typedef int32_t Type;

private:
    
    System eoos_; ///< EOOS Operating System.    
};    

/**
 * @relates lib_LinkedListTest
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
TEST_F(lib_LinkedListTest, Constructor)
{
    LinkedList<Type> obj;
    EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";    
}

} // namespace lib
} // namespace eoos
