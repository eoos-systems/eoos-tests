/**
 * @file      lib.ThreadTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021-2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Thread`. 
 */
#include "System.hpp"
#include "lib.Thread.hpp"

#ifdef EOOS_NO_STRICT_MISRA_RULES

namespace eoos
{
namespace lib
{

/**
 * @class ThreadTest
 * @test Thread
 * @brief Tests Thread class functionality.
 */
class ThreadTest : public ::testing::Test
{

protected:

    /**
     * @class Task
     * @brief Thread task for the test.
     */
    class Task : public ::eoos::Object<>, public api::Task
    {
        using Parent = ::eoos::Object<>;
      
    public:

        /**
         * @enum Error
         * @brief The task possible errors.
         */    
        enum Error
        {
            ERROR_OK,
            ERROR_UNDEF,
            ERROR_TIMEOUT,
            ERROR_NORESPONSE
        };
    
        /**
         * @enum Story
         * @brief Task story to play
         */
        enum class Story : int32_t
        {
            Default,
            Counter,            
            Reactor,
            Initiator            
        };
    
        /**
         * @brief Constructor.
         */
        Task() : Parent()
        {
        }
        
        /**
         * @brief Constructor.
         *
         * @param isConstructed Flag the object will be constructed.
         */
        Task(bool_t isConstructed) : Parent()
        {
            setConstructed(isConstructed);
        }
        
        /**
         * @brief Constructor.
         *
         * @param isConstructed Flag the object will be constructed.
         */
        Task(Story story) : Parent(),
            story_ (story){
        }
        
