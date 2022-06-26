/**
 * @file      lib.MutexGuardTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::MutexGuard`. 
 */
#include "lib.MutexGuard.hpp"
#include "lib.AbstractThreadTask.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{
namespace
{
    
const int64_t GUARD_LOCKED        (0x5555555555555555);
const int64_t GUARD_NOT_LOCKED    (0x5AAAAAAAAAAAAAAA);    
const int64_t GUARD_TIMEOUT       (0x7FFFFFFFFFFFFFFF);
const int64_t GUARD_UNKNOWN_VALUE (0x7EEEEEEEEEEEEEEE);
const int64_t GUARD_INIT_VALUE    (0x0000000000000000);

} // namespace
    
/**
 * @class lib_MutexGuardTest
 * @test Mutex
 * @brief Tests Mutex class functionality.
 */
class lib_MutexGuardTest : public ::testing::Test
{

protected:

    /**
     * @class Task
     * @brief Semaphore task for the test.
     */
    class ThreadTask : public AbstractThreadTask<>
    {
        typedef AbstractThreadTask<> Parent;
    
    public:
            
        /**
         * @brief Constructor.
         *
         * @param permits The initial number of permits available.
         */
        ThreadTask(api::Mutex& mutex) : Parent(),
            isRegisterRead_ (false),
            register_ (GUARD_INIT_VALUE),
            mutex_ (mutex){
        }

        /**
         * @brief Reads the register.
         *
         * @return Register value.
         */
        int64_t readRegister()
        {
            return register_;
        }

        /**
         * @brief Set register read.
         */        
        void setRegisterRead()
        {
            isRegisterRead_ = true;
        }
        
    private:    
            
        /**
         * @copydoc eoos::api::Task::start()
         */        
        virtual void start()
        {
            MutexGuard<> guard(mutex_);
            if(guard.isConstructed())
            {
                register_ = GUARD_LOCKED;
                for(uint32_t i=0; i<TESTS_WAIT_CYCLE_TIME; i++)
                {
                    if(isRegisterRead_)
                    {
                        break;
                    }
                }
                if( !isRegisterRead_ )
                {
                    register_ = GUARD_TIMEOUT;
                }
            }
            else
            {
                register_ = GUARD_NOT_LOCKED;
            }
        }
        
        bool_t volatile isRegisterRead_; ///< Register is read by primary thread.
        int64_t volatile register_;      ///< Register to access.
        api::Mutex& mutex_;              ///< Mutex to lock.
    };

private:
    
    System eoos_; ///< EOOS Operating System.    
};    
    
/**
 * @relates lib_MutexGuardTest
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
TEST_F(lib_MutexGuardTest, Constructor)
{
    Mutex<> obj;
    EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
}

/**
 * @relates lib_MutexGuardTest
 * @brief Mutex lock test. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Create a child thread
 *      - Lock mutex in the child thread
 *
 * @b Assert:
 *      - Check the mutex cannot be locked in the primary thread.
 */
TEST_F(lib_MutexGuardTest, lock)
{
    Mutex<> mutex;
    ASSERT_TRUE(mutex.tryLock()) << "Fatal: New mutex cannot be locked";
    mutex.unlock();
    ThreadTask thread(mutex);
    ASSERT_TRUE(thread.isConstructed()) << "Error: Thread for Semaphore testing is not constructed";
    ASSERT_TRUE(thread.execute()) << "Error: Thread was not executed";
    int64_t volatile registerRo(GUARD_UNKNOWN_VALUE);
    for(uint32_t i=0; i<TESTS_WAIT_CYCLE_TIME; i++)
    {
        registerRo = thread.readRegister();
        if(registerRo == GUARD_LOCKED)
        {
            break;
        }
    }
    ASSERT_NE(registerRo, GUARD_UNKNOWN_VALUE) << "Fatal: Register has not read";
    ASSERT_NE(registerRo, GUARD_NOT_LOCKED) << "Fatal: Mutex was not locked";
    ASSERT_NE(registerRo, GUARD_TIMEOUT) << "Fatal: Time is out";
    ASSERT_NE(registerRo, GUARD_INIT_VALUE) << "Fatal: Child thread control not gotten";
    ASSERT_EQ(registerRo, GUARD_LOCKED) << "Fatal: Mutex was not locked";
    ASSERT_FALSE(mutex.tryLock()) << "Fatal: Locked mutex can be locked";
    thread.setRegisterRead();
    EXPECT_TRUE(thread.join()) << "Error: Thread was not joined";
    ASSERT_TRUE(mutex.lock()) << "Fatal: Mutex cannot be locked";
    mutex.unlock();
}

} // namespace lib
} // namespace eoos
