/**
 * @file      lib.StreamTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Stream`. 
 */
#include "lib.Stream.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{
    
/**
 * @class lib_StreamTest
 * @test Stream
 * @brief Tests Stream class functionality.
 */
class lib_StreamTest : public ::testing::Test
{

private:
    
    System eoos_; ///< EOOS Operating System.    
};    

/**
 * @relates lib_StreamTest
 * @brief Tests the class constructor.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Output a string.
 *
 * @b Assert:
 *      - Test interface exists.
 */
TEST_F(lib_StreamTest, cout)
{
    Stream::cout() << "[     TEST ] This is output to cout" << "\n";
    int32_t value( 0 );
    Stream::cout() << "[     TEST ] This is output to cout of zero integer: " << value << "\n";
    value = 2147483647;
    Stream::cout() << "[     TEST ] This is output to cout of max 2147483647 integer: " << value << "\n";
    value = -2147483647;
    Stream::cout() << "[     TEST ] This is output to cout of min -2147483647 integer: " << value << "\n";
    api::Object& stream (Stream::cout().flush());
    EXPECT_TRUE(stream.isConstructed()) << "Fatal: System cout stream is not constructed";
}

/**
 * @relates lib_StreamTest
 * @brief Tests the class constructor.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Output a string.
 *
 * @b Assert:
 *      - Test interface exists.
 */
TEST_F(lib_StreamTest, cerr)
{
    Stream::cerr() << "[     TEST ] This is output to cerr that can be colored to red" << "\n";
    int32_t value( 0 );
    Stream::cout() << "[     TEST ] This is output to cerr of zero integer: " << value << "\n";
    value = 2147483647;
    Stream::cout() << "[     TEST ] This is output to cerr of max 2147483647 integer: " << value << "\n";
    value = -2147483647;
    Stream::cout() << "[     TEST ] This is output to cerr of min -2147483647 integer: " << value << "\n";
    api::Object& stream (Stream::cerr().flush());
    EXPECT_TRUE(stream.isConstructed()) << "Fatal: System cerr stream is not constructed";

}

} // namespace lib
} // namespace eoos
