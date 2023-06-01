/**
 * @file      DebugTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021-2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Thread`. 
 */
#include "lib.Thread.hpp"
#include "lib.String.hpp"
#include "lib.Stream.hpp"
#include "System.hpp"

namespace eoos
{

/**
 * @class glb_DebugTest
 * @brief Tests whatever for debug purposes.
 */
class glb_DebugTest : public ::testing::Test
{

protected:

    class Task : public lib::Object<>, public api::Task
    {
        typedef lib::Object<> Parent;
      
    public:

        bool_t isDone;
        uint64_t count;
    
        Task() : Parent(),
            isDone(false),
            count(0){
        }
        
    private:    
        
        virtual bool_t isConstructed() const
        {
            return Parent::isConstructed();
        }    
    
        virtual void start()
        {
            while(!isDone)
            {
                count++;
            }
        }
        
        virtual size_t getStackSize() const
        {
            return 0;
        }
    
    };
 
    Task task;
 
private:

    System eoos_;
};  
    
/**
 * @brief Waits for some cycles.
 *
 * @return true if wait is needed.
 */
static bool_t wait()
{
    const uint64_t COUNT(0xFFFF);
    static uint64_t count(COUNT);
    count--;
    bool_t res(true);
    if( count == 0 )
    {
        res = false;
        count = COUNT;
    }
    return res;
}

/**
 * @relates glb_DebugTest
 * @brief Tests thread stays in detached.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an Thread object.
 *      - Delete the Thread object.
 *
 * @b Assert:
 *      - Test the thread was not scheduled after its object had been deleted.
 */
TEST_F(glb_DebugTest, DISABLED_threadIsDetached)
{
    uint64_t count[] = {0,0};
    lib::Thread<>* thread( new lib::Thread<>(task) );
    thread->execute();
    lib::Stream::cout() << "Thread object is alive...\n";
    while(true)
    {
        if(!wait())
        {
            break;
        }
        if(task.count > count[0])
        {
            lib::Stream::cout() << ".";
        }
        count[0] = task.count;
    }
    delete thread;
    count[1] = count[0] = task.count;
    lib::String str;
    str.convert(count[0]);
    lib::Stream::cout() << "\n" << "Thread object is dead on count = " << str.getChar() << "\n";
    while( wait() )
    {
        lib::Stream::cout() << "~";
    }
    lib::Stream::cout() << "\n" << "Waiting thread could be alive completed.\n";
    while(true)
    {
        if(!wait())
        {
            break;
        }
        if(task.count > count[1])
        {
            lib::Stream::cout() << ".";
        }
        count[1] = task.count;
    }
    str.convert(count[0]);
    lib::Stream::cout() << "\n" << "Test is finished on count = " << str.getChar() << "\n";
    if(count[0] == count[1])
    {
        lib::Stream::cout() << "Thread was not scheduled after its object had been deleted - it's good case\n";
    }
    else
    {
        lib::Stream::cout() << "Thread was detached and continued executing after its object had been deleted - it's bad case\n";
    }
    task.isDone = true;
    ASSERT_EQ(count[1], count[0]) << "Fatal: Thread stayed in detach mode";
}

} // namespace eoos
