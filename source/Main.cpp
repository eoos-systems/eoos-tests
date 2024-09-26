/**
 * @file      MainTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020-2024, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit of `main`. 
 */
#include "System.hpp"
#include "lib.Stream.hpp"
#include "lib.String.hpp"
/// Test linkage errors by the includes below
#include "lib.Align.hpp"
#include "lib.ArgumentParser.hpp"
#include "lib.String.hpp"
#include "lib.BaseString.hpp"
#include "lib.Buffer.hpp"
#include "lib.CharTrait.hpp"
#include "lib.CircularList.hpp"
#include "lib.Fifo.hpp"
#include "lib.Guard.hpp"
#include "lib.Heap.hpp"
#include "lib.LinkedList.hpp"
#include "lib.Memory.hpp"
#include "lib.Mutex.hpp"
#include "lib.NoAllocator.hpp"
#include "lib.NonCopyable.hpp"
#include "lib.ObjectAllocator.hpp"
#include "lib.Object.hpp"
#include "lib.Register.hpp"
#include "lib.ResourceMemory.hpp"
#include "lib.Semaphore.hpp"
#include "lib.SharedPointer.hpp"
#include "lib.Stream.hpp"
#include "lib.Thread.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
    
/**
 * @brief Prints EOOS global configuration.
 */
static void printConfiguration()
{
    System eoos;
    lib::Stream::cout() << "[EOOS ] ~~~ eoos start ~~~~~~~~~~~~~~~~~\r\n";
    lib::Stream::cout() << "[EOOS ] WELCOME TO EOOS UNIT TESTS\r\n";
    // Output of C++ Language
    #if   EOOS_CPP_STANDARD == 1998
        lib::Stream::cout() << "[EOOS ] LANGUAGE: C++98\r\n";
    #elif EOOS_CPP_STANDARD == 2011
        lib::Stream::cout() << "[EOOS ] LANGUAGE: C++11\r\n";
    #elif EOOS_CPP_STANDARD == 2014
        lib::Stream::cout() << "[EOOS ] LANGUAGE: C++14\r\n";
    #elif EOOS_CPP_STANDARD == 2017
        lib::Stream::cout() << "[EOOS ] LANGUAGE: C++17\r\n";
    #elif EOOS_CPP_STANDARD == 2020
        lib::Stream::cout() << "[EOOS ] LANGUAGE: C++20\r\n";
    #else        
        lib::Stream::cout() << "[EOOS ] LANGUAGE: unknown\r\n";
    #endif
    
    // Output of Data Model of a hardware system
    #if defined (EOOS_TYPE_STDLIB)
        lib::Stream::cout() << "[EOOS ] DATA MODEL: C++ Standard Library types\r\n";
    #elif defined (EOOS_TYPE_WIDTH_LP32)
        lib::Stream::cout() << "[EOOS ] DATA MODEL: LP32 or 2/4/4 (int is 16-bit, long and pointer are 32-bit)\r\n";
    #elif defined (EOOS_TYPE_WIDTH_ILP32)
        lib::Stream::cout() << "[EOOS ] DATA MODEL: ILP32 or 4/4/4 (int, long, and pointer are 32-bit)\r\n";
    #elif defined (EOOS_TYPE_WIDTH_LLP64)
        lib::Stream::cout() << "[EOOS ] DATA MODEL: LLP64 or 4/4/8 (int and long are 32-bit, pointer is 64-bit)\r\n";
    #elif defined (EOOS_TYPE_WIDTH_LP64)
        lib::Stream::cout() << "[EOOS ] DATA MODEL: LP64 or 4/8/8 (int is 32-bit, long and pointer are 64-bit)\r\n";
    #else
        lib::Stream::cout() << "[EOOS ] DATA MODEL: C++ standard\r\n";
    #endif

    // Dynamic heap memory allocation
    #if defined (EOOS_GLOBAL_ENABLE_NO_HEAP)
        lib::Stream::cout() << "[EOOS ] DISABLE: Dynamic heap memory allocation\r\n";
    #else
        lib::Stream::cout() << "[EOOS ] ENABLE: Dynamic heap memory allocation\r\n";
    #endif

    #if EOOS_GLOBAL_SYS_NUMBER_OF_MUTEXS == 0
        lib::Stream::cout() << "[EOOS ] MEMORY MODE: Mutex in heap memory.\r\n";
    #else
        lib::Stream::cout() << "[EOOS ] MEMORY MODE: Mutex in pool memory of " << EOOS_GLOBAL_SYS_NUMBER_OF_MUTEXS << ".\r\n";
    #endif

    #if EOOS_GLOBAL_SYS_NUMBER_OF_SEMAPHORES == 0
        lib::Stream::cout() << "[EOOS ] MEMORY MODE: Semaphore in heap memory.\r\n";
    #else
        lib::Stream::cout() << "[EOOS ] MEMORY MODE: Semaphore in pool memory of " << EOOS_GLOBAL_SYS_NUMBER_OF_SEMAPHORES << ".\r\n";
    #endif

    #if EOOS_GLOBAL_SYS_NUMBER_OF_THREADS == 0
        lib::Stream::cout() << "[EOOS ] MEMORY MODE: Thread in heap memory.\r\n";
    #else
        lib::Stream::cout() << "[EOOS ] MEMORY MODE: Thread in pool memory of " << EOOS_GLOBAL_SYS_NUMBER_OF_THREADS << ".\r\n";
    #endif

    // EOOS state
    lib::Stream::cout() << "[EOOS ] PROPERTY: Size of EOOS system is " << static_cast<int32_t>(sizeof(sys::System)) << " Bytes\n";
}

/**
 * @brief Prints EOOS execution ending.
 */
static void printExecutionEnding()
{
    System eoos;
    lib::Stream::cout() << "[EOOS ] EOOS EXECUTION END\r\n";
    lib::Stream::cout() << "[EOOS ] ~~~ eoos end ~~~~~~~~~~~~~~~~~~~\r\n";    
}

} // namespace eoos

/**
 * @brief The main function.
 *
 * This function starts all the testsuites and is defined here as the EOOS library may have 
 * its own main() function defined and this definition will make a linker link the main(). 
 *
 * @param argc  The number of arguments passed to the program.
 * @param argv  An array of c-string of arguments where the last one - argc + 1 is null.
 * @return Error code or zero.
 */
int main(int argc, char** const argv)
{    
    ::eoos::printConfiguration();
    ::testing::InitGoogleTest(&argc, argv);
    int const error( RUN_ALL_TESTS() );
    ::eoos::printExecutionEnding();
    return error;
}
