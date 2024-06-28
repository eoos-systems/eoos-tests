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
            Value       : 15;
            Value dbf   : 1;
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
    const YourRegister::Value VAL(0x812180A5);
    YourRegister mem(VAL);
    Register<YourRegister> reg(mem);
    EXPECT_EQ(reg.value(), VAL) << "Fatal: Value of register is wrong";
}

/**
 * @relates lib_RegisterTest
 * @brief Tests register bit values.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the function is correct.
 */
TEST_F(lib_RegisterTest, bit)
{
    const YourRegister::Value VAL(0x800080A5);
    YourRegister mem(VAL);
    {
        Register<YourRegister> reg(mem);
        EXPECT_EQ(reg.bit().inrq , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().sleep, 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().txfp , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().rflm , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().nart , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";

        reg.bit().inrq = 0;
        EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().sleep, 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().txfp , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().rflm , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().nart , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";
        
        reg.bit().sleep = 1;
        EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().txfp , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().rflm , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().nart , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";

        reg.bit().txfp = 0;
        EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().rflm , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().nart , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";

        reg.bit().rflm = 1;
        EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().nart , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";

        reg.bit().nart = 1;
        EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().nart , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";

        reg.bit().awum = 0;
        EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().nart , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().awum , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";

        reg.bit().abom = 1;
        EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().nart , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().awum , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().abom , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";

        reg.bit().ttcm = 0;
        EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().nart , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().awum , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().abom , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().ttcm , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";

        reg.bit().reset = 0;
        EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().nart , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().awum , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().abom , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().ttcm , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().reset, 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";

        reg.bit().dbf = 0;
        EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().nart , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().awum , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().abom , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().ttcm , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().reset, 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().dbf  , 0) << "Fatal: Value of bit is wrong";        
    }
    {
        Register<YourRegister> const reg(mem);
        EXPECT_EQ(reg.bit().inrq , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().sleep, 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().txfp , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().rflm , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().nart , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
        EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";    
    }
}

/**
 * @relates lib_RegisterTest
 * @brief Tests get value function.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the function is correct.
 */
TEST_F(lib_RegisterTest, value)
{
    const YourRegister::Value VAL(0x812180A5);
    YourRegister mem(VAL);
    {
        Register<YourRegister> reg(mem);
        EXPECT_EQ(reg.value(), VAL) << "Fatal: Value of register is wrong";
    }
    {
        Register<YourRegister> const reg(mem);
        EXPECT_EQ(reg.value(), VAL) << "Fatal: Value of register is wrong";
    }
}

/**
 * @relates lib_RegisterTest
 * @brief Tests bit set.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the function is correct.
 */
TEST_F(lib_RegisterTest, setBit)
{
    const YourRegister::Value VAL(0x00000000);
    YourRegister mem(VAL);
    Register<YourRegister> reg(mem);
    
    EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x00000000) << "Fatal: Value of register is wrong";
    
    reg.setBit(0);
    EXPECT_EQ(reg.bit().inrq , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x00000001) << "Fatal: Value of register is wrong";

    reg.setBit(1);
    EXPECT_EQ(reg.bit().inrq , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x00000003) << "Fatal: Value of register is wrong";
    
    reg.setBit(2);
    EXPECT_EQ(reg.bit().inrq , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x00000007) << "Fatal: Value of register is wrong";

    reg.setBit(3);
    EXPECT_EQ(reg.bit().inrq , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x0000000F) << "Fatal: Value of register is wrong";

    reg.setBit(4);
    EXPECT_EQ(reg.bit().inrq , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x0000001F) << "Fatal: Value of register is wrong";

    reg.setBit(5);
    EXPECT_EQ(reg.bit().inrq , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x0000003F) << "Fatal: Value of register is wrong";

    reg.setBit(6);
    EXPECT_EQ(reg.bit().inrq , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x0000007F) << "Fatal: Value of register is wrong";

    reg.setBit(7);
    EXPECT_EQ(reg.bit().inrq , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x000000FF) << "Fatal: Value of register is wrong";

    reg.setBit(15);
    EXPECT_EQ(reg.bit().inrq , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x000080FF) << "Fatal: Value of register is wrong";

    reg.setBit(31);
    EXPECT_EQ(reg.bit().inrq , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x800080FF) << "Fatal: Value of register is wrong";
    
    reg.setBit(23);
    EXPECT_EQ(reg.bit().inrq , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x808080FF) << "Fatal: Value of register is wrong";    
}

