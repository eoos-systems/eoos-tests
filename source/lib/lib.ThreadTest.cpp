/**
 * @file      lib.ThreadTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021-2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Thread`. 
 */
#include "lib.Thread.hpp"
#include "lib.AbstractTask.hpp"
#include "System.hpp"

#ifndef EOOS_GLOBAL_ENABLE_NO_HEAP

namespace eoos
{
namespace lib
{

/**
 * @class lib_ThreadTest
 * @test Thread
 * @brief Tests Thread class functionality.
 */
class lib_ThreadTest : public ::testing::Test
{

protected:

    /**
     * @class Task
     * @brief Semaphore task for the test.
     */
    class Task : public AbstractTask<>
    {
        typedef AbstractTask<> Parent;
      
    public:

        /**
         * @enum Error
         * @brief The task possible errors.
         */    
        enum Error
        {
            ERROR_TEST_OK,
            ERROR_TEST_UNDEF,
            ERROR_TEST_TIMEOUT,
            ERROR_TEST_NORESPONSE
        };
    
        /**
         * @enum Story
         * @brief Task story to play
         */
        enum Story
        {
            STORY_DEFAULT,
            STORY_COUNTER,            
            STORY_REACTOR,
            STORY_INITIATOR            
        };
    
        /**
         * @brief Constructor.
         */
        Task() 
            : Parent()
            , count_ (0U)
            , toCount_ (true)
            , isStarted_ (false)
            , isDead_ (false)
            , story_ (STORY_DEFAULT)
            , error_ (ERROR_TEST_UNDEF)
            , toWait_ (true)
            , stackSize_(0U) {
        }

        /**
         * @brief Constructor.
         *
         * @param stackSize This task stack size.         
         */
        Task(size_t stackSize) 
            : Parent()
            , count_ (0U)
            , toCount_ (true)
            , isStarted_ (false)
            , isDead_ (false)
            , story_ (STORY_DEFAULT)
            , error_ (ERROR_TEST_UNDEF)
            , toWait_ (true)
            , stackSize_(stackSize) {
        }

        /**
         * @brief Constructor.
         *
         * @param isConstructed Flag the object will be constructed.
         */
        Task(bool_t isConstructed) 
            : Parent()
            , count_ (0U)
            , toCount_ (true)
            , isStarted_ (false)
            , isDead_ (false)
            , story_ (STORY_DEFAULT)
            , error_ (ERROR_TEST_UNDEF)
            , toWait_ (true)
            , stackSize_(0U) {
            setConstructed(isConstructed);
        }
        
        /**
         * @brief Constructor.
         *
         * @param isConstructed Flag the object will be constructed.
         */
        Task(Story story) 
            : Parent()
            , count_ (0U)
            , toCount_ (true)
            , isStarted_ (false)
            , isDead_ (false)
            , story_ (story)
            , error_ (ERROR_TEST_UNDEF)
            , toWait_ (true)
            , stackSize_(0U) {            
        }
        
        /**
         * @brief Waits the task is called in separated thread.
         *
         * @return True if task was started by the OS scheduler.
         */
        bool waitIsStarted() const
        {
            bool_t isStarted(false);
            for(uint32_t i=0; i<TESTS_WAIT_CYCLE_TIME; i++)
            {
                isStarted = isStarted_;
                if(isStarted)
                {
                    break;
                }
            }
            return isStarted;
        }

        /**
         * @brief Stops counter.
         */        
        void stopCounter()
        {
            toCount_ = false;
        }

        /**
         * @brief Stops counter.
         */        
        uint64_t getCounter()
        {
            return count_;
        }

        /**
         * @brief Tests if the task is completed execution.
         *
         * @return True if task is is completed execution.
         */        
        bool isDead() const
        {
            return isDead_;
        }
        
        /**
         * @brief Returns execution error.
         *
         * @return an error code.
         */        
        int32_t getError() const
        {
            return error_;
        }
        
