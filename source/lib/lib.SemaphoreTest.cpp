/**
 * @file      lib.SemaphoreTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Semaphore`. 
 */
#include "lib.Semaphore.hpp"
#include "lib.AbstractThreadTask.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{

/**
 * @class lib_SemaphoreTest
 * @test Semaphore
 * @brief Tests Semaphore class functionality.
 */
class lib_SemaphoreTest : public ::testing::Test
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
         * @param semAcquire Semaphore to acquire in the thread.
         * @param semRelease Semaphore to release in the thread after the acquirement.
         */
        ThreadTask(api::Semaphore& semAcquire, api::Semaphore& semRelease) : Parent(),
            isAcquired_ (false),
            semAcquire_ (semAcquire),
            semRelease_ (semRelease){
        }

        /**
         * @brief Test if semaphore was acquired.
         *
         * @return True if semaphore was acquired.
         */        
        bool_t wasAcquired()
        {
            return isAcquired_;
        }
                        
    private:    
            
        /**
         * @copydoc eoos::api::Task::start()
         */        
        virtual void start()
        {
            isAcquired_ = semAcquire_.acquire();
            semRelease_.release();
        }
        
        bool_t isAcquired_;          ///< Acquirement flag.
        api::Semaphore& semAcquire_; ///< Semaphore to acquire in the thread.
        api::Semaphore& semRelease_; ///< Semaphore to release in the thread after the acquirement.
    };
    
private:

    System eoos_; ///< EOOS Operating System.
};  

/**
 * @relates lib_SemaphoreTest
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
TEST_F(lib_SemaphoreTest, Constructor)
{
    Semaphore<> obj(0);
    EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
}

/**
 * @relates lib_SemaphoreTest
 * @brief Test if object is constructed. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct a constructed and unconstructed objects of the class.
 *
 * @b Assert:
 *      - Test the object is constructed.
 */
TEST_F(lib_SemaphoreTest, isConstructed)
{
    {
        Semaphore<> obj(0);
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed with permits 0";
    }
    {
        Semaphore<> obj(1);
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed with permits 1";
    }
    {
        Semaphore<> obj(0x7FFFFFFF);
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed with permits 0x7FFFFFFF";
    }    
    {
        Semaphore<> obj(-1);
        EXPECT_FALSE(obj.isConstructed()) << "Fatal: Object is constructed with permits -1";
    }
    {
        Semaphore<> obj(0 - 0x7FFFFFFF -1);
        EXPECT_FALSE(obj.isConstructed()) << "Fatal: Object is constructed with minimal negative permits";
    }
}

/**
 * @relates lib_SemaphoreTest
 * @brief Semaphore acquire test. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Create a child thread
 *      - Acquire a semaphore in the child thread, and release the semaphore in the primary thread
 *      - Enter to the critiacl section in the child thread and flag the acquirement done.
 *      - Release other semaphore in the child thread and acquire it in the primary thread.
 *
 * @b Assert:
 *      - Check acquirement done in both threads.
 */
TEST_F(lib_SemaphoreTest, acquire)
{
    Semaphore<> semAcquire(0);
    Semaphore<> semRelease(0);
    ThreadTask thread(semAcquire, semRelease);
    ASSERT_TRUE(thread.isConstructed()) << "Error: Thread for Semaphore testing is not constructed";
    ASSERT_TRUE(thread.execute()) << "Error: Thread was not executed";
    semAcquire.release();
    EXPECT_TRUE(semRelease.acquire()) << "Fatal: Semaphore was not acquired in the primary thread";
    EXPECT_TRUE(thread.wasAcquired()) << "Fatal: Semaphore was not acquired in the child thread";
    EXPECT_TRUE(thread.join()) << "Error: Thread was not joined";
}

} // namespace lib
} // namespace eoos