        /**
         * @brief Waits the task is called in separated thread.
         *
         * @return True if task was started by the OS scheduler.
         */
        bool waitIsStarted() const
        {
            bool_t isStarted {false};
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
        uint32_t getCounter()
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
        
    private:    
        
        /**
         * @copydoc eoos::api::Object::isConstructed()
         */        
        bool_t isConstructed() const override
        {
            return Parent::isConstructed();
        }    
    
        /**
         * @copydoc eoos::api::Task::start()
         */        
        void start() override
        {
            isStarted_ = true;            
            switch (story_)
            {
                case Story::Default:   playDefault();   break;
                case Story::Counter:   playCounter();   break;
                case Story::Reactor:   playReactor();   break;
                case Story::Initiator: playInitiator(); break;                
            }
            isDead_ = true;            
        }

        /**
         * @copydoc eoos::api::Task::getStackSize()
         */
        size_t getStackSize() const override
        {
            return 0;
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
                if( not toCount_ )
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
            int32_t count {TESTS_WAIT_CYCLE_TIME};
            while(true)
            {   
                if(channelItoR_ == MSG_PING)
                {
                    channelRtoI_ = MSG_PONG;
                    break;
                }
                if(--count == 0)
                {
                    error_ = ERROR_TIMEOUT;
                    return;
                }
            }
            // The initiator has initiated, the reactor has the reacted
            // Complete with own success
            error_ = ERROR_OK;
        }

        /**
         * @brief Plays initiator story.
         */
        void playInitiator()
        {
            // Wait the reactor is ready
            int32_t count {TESTS_WAIT_CYCLE_TIME};
            while(true)
            {   
                if(channelRtoI_ == MSG_READY)
                {
                    break;
                }
                if(--count == 0)
                {
                    error_ = ERROR_TIMEOUT;
                    return;
                }
            }
            // Initiate the reactor
            channelItoR_ = MSG_PING;
            // Ask scheduler to yield current time slice to other thread, 
            // relying the reactor will be called
            Thread<>::yield();
            // Check the reactor reacted 
            error_ = (channelRtoI_ == MSG_PONG) ? ERROR_OK : ERROR_NORESPONSE;
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
        
        static int32_t channelItoR_;   ///< Channel Initiator to Reactor direction.
        static int32_t channelRtoI_;   ///< Channel Reactor to Initiator direction.
        
        uint32_t count_ {0};           ///< Counter.
        bool_t toCount_ {true};        ///< Has to count flag.
        bool_t isStarted_ {false};     ///< Task started flag.
        bool_t isDead_ {false};        ///< Task dead flag.
        Story story_ {Story::Default}; ///< Task story to play.
        int32_t error_ {ERROR_UNDEF};  ///< Execution error.
        bool_t toWait_ {true};         ///< Task wait and executed.
    };
    
protected:    

    /**
     * @struct Tasks
     * @brief Task collection under test.
     */
    struct Tasks
    {
        Task normal;
        Task unconstructed {false};
        Task counter[2] = {Task::Story::Counter, Task::Story::Counter};
        Task in {Task::Story::Initiator};
        Task re {Task::Story::Reactor};        
    } task;

    // @note Re-define the api::Thread constants here as GTest on GCC doesn't like static variables 
    // and constants defined in scope of fixture classes as well as in scope of tested classes.    
    int32_t const PRIORITY_WRONG {api::Thread::PRIORITY_WRONG};
    int32_t const PRIORITY_MAX {api::Thread::PRIORITY_MAX};
    int32_t const PRIORITY_MIN {api::Thread::PRIORITY_MIN};
    int32_t const PRIORITY_NORM {api::Thread::PRIORITY_NORM};
    int32_t const PRIORITY_LOCK  {api::Thread::PRIORITY_LOCK};
    
private:

    System eoos_; ///< EOOS Operating System.
};  

int32_t ThreadTest::Task::channelItoR_ {ThreadTest::Task::MSG_IDLE};
int32_t ThreadTest::Task::channelRtoI_ {ThreadTest::Task::MSG_IDLE};

/**
 * @relates ThreadTest
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
TEST_F(ThreadTest, Constructor)
{
    Thread<> obj(task.normal);
    EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
}

/**
 * @relates ThreadTest
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
TEST_F(ThreadTest, isConstructed)
{
    // Test constructed
    {
        Thread<> obj(task.normal);
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
    }
    // Test unconstructed
    {
        Thread<> thread(task.unconstructed);
        EXPECT_FALSE(thread.isConstructed()) << "Error: Object is constructed";
    }
}

/**
 * @relates ThreadTest
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
TEST_F(ThreadTest, execute)
{
    // Execute constructed task
    {
        Thread<> thread(task.normal);
        EXPECT_TRUE(thread.isConstructed()) << "Error: Object is not constructed";
        EXPECT_FALSE(task.normal.waitIsStarted()) << "Error: Thread was started without execute() function";
        EXPECT_TRUE(thread.execute()) << "Error: Thread was not executed";
        EXPECT_TRUE(task.normal.waitIsStarted()) << "Fatal: Thread was not executed";
        EXPECT_TRUE(thread.join()) << "Error: Thread was not joined";
    }
    // Execute not constructed task
    {
        Thread<> thread(task.unconstructed);
        EXPECT_FALSE(thread.isConstructed()) << "Error: Object is constructed";
        EXPECT_FALSE(thread.execute()) << "Error: Thread was executed";
        EXPECT_FALSE(task.unconstructed.waitIsStarted()) << "Fatal: Unconstructed thread was executed";
        EXPECT_FALSE(thread.join()) << "Error: Thread was joined";
    }
}

/**
 * @relates ThreadTest
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
TEST_F(ThreadTest, join)
{
    {
        Thread<> thread(task.normal);
        EXPECT_TRUE(thread.isConstructed()) << "Error: Object is not constructed";
        EXPECT_TRUE(thread.execute()) << "Error: Thread was not executed";
        EXPECT_TRUE(thread.join()) << "Error: Thread was not joined";
        EXPECT_TRUE(task.normal.isDead()) << "Fatal: Thread is not dead";
    }
    {
        Thread<> thread(task.unconstructed);
        EXPECT_FALSE(thread.isConstructed()) << "Error: Object is constructed";
        EXPECT_FALSE(thread.execute()) << "Error: Thread was executed";
        EXPECT_FALSE(thread.join()) << "Error: Thread was joined";
        EXPECT_FALSE(task.unconstructed.isDead()) << "Fatal: Thread is dead";        
    }
}

/**
 * @relates ThreadTest
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
TEST_F(ThreadTest, getPriority)
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
 * @relates ThreadTest
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
TEST_F(ThreadTest, setPriority)
{
    {
        Thread<> thread(task.normal);
        EXPECT_TRUE(thread.setPriority(PRIORITY_LOCK)) << "Error: Thread priority is not set";
        EXPECT_EQ(thread.getPriority(), PRIORITY_LOCK) << "Fatal: Thread priority is wrong";
    }
    {
        Thread<> thread(task.unconstructed);
        EXPECT_FALSE(thread.setPriority(PRIORITY_LOCK)) << "Error`: Thread priority is set"; 
        EXPECT_EQ(thread.getPriority(), PRIORITY_WRONG) << "Fatal: Thread priority is not wrong";        
    }
    for(int32_t priority=PRIORITY_MIN; priority<=PRIORITY_MAX; priority++)
    {
        Thread<> thread(task.normal);
        EXPECT_TRUE(thread.setPriority(priority)) << "Error: Thread priority is not set";
        EXPECT_EQ(thread.getPriority(), priority) << "Fatal: Thread priority is wrong";
    }
    {
        Thread<> thread(task.normal);
        EXPECT_FALSE(thread.setPriority(PRIORITY_MAX + 1)) << "Error: Thread priority is set";
        EXPECT_EQ(thread.getPriority(), PRIORITY_NORM) << "Fatal: Thread priority is wrong";
    }  
    {
        Thread<> thread(task.normal);
        EXPECT_FALSE(thread.setPriority(PRIORITY_MIN - 2)) << "Error: Thread priority is set";
        EXPECT_EQ(thread.getPriority(), PRIORITY_NORM) << "Fatal: Thread priority is wrong";
    }      
}

/**
 * @relates ThreadTest
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
TEST_F(ThreadTest, yield_reactionOnInitiation)
{
    Thread<> re(task.re);
    Thread<> in(task.in);

    EXPECT_TRUE(re.execute()) << "Error: Reactor thread was not executed";    
    EXPECT_TRUE(in.execute()) << "Error: Initiator thread was not executed";

    EXPECT_TRUE(re.join()) << "Error: Reactor thread was not joined";
    EXPECT_TRUE(in.join()) << "Error: Initiator thread was not joined";

    EXPECT_NE(task.in.getError(), Task::ERROR_UNDEF) << "Error: Initiator was not started";    
    EXPECT_NE(task.in.getError(), Task::ERROR_TIMEOUT) << "Error: Initiator didn't get confirmation Reactor started";
    EXPECT_NE(task.in.getError(), Task::ERROR_NORESPONSE) << "Error: Initiator didn't get reactor response";
    EXPECT_EQ(task.in.getError(), Task::ERROR_OK) << "Error: Initiator unexpected error";
    
    EXPECT_NE(task.re.getError(), Task::ERROR_UNDEF) << "Error: Reactor was not started";    
    EXPECT_NE(task.re.getError(), Task::ERROR_TIMEOUT) << "Error: Reactor didn't get initiator request";
    EXPECT_EQ(task.re.getError(), Task::ERROR_OK) << "Error: Reactor unexpected error";
}

/**
 * @relates ThreadTest
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
TEST_F(ThreadTest, sleep)
{
    int64_t ms[2] = {300, 1200};
    uint32_t counter[2] = {100, 100};
    for(int32_t i=0; i<2; i++)
    {
        Thread<> count(task.counter[i]);
        EXPECT_TRUE(count.execute()) << "Error: Thread was not executed";
        EXPECT_TRUE(Thread<>::sleep(ms[i])) << "Error: Thread sleep got a system error";
        task.counter[i].stopCounter();
        EXPECT_TRUE(count.join()) << "Error: Thread was not joined";
        counter[i] += task.counter[i].getCounter();
    }
    EXPECT_LT(counter[0] + counter[0], counter[1]) << "Error: Thread was not joined";
}

} // namespace lib
} // namespace eoos

#endif // EOOS_NO_STRICT_MISRA_RULES
