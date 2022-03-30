/**
 * @file      lib.StringTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020-2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::String`. 
 */
#include "System.hpp"
#include "lib.String.hpp"

#ifdef EOOS_NO_STRICT_MISRA_RULES

namespace eoos
{
namespace lib
{
    
/**
 * @class StringTest
 * @test String
 * @brief Tests String class functionality.
 */
class StringTest : public ::testing::Test
{

private:
    
    System eoos_; ///< EOOS Operating System.    
};    

/**
 * @relates StringTest
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
TEST_F(StringTest, Constructor)
{
    String const obj;
    EXPECT_TRUE(obj.isConstructed())     << "Error: Object is not constructed";    
}

} // namespace lib
} // namespace eoos

#endif // EOOS_NO_STRICT_MISRA_RULES
