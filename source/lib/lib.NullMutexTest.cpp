/**
 * @file      lib.NullMutexTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2026, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::NullMutex`.
 */
#include "lib.NullMutex.hpp"
#include "Tests.hpp"

namespace eoos
{
namespace lib
{

namespace
{
/**
 * @class NullMutexUnconstructed<T,L>
 *
 * @brief Unconstructed NullMutex class.
 */
class NullMutexUnconstructed : public NullMutex<>
{
    typedef NullMutex<> Parent;

public:

    /**
     * @copydoc eoos::lib::NullMutex::NullMutex()
     */
    NullMutexUnconstructed()
        : NullMutex<>() {
        setConstructed(false);
    }

protected:

    using Parent::setConstructed;

};

} // namespace

/**
 * @class lib_NullMutexTest
 * @test NullMutex
 * @brief Tests NullMutex class functionality.
 */
class lib_NullMutexTest : public ::testing::Test
{
};

/**
 * @relates lib_NullMutexTest
 * @brief Tests the class constructor.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct an object of the class.
 *
 * @b Assert:
 *      - Test the object is constructed.
 */
TEST_F(lib_NullMutexTest, Constructor)
{
    NullMutex<> const obj;
    EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
}

/**
 * @relates lib_NullMutexTest
 * @brief NullMutex lock test.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_NullMutexTest, lock)
{
    NullMutex<> mutex;
    EXPECT_TRUE(mutex.tryLock()) << "Fatal: New mutex cannot be locked";
    EXPECT_TRUE(mutex.unlock()) << "Fatal: New mutex cannot be unlocked";
    EXPECT_TRUE(mutex.lock()) << "Fatal: Mutex cannot be locked";
    EXPECT_TRUE(mutex.unlock()) << "Fatal: Mutex cannot be unlocked";
}

/**
 * @relates lib_NullMutexTest
 * @brief NullMutex lock test.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_NullMutexTest, lock_unconstructed)
{
    NullMutexUnconstructed mutex;
    EXPECT_FALSE(mutex.tryLock()) << "Fatal: New mutex can be locked";
    EXPECT_FALSE(mutex.unlock()) << "Fatal: New mutex can be unlocked";
    EXPECT_FALSE(mutex.lock()) << "Fatal: Mutex can be locked";
    EXPECT_FALSE(mutex.unlock()) << "Fatal: Mutex can be unlocked";
}

} // namespace lib
} // namespace eoos
