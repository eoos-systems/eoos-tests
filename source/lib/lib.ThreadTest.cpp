/**
 * @file      lib.ThreadTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021, Sergey Baigudin, Baigudin Software
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

class ThreadTest : public ::testing::Test
{

protected:

    class Task : public ::eoos::Object<>, public api::Task
    {
        using Parent = ::eoos::Object<>;
      
    public:
    
        Task() : Parent()
        {
        }
        
        Task(bool_t isConstructed) : Parent()
        {
            setConstructed(isConstructed);
        }
        
        bool waitIsStarted()
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
        
        bool isDead()
        {
            return isDead_;
        }
        
    private:    
        
        bool_t isConstructed() const override
        {
            return Parent::isConstructed();
        }    
    
        void start() override
        {
            isStarted_ = true;
            Thread<>::yield();
            isDead_ = true;
        }
        
        size_t getStackSize() const override
        {
            return 0;
        }
    
        bool_t isStarted_ {false};
        bool_t isDead_ {false};
    };
    
protected:    

    static int32_t TASK_RETURN_ERROR;

    struct Tasks
    {
        Task normal;
        Task unconstructed {false};
    } task;

    // @note Re-define the api::Thread constants here as GTest on GCC doesn't like static variables 
    // and constants defined in scope of fixture classes as well as in scope of tested classes.
    int32_t const ID_WRONG {api::Thread::ID_WRONG};
    
    int32_t const PRIORITY_WRONG {api::Thread::PRIORITY_WRONG};
    int32_t const PRIORITY_MAX {api::Thread::PRIORITY_MAX};
    int32_t const PRIORITY_MIN {api::Thread::PRIORITY_MIN};
    int32_t const PRIORITY_NORM {api::Thread::PRIORITY_NORM};
    int32_t const PRIORITY_LOCK  {api::Thread::PRIORITY_LOCK};
    
private:

    System eoos_; ///< EOOS Operating System.
};  
    
int32_t ThreadTest::TASK_RETURN_ERROR {333};

TEST_F(ThreadTest, Constructor)
{
    Thread<> obj(task.normal);
    EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
}

TEST_F(ThreadTest, isConstructed)
{
    Thread<> obj(task.normal);
    EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
    EXPECT_FALSE(task.normal.waitIsStarted()) << "Fatal: Constructed thread was executed";
}

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

TEST_F(ThreadTest, join)
{
    Thread<> thread(task.normal);
    EXPECT_TRUE(thread.isConstructed()) << "Error: Object is not constructed";
    EXPECT_TRUE(thread.execute()) << "Error: Thread was not executed";
    EXPECT_TRUE(thread.join()) << "Error: Thread was not joined";
    EXPECT_TRUE(task.normal.isDead()) << "Fatal: Thread is not dead";
}

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

TEST_F(ThreadTest, sleep)
{   
}

TEST_F(ThreadTest, yield)
{   
}

} // namespace lib
} // namespace eoos

#endif // EOOS_NO_STRICT_MISRA_RULES