        /**
         * @copydoc eoos::api::Task::getStackSize()
         */
        virtual size_t getStackSize() const
        {
            size_t stackSize( stackSize_ );
            if(stackSize == 0) 
            {
                stackSize = AbstractTask<>::getStackSize();
            }
            return stackSize;
        }  
        
    private:    
            
        /**
         * @copydoc eoos::api::Task::start()
         */        
        virtual void start()
        {
            isStarted_ = true;            
            switch (story_)
            {
                case STORY_DEFAULT:
                {
                    playDefault();
                    break;
                }
                case STORY_COUNTER:
                {
                    playCounter();
                    break;
                }
                case STORY_REACTOR:
                {
                    playReactor();
                    break;
                }
                case STORY_INITIATOR:
                {
                    playInitiator();
                    break;
                }
            }
            isDead_ = true;            
        }

        /**
         * @brief Plays default story.
         */        
        void playDefault()
        {
            Thread<>::yield();
        }

        /**
         * @brief Plays counter story.
         */        
        void playCounter()
        {
            while(true)
            {
                if( !toCount_ )
                {
                    break;
                }
                count_++;
            }
        }
        
        /**
         * @brief Plays reactor story.
         */                
        void playReactor()
        {
            // Inform the initiator the reactor is ready to react
            channelRtoI_ = MSG_READY;
            // Wait the initiator initiated
            int32_t count(TESTS_WAIT_CYCLE_TIME);
            while(true)
            {   
                if(channelItoR_ == MSG_PING)
                {
                    channelRtoI_ = MSG_PONG;
                    break;
                }
                if(--count == 0)
                {
                    error_ = ERROR_TEST_TIMEOUT;
                    return;
                }
            }
            // The initiator has initiated, the reactor has the reacted
            // Complete with own success
            error_ = ERROR_TEST_OK;
        }

        /**
         * @brief Plays initiator story.
         */
        void playInitiator()
        {
            // Wait the reactor is ready
            int32_t count(TESTS_WAIT_CYCLE_TIME);
            while(true)
            {   
                if(channelRtoI_ == MSG_READY)
                {
                    break;
                }
                if(--count == 0)
                {
                    error_ = ERROR_TEST_TIMEOUT;
                    return;
                }
            }
            // Initiate the reactor
            channelItoR_ = MSG_PING;
            // Ask scheduler to yield current time slice to other thread, 
            // relying the reactor will be called
            Thread<>::yield();
            // Check the reactor reacted 
            error_ = (channelRtoI_ == MSG_PONG) ? ERROR_TEST_OK : ERROR_TEST_NORESPONSE;
        }

        /**
         * @enum Msg
         * @brief Initiator-reactor messages.
         */        
        enum Msg
        {
            MSG_IDLE,
            MSG_READY,
            MSG_PING,
            MSG_PONG
        };
        
        static int32_t volatile channelItoR_;   ///< Channel Initiator to Reactor direction.
        static int32_t volatile channelRtoI_;   ///< Channel Reactor to Initiator direction.
        
        uint64_t count_;            ///< Counter.
        bool_t volatile toCount_;   ///< Has to count flag.
        bool_t volatile isStarted_; ///< Task started flag.
        bool_t isDead_;             ///< Task dead flag.
        Story story_;               ///< Task story to play.
        int32_t error_;             ///< Execution error.
        bool_t toWait_;             ///< Task wait and executed.
        size_t stackSize_;          ///< Task stack size.
    };

    /**
     * @struct Tasks
     * @brief Task collection under test.
     */
    struct Tasks
    {
        Tasks() 
            : normal()
            , stack( static_cast<size_t>(16384UL) )
            , unconstructed( false )
            , in( Task::STORY_INITIATOR )
            , re( Task::STORY_REACTOR )
            , counter0( Task::STORY_COUNTER )
            , counter1( Task::STORY_COUNTER ){
            counters[0] = &counter0;
            counters[1] = &counter1;
        }
        
