/**
 * @file      lib.RegisterTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2024, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Register`.
 */
#include "lib.Register.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{

/**
 * @class lib_RegisterTest
 * @test Register
 * @brief Tests Register class functionality.
 */
class lib_RegisterTest : public ::testing::Test
{
    
protected:

    union YourRegister
    {
        typedef uint32_t Value;
        YourRegister(){}
        YourRegister(Value v){value = v;}
       ~YourRegister(){}    
      
        Value value;
        struct Bit
        {
            Value inrq  : 1;
            Value sleep : 1;
            Value txfp  : 1;
            Value rflm  : 1;
            Value nart  : 1;
            Value awum  : 1;
            Value abom  : 1;
            Value ttcm  : 1;
            Value       : 7;
            Value reset : 1;
            Value dbf   : 1;
            Value       : 15;
        } bit;
    };

private:
    
    System eoos_; ///< EOOS Operating System.
};    

/**
 * @relates lib_RegisterTest
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
TEST_F(lib_RegisterTest, Constructor)
{
    const YourRegister::Value VAL(0x000018A5);
    YourRegister mem(VAL);
    Register<YourRegister> reg(mem);
    EXPECT_EQ(reg.value(), VAL) << "Fatal: Value of register is wrong";
}

} // namespace lib
} // namespace eoos
