/**
 * @file      lib.GuardTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022-2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Guard`. 
 */
#include "lib.Guard.hpp"
#include "lib.Mutex.hpp"
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

/**
 * @class MutexUnconstructed<A>
 *
 * @brief Class to provide protect functions to public scope.
 */
class MutexUnconstructed : public Mutex<>
{
    typedef Mutex<> Parent;

public:

    using Parent::setConstructed;
    
    MutexUnconstructed()
        : Mutex<>() {
        setConstructed(false);
    }

};

} // namespace
    
/**
 * @class lib_GuardTest
 * @test Mutex
 * @brief Tests Mutex class functionality.
 */
class lib_GuardTest : public ::testing::Test
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
            Guard<> guard(mutex_);
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

    /**
     * @class ThreadCount
     * @brief Count thread`.
     */
    class ThreadCount : public lib::AbstractThreadTask<>
    {
    
    public:

        /**
         * @enum Count
         * @brief Count direction.
         */
        enum Count
        {
            COUNT_UP,
            COUNT_DW
        };
        
        /**
         * @brief Constructor.
         *
         * @param count Count direction.
         * @param mutex Mutex resource to lock on.
         * @param resource Atomic resource.
         */
        ThreadCount(Count count, api::Mutex& mutex, int64_t& resource)
            : lib::AbstractThreadTask<>()
            , isCompleted_( false )
            , count_( count )
            , mutex_( mutex )
            , resource_( resource ) {
        }
        
        /**
         * @brief Test if counting is completed.
         *
         * @return True ii completed.
         */
        bool_t isCompleted()
        {
            return isCompleted_;
        }
            
    private:
    
        /**
         * @copydoc eoos::api::Task::start()
         */
        virtual void start()
        {
            if(count_ == COUNT_UP)
            {
                countUp();
            }
            else
            {
                countDown();
            }
        }

        /**
         * @brief Counts up.
         */
        void countUp()
        {
            {
                lib::Guard<> const guard(mutex_);
                volatile int64_t resource( resource_ );
                for(int32_t i(0); i<=MAX_COUNT; i++)
                {
                    resource++;
                }
                resource_ = resource;
            }
            isCompleted_ = true;
        }
    
        /**
         * @brief Counts down.
         */
        void countDown()
        {
            {
                lib::Guard<> const guard(mutex_);
                volatile int64_t resource( resource_ );
                for(int32_t i(MAX_COUNT); i>=0; i--)
                {
                    resource--;
                }
                resource_ = resource;
            }
            isCompleted_ = true;
        }

        /**
         * @brief Maximum count.
         */
        static const int32_t MAX_COUNT = 0x800000;        

        /**
         * @brief Complete flag.
         */
        bool_t volatile isCompleted_;

        /**
         * @brief Count direction.
         */
        Count count_;
    
        /**
         * @brief Mutex resource to lock on.
         */
        api::Mutex& mutex_;

        /**
         * @brief Atomic resource.
         */
        int64_t& resource_;
    
    };

private:
    
    System eoos_; ///< EOOS Operating System.    
};    
    
/**
 * @relates lib_GuardTest
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
TEST_F(lib_GuardTest, Constructor)
{
    {
        Mutex<> mtx;
        Guard<> obj( mtx );
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
    }
    { 
        MutexUnconstructed mtx;
        Guard<> obj( mtx );
        EXPECT_FALSE(obj.isConstructed()) << "Fatal: Object is constructed";
    }
}

/**
 * @relates lib_GuardTest
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
TEST_F(lib_GuardTest, lock)
{
    Mutex<> mutex;
    EXPECT_TRUE(mutex.tryLock()) << "Fatal: New mutex cannot be locked";
    EXPECT_TRUE(mutex.unlock()) << "Fatal: Mutex cannot be locked";
    ThreadTask thread(mutex);
    EXPECT_TRUE(thread.isConstructed()) << "Error: Thread for Semaphore testing is not constructed";
    EXPECT_TRUE(thread.execute()) << "Error: Thread was not executed";
    int64_t volatile registerRo(GUARD_UNKNOWN_VALUE);
    for(uint32_t i=0; i<TESTS_WAIT_CYCLE_TIME; i++)
    {
        registerRo = thread.readRegister();
        if(registerRo == GUARD_LOCKED)
        {
            break;
        }
    }
    EXPECT_NE(registerRo, GUARD_UNKNOWN_VALUE) << "Fatal: Register has not read";
    EXPECT_NE(registerRo, GUARD_NOT_LOCKED) << "Fatal: Mutex was not locked";
    EXPECT_NE(registerRo, GUARD_TIMEOUT) << "Fatal: Time is out";
    EXPECT_NE(registerRo, GUARD_INIT_VALUE) << "Fatal: Child thread control not gotten";
    EXPECT_EQ(registerRo, GUARD_LOCKED) << "Fatal: Mutex was not locked";
    EXPECT_FALSE(mutex.tryLock()) << "Fatal: Locked mutex can be locked";
    thread.setRegisterRead();
    EXPECT_TRUE(thread.join()) << "Error: Thread was not joined";
    EXPECT_TRUE(mutex.lock()) << "Fatal: Mutex cannot be locked";
    EXPECT_TRUE(mutex.unlock()) << "Fatal: Mutex cannot be unlocked";
}

/**
 * @relates lib_GuardTest
 * @brief Mutex atomic lock test. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Create two threads and pass them a mutex.
 *      - Run the threads to count a global variable up and down under the mutex.
 *
 * @b Assert:
 *      - Check counting complited.
 *      - Check initial value of the variable is not changed. 
 */
TEST_F(lib_GuardTest, atomic)
{
    const int64_t resVal( 770 );
    int64_t resource( resVal );
    Mutex<> mutex;
    ThreadCount countUp(ThreadCount::COUNT_UP, mutex, resource);
    ThreadCount countDw(ThreadCount::COUNT_DW, mutex, resource);
    countUp.execute();
    countDw.execute();
    bool_t isCompleted( false );
    for(uint32_t i=0; i<TESTS_WAIT_CYCLE_TIME; i++)
    {
        isCompleted = countUp.isCompleted();
        isCompleted &= countDw.isCompleted();
        if( isCompleted )
        {
            break;
        }
    }
    EXPECT_TRUE(isCompleted) << "Fatal: Counting threads didn't complite their jobs";
    EXPECT_EQ(resource, resVal) << "Fatal: Mutex was not locked on atomic resource access";
    EXPECT_TRUE(countUp.join()) << "Error: Thread was not joined";
    EXPECT_TRUE(countDw.join()) << "Error: Thread was not joined";
}

} // namespace lib
} // namespace eoos
