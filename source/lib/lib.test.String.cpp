/**
 * @file      lib.test.String.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020-2021, Sergey Baigudin, Baigudin Software
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
namespace test
{
    
class test_lib_String : public ::testing::Test
{

protected:
    
    System eoos;    
};    

TEST_F(test_lib_String, Constructor)
{
    String const obj;
    EXPECT_TRUE(obj.isConstructed())     << "Error: Object is not conctructed";    
}

} // namespace test
} // namespace lib
} // namespace eoos

#endif // EOOS_NO_STRICT_MISRA_RULES
