/**
 * @file      System.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "sys.Call.hpp"
#include "Tests.hpp"

namespace eoos
{

/**
 * @class System
 * @brief Operating system for Unit Tests.
 */
class System final
{
public:

    /**
     * @brief Constructor.
     */
    System()
    {
        sys::Call::initialize();
    }

    /**
     * @brief Destructor.
     */
    ~System()
    {
        sys::Call::deinitialize();
    }

    /**
     * @brief Executes the operating system.
     *
     * @return zero, or error code if the execution has been terminated.
     */
    int32_t execute()
    {
        return sys::Call::execute();
    }

};

} // namespace eoos

#endif // SYSTEM_HPP_