/**
 * @relates lib_RegisterTest
 * @brief Tests bit clear.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the function is correct.
 */
TEST_F(lib_RegisterTest, clearBit)
{
    const YourRegister::Value VAL(0x808080FF);
    YourRegister mem(VAL);
    Register<YourRegister> reg(mem);
    
    EXPECT_EQ(reg.bit().inrq , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x808080FF) << "Fatal: Value of register is wrong";
    
    reg.clearBit(0);
    EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x808080FE) << "Fatal: Value of register is wrong";

    reg.clearBit(1);
    EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x808080FC) << "Fatal: Value of register is wrong";
    
    reg.clearBit(2);
    EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x808080F8) << "Fatal: Value of register is wrong";

    reg.clearBit(3);
    EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x808080F0) << "Fatal: Value of register is wrong";

    reg.clearBit(4);
    EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x808080E0) << "Fatal: Value of register is wrong";

    reg.clearBit(5);
    EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x808080C0) << "Fatal: Value of register is wrong";

    reg.clearBit(6);
    EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x80808080) << "Fatal: Value of register is wrong";

    reg.clearBit(7);
    EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x80808000) << "Fatal: Value of register is wrong";

    reg.clearBit(15);
    EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x80800000) << "Fatal: Value of register is wrong";

    reg.clearBit(31);
    EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x00800000) << "Fatal: Value of register is wrong";
    
    reg.clearBit(23);
    EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.value(), 0x00000000) << "Fatal: Value of register is wrong";    
}

/**
 * @relates lib_RegisterTest
 * @brief Tests commit to memory.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the function is correct.
 */
TEST_F(lib_RegisterTest, commit)
{
    const YourRegister::Value VAL(0x800080FF);
    YourRegister mem(VAL);
    Register<YourRegister> reg(mem);
    
    EXPECT_EQ(mem.bit.inrq , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.sleep, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.txfp , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.rflm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.nart , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.awum , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.abom , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.ttcm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.reset, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.dbf  , 1) << "Fatal: Value of bit is wrong";

    reg.bit().inrq  = 0;
    reg.bit().sleep = 0;
    reg.bit().txfp  = 0;
    reg.bit().rflm  = 0;
    reg.bit().nart  = 0;
    reg.bit().awum  = 0;
    reg.bit().abom  = 0;
    reg.bit().ttcm  = 0;
    reg.bit().reset = 0;
    reg.bit().dbf   = 0;

    EXPECT_EQ(mem.bit.inrq , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.sleep, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.txfp , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.rflm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.nart , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.awum , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.abom , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.ttcm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.reset, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.dbf  , 1) << "Fatal: Value of bit is wrong";

    reg.commit();

    EXPECT_EQ(mem.bit.inrq , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.sleep, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.txfp , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.rflm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.nart , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.awum , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.abom , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.ttcm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.reset, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(mem.bit.dbf  , 0) << "Fatal: Value of bit is wrong";   
}

/**
 * @relates lib_RegisterTest
 * @brief Tests fetch from memory.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the function is correct.
 */
TEST_F(lib_RegisterTest, fetch)
{
    const YourRegister::Value VAL(0x800080FF);
    YourRegister mem(VAL);
    Register<YourRegister> reg(mem);
    
    EXPECT_EQ(reg.bit().inrq , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";

    mem.bit.inrq  = 0;
    mem.bit.sleep = 0;
    mem.bit.txfp  = 0;
    mem.bit.rflm  = 0;
    mem.bit.nart  = 0;
    mem.bit.awum  = 0;
    mem.bit.abom  = 0;
    mem.bit.ttcm  = 0;
    mem.bit.reset = 0;
    mem.bit.dbf   = 0;

    EXPECT_EQ(reg.bit().inrq , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 1) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 1) << "Fatal: Value of bit is wrong";

    reg.fetch();

    EXPECT_EQ(reg.bit().inrq , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().sleep, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().txfp , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().rflm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().nart , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().awum , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().abom , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().ttcm , 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().reset, 0) << "Fatal: Value of bit is wrong";
    EXPECT_EQ(reg.bit().dbf  , 0) << "Fatal: Value of bit is wrong";   
}

} // namespace lib
} // namespace eoos
