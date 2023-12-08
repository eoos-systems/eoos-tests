/**
 * @file      Tests.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021-2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Global definitions of Unit Tests. 
 */
#ifndef TESTS_HPP_
#define TESTS_HPP_

#include "gtest/gtest.h"
#include "Types.hpp"

/**
 * @brief Number of cycles when a test would wait a result.
 */
#ifndef EOOS_TESTS_WAIT_CYCLE_TIME
    #define EOOS_TESTS_WAIT_CYCLE_TIME (0x0FFFFFFF)
#endif

namespace eoos
{

/**
 * @brief Number of cycles when a test would wait a result.
 */
static const uint32_t TESTS_WAIT_CYCLE_TIME( EOOS_TESTS_WAIT_CYCLE_TIME );

/**
 * @class NullAllocator
 * @brief No memory allocator.
 */
class NullAllocator
{

public:

    /**
     * @brief Returns nullptr.
     *
     * @return the null pointer.
     */    
    static void* allocate(size_t)
    {
        return NULLPTR;
    }

    /**
     * @brief Does nothing.
     */    
    static void free(void*)
    {
    }

};

} // namespace eoos

#endif // TESTS_HPP_
