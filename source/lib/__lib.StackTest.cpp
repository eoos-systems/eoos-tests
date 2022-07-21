/**
 * @file      lib.StackTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Stack`. 
 */
#include "lib.Stack.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{
    
/**
 * @class lib_StackTest
 * @test Stack
 * @brief Tests Stack class functionality.
 */
class lib_StackTest : public ::testing::Test
{

protected:

    typedef uint64_t Type;

private:
    
    System eoos_; ///< EOOS Operating System.    
};    

/**
 * @relates lib_StackTest
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
TEST_F(lib_StackTest, Constructor)
{
    Stack<Type> obj(api::Stack<Type>::Operation::ED, 8);
    EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";        
}
	

/**
 * @relates lib_StackTest
 * @brief Tests the class constructor.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the stack is not empty.
 */
TEST_F(lib_StackTest, isEmpty)
{
    Stack<Type> obj(api::Stack<Type>::Operation::ED, 8);
    EXPECT_FALSE(obj.isEmpty()) << "Fatal: Object is empty";        
}

} // namespace lib
} // namespace eoos
