/**
 * @file      lib.CharTraitTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib.CharTrait`. 
 */
#include "lib.CharTrait.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{
    
/**
 * @class lib_CharTrait
 * @test CharTrait
 * @brief Tests CharTrait class functionality.
 */
class lib_CharTrait : public ::testing::Test
{

private:
    
    System eoos_; ///< EOOS Operating System.    
};    
    
/**
 * @relates lib_CharTrait
 * @brief Tests string terminator.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Get terminator.
 *
 * @b Assert:
 *      - Test the terminator is valid.
 */
TEST_F(lib_CharTrait, getTerminator)
{
    EXPECT_EQ(CharTrait<char_t>::getTerminator(), '\0') << "Fatal: Wrong terminator of char_t";
    EXPECT_EQ(CharTrait<wchar_t>::getTerminator(), L'\0') << "Fatal: Wrong terminator of wchar_t";

#if EOOS_CPP_STANDARD >= 2011
    EXPECT_EQ(CharTrait<char16_t>::getTerminator(), u'\0') << "Fatal: Wrong terminator of char16_t";
    EXPECT_EQ(CharTrait<char32_t>::getTerminator(), U'\0') << "Fatal: Wrong terminator of char32_t";
#endif // EOOS_CPP_STANDARD >= 2011

#if EOOS_CPP_STANDARD >= 2020
    EXPECT_EQ(CharTrait<char8_t>::getTerminator(), u8'\0') << "Fatal: Wrong terminator of char8_t";
#endif // EOOS_CPP_STANDARD >= 2020
}

/**
 * @relates lib_CharTrait
 * @brief Tests minus sign.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Get minus sign.
 *
 * @b Assert:
 *      - Test the sign is valid.
 */
TEST_F(lib_CharTrait, getMinusSign)
{
    EXPECT_EQ(CharTrait<char_t>::getMinusSign(), '-') << "Fatal: Wrong minus sign of char_t";
    EXPECT_EQ(CharTrait<wchar_t>::getMinusSign(), L'-') << "Fatal: Wrong minus sign of wchar_t";

#if EOOS_CPP_STANDARD >= 2011
    EXPECT_EQ(CharTrait<char16_t>::getMinusSign(), u'-') << "Fatal: Wrong minus sign of char16_t";
    EXPECT_EQ(CharTrait<char32_t>::getMinusSign(), U'-') << "Fatal: Wrong minus sign of char32_t";
#endif // EOOS_CPP_STANDARD >= 2011

#if EOOS_CPP_STANDARD >= 2020
    EXPECT_EQ(CharTrait<char8_t>::getMinusSign(), u8'-') << "Fatal: Wrong minus sign of char8_t";
#endif // EOOS_CPP_STANDARD >= 2020
}

/**
 * @relates lib_CharTrait
 * @brief Tests convertion digit to char.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - convert digit to char.
 *
 * @b Assert:
 *      - Test the char is valid.
 */
