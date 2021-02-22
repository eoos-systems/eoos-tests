/**
 * @brief Global definitions of Unit Tests.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021, Sergey Baigudin, Baigudin Software
 */
#ifndef TESTS_HPP_
#define TESTS_HPP_

#include <iostream>
#include "gtest/gtest.h"
#include "Types.hpp"

/**
 * @brief Number of cycles when a test would wait a result.
 */
#ifndef EOOS_TESTS_WAIT_CYCLE_TIME
    #define EOOS_TESTS_WAIT_CYCLE_TIME (0x00ffffff)
#endif

namespace eoos
{

/**
 * @brief Number of cycles when a test would wait a result.
 */
static const uint32_t TESTS_WAIT_CYCLE_TIME { EOOS_TESTS_WAIT_CYCLE_TIME };

} // namespace eoos

#endif // TESTS_HPP_