        Task normal;
        Task stack;        
        Task unconstructed;
        Task in;
        Task re;
        // @note G++ compiler creates templorary objects and move them
        // by calling move constructors of objects in Task[2] array.
        // Move semantic of the Task class is prohibited by  inhiring 
        // of NonCopyable<A> class. Therefore, will use Task*[2] here:
        Task counter0;
        Task counter1;
        Task* counters[2];
    } task;
    
private:

    System eoos_; ///< EOOS Operating System.
};  

int32_t volatile lib_ThreadTest::Task::channelItoR_(lib_ThreadTest::Task::MSG_IDLE);
int32_t volatile lib_ThreadTest::Task::channelRtoI_(lib_ThreadTest::Task::MSG_IDLE);

// @note Re-define the api::Thread constants here as GTest on GCC doesn't like static variables 
// and constants defined in scope of fixture classes as well as in scope of tested classes.    
static const int32_t PRIORITY_WRONG(api::Thread::PRIORITY_WRONG);
static const int32_t PRIORITY_MAX(api::Thread::PRIORITY_MAX);
static const int32_t PRIORITY_MIN(api::Thread::PRIORITY_MIN);
static const int32_t PRIORITY_NORM(api::Thread::PRIORITY_NORM);
static const int32_t PRIORITY_LOCK(api::Thread::PRIORITY_LOCK);


/**
 * @relates lib_ThreadTest
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
TEST_F(lib_ThreadTest, Constructor)
{
    Thread<> obj(task.normal);
    EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
}

/**
 * @relates lib_ThreadTest
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
 *      - Test the object is not constructed. 
 */
TEST_F(lib_ThreadTest, isConstructed)
{
    // Test constructed
    {
        Thread<> obj(task.normal);
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
    }
    // Test unconstructed
    {
        Thread<> thread(task.unconstructed);
        EXPECT_FALSE(thread.isConstructed()) << "Fatal: Object is constructed";
    }
}

/**
 * @relates lib_ThreadTest
 * @brief Test if thread can be executed. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct a constructed and unconstructed objects of the class.
 *
 * @b Assert:
 *      - Test the constructed object is executed.
 *      - Test the unconstructed object is not executed.
 */
TEST_F(lib_ThreadTest, execute)
{
    // Execute constructed task
    {
        Thread<> thread(task.normal);
        EXPECT_TRUE(thread.isConstructed()) << "Error: Object is not constructed";
        EXPECT_FALSE(task.normal.waitIsStarted()) << "Error: Thread was started without execute() function";
        ASSERT_TRUE(thread.execute()) << "Fatal: Thread was not executed";
        EXPECT_TRUE(task.normal.waitIsStarted()) << "Error: Thread was not started after execute() function";
        EXPECT_TRUE(thread.join()) << "Error: Thread was not joined";
        ASSERT_FALSE(thread.execute()) << "Fatal: Thread was executed";        
    }
    // Execute constructed task with stack defined
    {
        Thread<> thread(task.stack);
        EXPECT_TRUE(thread.isConstructed()) << "Error: Object is not constructed";
        EXPECT_FALSE(task.stack.waitIsStarted()) << "Error: Thread was started without execute() function";
        ASSERT_TRUE(thread.execute()) << "Fatal: Thread was not executed";
        EXPECT_TRUE(task.stack.waitIsStarted()) << "Error: Thread was not started after execute() function";
        EXPECT_TRUE(thread.join()) << "Error: Thread was not joined";
    }    
    // Execute not constructed task
    {
        Thread<> thread(task.unconstructed);
        EXPECT_FALSE(thread.isConstructed()) << "Error: Object is constructed";
        ASSERT_FALSE(thread.execute()) << "Fatal: Thread was executed";
        EXPECT_FALSE(task.unconstructed.waitIsStarted()) << "Error: Unconstructed thread was executed";
        EXPECT_FALSE(thread.join()) << "Error: Thread was joined";
    }
}

/**
 * @relates lib_ThreadTest
 * @brief Test if thread is joined.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct a constructed and unconstructed objects of the class.
 *
 * @b Assert:
 *      - Test the constructed object is joined and dead after that.
 *      - Test the unconstructed object is not joined and not dead meaning it was not started.
 */
TEST_F(lib_ThreadTest, join)
{
    {
        Thread<> thread(task.normal);
        EXPECT_TRUE(thread.isConstructed()) << "Error: Object is not constructed";
        EXPECT_TRUE(thread.execute()) << "Error: Thread was not executed";
        EXPECT_TRUE(thread.join()) << "Fatal: Thread was not joined";
        EXPECT_TRUE(task.normal.isDead()) << "Error: Thread is not dead";
    }
    {
        Thread<> thread(task.unconstructed);
        EXPECT_FALSE(thread.isConstructed()) << "Error: Object is constructed";
        EXPECT_FALSE(thread.execute()) << "Error: Thread was executed";
        EXPECT_FALSE(thread.join()) << "Fatal: Thread was joined";
        EXPECT_FALSE(task.unconstructed.isDead()) << "Error: Thread is dead";        
    }
}

/**
 * @relates lib_ThreadTest
 * @brief Test if thread priority can be gotten right.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct a constructed and unconstructed objects of the class.
 *
 * @b Assert:
 *      - Test the constructed object has Normal priority.
 *      - Test the unconstructed object has Wrong priority.
 */
TEST_F(lib_ThreadTest, getPriority)
{
    {
        Thread<> thread(task.normal);
        EXPECT_EQ(thread.getPriority(), PRIORITY_NORM) << "Fatal: Thread priority is not Normal";
    }
    {
        Thread<> thread(task.unconstructed);
        EXPECT_EQ(thread.getPriority(), PRIORITY_WRONG) << "Fatal: Thread priority is not Wrong";
    }    
}

/**
 * @relates lib_ThreadTest
 * @brief Test if thread priority can be set.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Set all priorities in valid range.
 *      - Set all priorities out of valid range. 
 *
 * @b Assert:
 *      - Test priorities in valid range are set.
 *      - Test priorities out of valid range are not set.
 */
TEST_F(lib_ThreadTest, setPriority)
{
    {
        Thread<> thread(task.normal);
        EXPECT_TRUE(thread.setPriority(PRIORITY_LOCK)) << "Fatal: Thread priority is not set";
        EXPECT_EQ(thread.getPriority(), PRIORITY_LOCK) << "Error: Thread priority is wrong";
    }
    {
        Thread<> thread(task.unconstructed);
        EXPECT_FALSE(thread.setPriority(PRIORITY_LOCK)) << "Fatal: Thread priority is set"; 
        EXPECT_EQ(thread.getPriority(), PRIORITY_WRONG) << "Error: Thread priority is not wrong";        
    }
    for(int32_t priority=PRIORITY_MIN; priority<=PRIORITY_MAX; priority++)
    {
        Thread<> thread(task.normal);
        EXPECT_TRUE(thread.setPriority(priority)) << "Fatal: Thread priority is not set";
        EXPECT_EQ(thread.getPriority(), priority) << "Error: Thread priority is wrong";
    }
    {
        Thread<> thread(task.normal);
        EXPECT_FALSE(thread.setPriority(PRIORITY_MAX + 1)) << "Fatal: Thread priority is set";
        EXPECT_EQ(thread.getPriority(), PRIORITY_NORM) << "Error: Thread priority is wrong";
    }  
    {
        Thread<> thread(task.normal);
        EXPECT_FALSE(thread.setPriority(PRIORITY_MIN - 2)) << "Fatal: Thread priority is set";
        EXPECT_EQ(thread.getPriority(), PRIORITY_NORM) << "Error: Thread priority is wrong";
    }      
}

/**
 * @relates lib_ThreadTest
 * @brief Test if thread yields its time slice.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Create and start Initiator and Reactor threads.
 *      - Initiator waits Reactor is started.
 *      - Reactor waits a 'ping' message form Initiator.
 *      - Initiator sends the 'ping' message to Reactor.
 *      - Initiator yields its time slice relying OS scheduler will switch to Reactor then.
 *      - Reactor gets its time slice and gets the 'ping' message.
 *      - Reactor sends a 'pong' message and exits.
 *      - Initiator gets control back after the yielding and check the 'pong' message.
 *      - Initiator exits.
 *
 * @b Assert:
 *      - Test no errors during the ping-pong communication.
 */
TEST_F(lib_ThreadTest, yield_reactionOnInitiation)
{
    Thread<> re(task.re);
    Thread<> in(task.in);

    EXPECT_TRUE(re.execute()) << "Error: Reactor thread was not executed";    
    EXPECT_TRUE(in.execute()) << "Error: Initiator thread was not executed";

    EXPECT_TRUE(re.join()) << "Error: Reactor thread was not joined";
    EXPECT_TRUE(in.join()) << "Error: Initiator thread was not joined";

    EXPECT_NE(task.in.getError(), Task::ERROR_TEST_UNDEF) << "Fatal: Initiator was not started";    
    EXPECT_NE(task.in.getError(), Task::ERROR_TEST_TIMEOUT) << "Fatal: Initiator didn't get confirmation Reactor started";
    EXPECT_NE(task.in.getError(), Task::ERROR_TEST_NORESPONSE) << "Fatal: Initiator didn't get reactor response";
    EXPECT_EQ(task.in.getError(), Task::ERROR_TEST_OK) << "Fatal: Initiator unexpected error";
    
    EXPECT_NE(task.re.getError(), Task::ERROR_TEST_UNDEF) << "Fatal: Reactor was not started";    
    EXPECT_NE(task.re.getError(), Task::ERROR_TEST_TIMEOUT) << "Fatal: Reactor didn't get initiator request";
    EXPECT_EQ(task.re.getError(), Task::ERROR_TEST_OK) << "Fatal: Reactor unexpected error";
}

/**
 * @relates lib_ThreadTest
 * @brief Test if thread sleeps.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Initialize begin values of counters to non-zero (100) value to be sure if sleep was not performed,
 *        two values of counter 1 would be great than a value of counter 2.
 *      - Run a task counter 1.
 *      - Sleep for N milliseconds.
 *      - Run a task counter 2.
 *      - Sleep for N*4 milliseconds.
 *
 * @b Assert:
 *      - Test two values of counter 1 less than a value of counter 2.
 */
TEST_F(lib_ThreadTest, sleep)
{
    int32_t ms[2] = {300, 1200};
    uint64_t counters[2] = {100, 100};
    for(int32_t i=0; i<2; i++)
    {
        Thread<> count(*task.counters[i]);
        EXPECT_TRUE(count.execute()) << "Error: Thread was not executed";
        EXPECT_TRUE(Thread<>::sleep(ms[i])) << "Error: Thread sleep got a system error";
        task.counters[i]->stopCounter();
        EXPECT_TRUE(count.join()) << "Error: Thread was not joined";
        counters[i] += task.counters[i]->getCounter();
    }
    uint64_t val1( counters[0] + counters[0] );
    uint64_t val2( counters[1] );
    EXPECT_LT(val1, val2) << "Fatal: Thread was not joined";
}

/**
 * @relates lib_ThreadTest
 * @brief Test if thread sleeps.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Initialize begin values of counters to non-zero (100) value to be sure if sleep was not performed,
 *        two values of counter 1 would be great than a value of counter 2.
 *      - Run a task counter 1.
 *      - Sleep for N milliseconds.
 *      - Run a task counter 2.
 *      - Sleep for N*4 milliseconds.
 *
 * @b Assert:
 *      - Test two values of counter 1 less than a value of counter 2.
 */
TEST_F(lib_ThreadTest, sleep_wrongArgs)
{
    EXPECT_FALSE(Thread<>::sleep(-1)) << "Fatal: Thread sleep with negate time argument";
}

} // namespace lib
} // namespace eoos

#endif // EOOS_GLOBAL_ENABLE_NO_HEAP
