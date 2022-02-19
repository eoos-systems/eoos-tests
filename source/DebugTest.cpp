/**
 * @file      DebugTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Thread`. 
 */
#include "System.hpp"
#include "lib.Thread.hpp"

namespace eoos
{

class DebugTest : public ::testing::Test
{

protected:

    class Task : public ::eoos::Object<>, public api::Task
    {
        using Parent = ::eoos::Object<>;
      
    public:

        bool_t isDone {false};
        uint64_t count {0};
        
    private:    
        
        bool_t isConstructed() const override
        {
            return Parent::isConstructed();
        }    
    
        int32_t start() override
        {
            while(not isDone)
            {
                count++;
            }
            return 0;
        }
        
        size_t getStackSize() const override
        {
            return 0;
        }
    
    };
 
    Task task;
 
private:

    System eoos_;
};  
    
static bool_t wait()
{
    const uint64_t COUNT {0xFFFF};
    static uint64_t count {COUNT};
    count--;
    bool_t res {true};
    if( count == 0 )
    {
        res = false;
        count = COUNT;
    }
    return res;
}

TEST_F(DebugTest, threadIsDetached)
{
    uint64_t count[] = {0,0};
    lib::Thread<>* thread = new lib::Thread<>(task);
    thread->execute();
    std::cout << "Thread object is alive..." << std::endl;
    while(true)
    {
        if(not wait())
        {
            break;
        }
        if(task.count > count[0])
        {
            std::cout << ".";
        }
        count[0] = task.count;
    }
    delete thread;
    count[1] = count[0] = task.count;
    std::cout << std::endl << "Thread object is dead on count = " << count[0] << std::endl;
    while( wait() )
    {
        std::cout << "~";
    }
    std::cout << std::endl << "Waiting thread could be alive completed." << count[0] << std::endl;
    while(true)
    {
        if(not wait())
        {
            break;
        }
        if(task.count > count[1])
        {
            std::cout << ".";
        }
        count[1] = task.count;
    }
    std::cout << std::endl << "Test is finished on count = " << count[1] << std::endl;
    if(count[0] == count[1])
    {
        std::cout << "Thread was not scheduled after its object had been deleted - it's good case" << std::endl;
    }
    else
    {
        std::cout << "Thread was detached and continued executing after its object had been deleted - it's bad case" << std::endl;
    }
    task.isDone = true;
    ASSERT_EQ(count[1], count[0]) << "Fatal: Thread stayed in detach mode";
}

} // namespace eoos