TEST_F(lib_CharTrait, convertDigitToChar)
{
    {
        EXPECT_EQ(CharTrait<char_t>::convertDigitToChar(0),   '0') << "Fatal: Wrong digit char of char_t";
        EXPECT_EQ(CharTrait<char_t>::convertDigitToChar(1),   '1') << "Fatal: Wrong digit char of char_t";
        EXPECT_EQ(CharTrait<char_t>::convertDigitToChar(2),   '2') << "Fatal: Wrong digit char of char_t";
        EXPECT_EQ(CharTrait<char_t>::convertDigitToChar(3),   '3') << "Fatal: Wrong digit char of char_t";
        EXPECT_EQ(CharTrait<char_t>::convertDigitToChar(4),   '4') << "Fatal: Wrong digit char of char_t";
        EXPECT_EQ(CharTrait<char_t>::convertDigitToChar(5),   '5') << "Fatal: Wrong digit char of char_t";
        EXPECT_EQ(CharTrait<char_t>::convertDigitToChar(6),   '6') << "Fatal: Wrong digit char of char_t";
        EXPECT_EQ(CharTrait<char_t>::convertDigitToChar(7),   '7') << "Fatal: Wrong digit char of char_t";
        EXPECT_EQ(CharTrait<char_t>::convertDigitToChar(8),   '8') << "Fatal: Wrong digit char of char_t";
        EXPECT_EQ(CharTrait<char_t>::convertDigitToChar(9),   '9') << "Fatal: Wrong digit char of char_t";
        EXPECT_EQ(CharTrait<char_t>::convertDigitToChar(0xA), 'a') << "Fatal: Wrong digit char of char_t";
        EXPECT_EQ(CharTrait<char_t>::convertDigitToChar(0xB), 'b') << "Fatal: Wrong digit char of char_t";
        EXPECT_EQ(CharTrait<char_t>::convertDigitToChar(0xC), 'c') << "Fatal: Wrong digit char of char_t";
        EXPECT_EQ(CharTrait<char_t>::convertDigitToChar(0xD), 'd') << "Fatal: Wrong digit char of char_t";
        EXPECT_EQ(CharTrait<char_t>::convertDigitToChar(0xE), 'e') << "Fatal: Wrong digit char of char_t";
        EXPECT_EQ(CharTrait<char_t>::convertDigitToChar(0xF), 'f') << "Fatal: Wrong digit char of char_t";
        EXPECT_EQ(CharTrait<char_t>::convertDigitToChar(-1),  ' ') << "Fatal: Wrong digit char of char_t";
        EXPECT_EQ(CharTrait<char_t>::convertDigitToChar(16),  ' ') << "Fatal: Wrong digit char of char_t";
    }
    {
        EXPECT_EQ(CharTrait<wchar_t>::convertDigitToChar(0),   L'0') << "Fatal: Wrong digit char of wchar_t";
        EXPECT_EQ(CharTrait<wchar_t>::convertDigitToChar(1),   L'1') << "Fatal: Wrong digit char of wchar_t";
        EXPECT_EQ(CharTrait<wchar_t>::convertDigitToChar(2),   L'2') << "Fatal: Wrong digit char of wchar_t";
        EXPECT_EQ(CharTrait<wchar_t>::convertDigitToChar(3),   L'3') << "Fatal: Wrong digit char of wchar_t";
        EXPECT_EQ(CharTrait<wchar_t>::convertDigitToChar(4),   L'4') << "Fatal: Wrong digit char of wchar_t";
        EXPECT_EQ(CharTrait<wchar_t>::convertDigitToChar(5),   L'5') << "Fatal: Wrong digit char of wchar_t";
        EXPECT_EQ(CharTrait<wchar_t>::convertDigitToChar(6),   L'6') << "Fatal: Wrong digit char of wchar_t";
        EXPECT_EQ(CharTrait<wchar_t>::convertDigitToChar(7),   L'7') << "Fatal: Wrong digit char of wchar_t";
        EXPECT_EQ(CharTrait<wchar_t>::convertDigitToChar(8),   L'8') << "Fatal: Wrong digit char of wchar_t";
        EXPECT_EQ(CharTrait<wchar_t>::convertDigitToChar(9),   L'9') << "Fatal: Wrong digit char of wchar_t";
        EXPECT_EQ(CharTrait<wchar_t>::convertDigitToChar(0xA), L'a') << "Fatal: Wrong digit char of wchar_t";
        EXPECT_EQ(CharTrait<wchar_t>::convertDigitToChar(0xB), L'b') << "Fatal: Wrong digit char of wchar_t";
        EXPECT_EQ(CharTrait<wchar_t>::convertDigitToChar(0xC), L'c') << "Fatal: Wrong digit char of wchar_t";
        EXPECT_EQ(CharTrait<wchar_t>::convertDigitToChar(0xD), L'd') << "Fatal: Wrong digit char of wchar_t";
        EXPECT_EQ(CharTrait<wchar_t>::convertDigitToChar(0xE), L'e') << "Fatal: Wrong digit char of wchar_t";
        EXPECT_EQ(CharTrait<wchar_t>::convertDigitToChar(0xF), L'f') << "Fatal: Wrong digit char of wchar_t";
        EXPECT_EQ(CharTrait<wchar_t>::convertDigitToChar(-1),  L' ') << "Fatal: Wrong digit char of wchar_t";
        EXPECT_EQ(CharTrait<wchar_t>::convertDigitToChar(16),  L' ') << "Fatal: Wrong digit char of wchar_t";
    }

#if EOOS_CPP_STANDARD >= 2011
    {
        EXPECT_EQ(CharTrait<char16_t>::convertDigitToChar(0),   u'0') << "Fatal: Wrong digit char of char16_t";
        EXPECT_EQ(CharTrait<char16_t>::convertDigitToChar(1),   u'1') << "Fatal: Wrong digit char of char16_t";
        EXPECT_EQ(CharTrait<char16_t>::convertDigitToChar(2),   u'2') << "Fatal: Wrong digit char of char16_t";
        EXPECT_EQ(CharTrait<char16_t>::convertDigitToChar(3),   u'3') << "Fatal: Wrong digit char of char16_t";
        EXPECT_EQ(CharTrait<char16_t>::convertDigitToChar(4),   u'4') << "Fatal: Wrong digit char of char16_t";
        EXPECT_EQ(CharTrait<char16_t>::convertDigitToChar(5),   u'5') << "Fatal: Wrong digit char of char16_t";
        EXPECT_EQ(CharTrait<char16_t>::convertDigitToChar(6),   u'6') << "Fatal: Wrong digit char of char16_t";
        EXPECT_EQ(CharTrait<char16_t>::convertDigitToChar(7),   u'7') << "Fatal: Wrong digit char of char16_t";
        EXPECT_EQ(CharTrait<char16_t>::convertDigitToChar(8),   u'8') << "Fatal: Wrong digit char of char16_t";
        EXPECT_EQ(CharTrait<char16_t>::convertDigitToChar(9),   u'9') << "Fatal: Wrong digit char of char16_t";
        EXPECT_EQ(CharTrait<char16_t>::convertDigitToChar(0xA), u'a') << "Fatal: Wrong digit char of char16_t";
        EXPECT_EQ(CharTrait<char16_t>::convertDigitToChar(0xB), u'b') << "Fatal: Wrong digit char of char16_t";
        EXPECT_EQ(CharTrait<char16_t>::convertDigitToChar(0xC), u'c') << "Fatal: Wrong digit char of char16_t";
        EXPECT_EQ(CharTrait<char16_t>::convertDigitToChar(0xD), u'd') << "Fatal: Wrong digit char of char16_t";
        EXPECT_EQ(CharTrait<char16_t>::convertDigitToChar(0xE), u'e') << "Fatal: Wrong digit char of char16_t";
        EXPECT_EQ(CharTrait<char16_t>::convertDigitToChar(0xF), u'f') << "Fatal: Wrong digit char of char16_t";
        EXPECT_EQ(CharTrait<char16_t>::convertDigitToChar(-1),  u' ') << "Fatal: Wrong digit char of char16_t";
        EXPECT_EQ(CharTrait<char16_t>::convertDigitToChar(16),  u' ') << "Fatal: Wrong digit char of char16_t";
    }
    {
        EXPECT_EQ(CharTrait<char32_t>::convertDigitToChar(0),   U'0') << "Fatal: Wrong digit char of char32_t";
        EXPECT_EQ(CharTrait<char32_t>::convertDigitToChar(1),   U'1') << "Fatal: Wrong digit char of char32_t";
        EXPECT_EQ(CharTrait<char32_t>::convertDigitToChar(2),   U'2') << "Fatal: Wrong digit char of char32_t";
        EXPECT_EQ(CharTrait<char32_t>::convertDigitToChar(3),   U'3') << "Fatal: Wrong digit char of char32_t";
        EXPECT_EQ(CharTrait<char32_t>::convertDigitToChar(4),   U'4') << "Fatal: Wrong digit char of char32_t";
        EXPECT_EQ(CharTrait<char32_t>::convertDigitToChar(5),   U'5') << "Fatal: Wrong digit char of char32_t";
        EXPECT_EQ(CharTrait<char32_t>::convertDigitToChar(6),   U'6') << "Fatal: Wrong digit char of char32_t";
        EXPECT_EQ(CharTrait<char32_t>::convertDigitToChar(7),   U'7') << "Fatal: Wrong digit char of char32_t";
        EXPECT_EQ(CharTrait<char32_t>::convertDigitToChar(8),   U'8') << "Fatal: Wrong digit char of char32_t";
        EXPECT_EQ(CharTrait<char32_t>::convertDigitToChar(9),   U'9') << "Fatal: Wrong digit char of char32_t";
        EXPECT_EQ(CharTrait<char32_t>::convertDigitToChar(0xA), U'a') << "Fatal: Wrong digit char of char32_t";
        EXPECT_EQ(CharTrait<char32_t>::convertDigitToChar(0xB), U'b') << "Fatal: Wrong digit char of char32_t";
        EXPECT_EQ(CharTrait<char32_t>::convertDigitToChar(0xC), U'c') << "Fatal: Wrong digit char of char32_t";
        EXPECT_EQ(CharTrait<char32_t>::convertDigitToChar(0xD), U'd') << "Fatal: Wrong digit char of char32_t";
        EXPECT_EQ(CharTrait<char32_t>::convertDigitToChar(0xE), U'e') << "Fatal: Wrong digit char of char32_t";
        EXPECT_EQ(CharTrait<char32_t>::convertDigitToChar(0xF), U'f') << "Fatal: Wrong digit char of char32_t";
        EXPECT_EQ(CharTrait<char32_t>::convertDigitToChar(-1),  U' ') << "Fatal: Wrong digit char of char32_t";
        EXPECT_EQ(CharTrait<char32_t>::convertDigitToChar(16),  U' ') << "Fatal: Wrong digit char of char32_t";
    }
#endif // EOOS_CPP_STANDARD >= 2011

#if EOOS_CPP_STANDARD >= 2020
    {
        EXPECT_EQ(CharTrait<char8_t>::convertDigitToChar(0),   u8'0') << "Fatal: Wrong digit char of char8_t";
        EXPECT_EQ(CharTrait<char8_t>::convertDigitToChar(1),   u8'1') << "Fatal: Wrong digit char of char8_t";
        EXPECT_EQ(CharTrait<char8_t>::convertDigitToChar(2),   u8'2') << "Fatal: Wrong digit char of char8_t";
        EXPECT_EQ(CharTrait<char8_t>::convertDigitToChar(3),   u8'3') << "Fatal: Wrong digit char of char8_t";
        EXPECT_EQ(CharTrait<char8_t>::convertDigitToChar(4),   u8'4') << "Fatal: Wrong digit char of char8_t";
        EXPECT_EQ(CharTrait<char8_t>::convertDigitToChar(5),   u8'5') << "Fatal: Wrong digit char of char8_t";
        EXPECT_EQ(CharTrait<char8_t>::convertDigitToChar(6),   u8'6') << "Fatal: Wrong digit char of char8_t";
        EXPECT_EQ(CharTrait<char8_t>::convertDigitToChar(7),   u8'7') << "Fatal: Wrong digit char of char8_t";
        EXPECT_EQ(CharTrait<char8_t>::convertDigitToChar(8),   u8'8') << "Fatal: Wrong digit char of char8_t";
        EXPECT_EQ(CharTrait<char8_t>::convertDigitToChar(9),   u8'9') << "Fatal: Wrong digit char of char8_t";
        EXPECT_EQ(CharTrait<char8_t>::convertDigitToChar(0xA), u8'a') << "Fatal: Wrong digit char of char8_t";
        EXPECT_EQ(CharTrait<char8_t>::convertDigitToChar(0xB), u8'b') << "Fatal: Wrong digit char of char8_t";
        EXPECT_EQ(CharTrait<char8_t>::convertDigitToChar(0xC), u8'c') << "Fatal: Wrong digit char of char8_t";
        EXPECT_EQ(CharTrait<char8_t>::convertDigitToChar(0xD), u8'd') << "Fatal: Wrong digit char of char8_t";
        EXPECT_EQ(CharTrait<char8_t>::convertDigitToChar(0xE), u8'e') << "Fatal: Wrong digit char of char8_t";
        EXPECT_EQ(CharTrait<char8_t>::convertDigitToChar(0xF), u8'f') << "Fatal: Wrong digit char of char8_t";
        EXPECT_EQ(CharTrait<char8_t>::convertDigitToChar(-1),  u8' ') << "Fatal: Wrong digit char of char8_t";
        EXPECT_EQ(CharTrait<char8_t>::convertDigitToChar(16),  u8' ') << "Fatal: Wrong digit char of char8_t";
    }
#endif // EOOS_CPP_STANDARD >= 2020
}

} // namespace lib
} // namespace eoos
