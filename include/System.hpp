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
        : isInitialized_ (sys::Call::initialize()) {
    }

    /**
     * @brief Destructor.
     */
    ~System()
    {
        sys::Call::deinitialize();
    }
    
    /**
     * @brief Tests if the OS has been initialized.
     *
     * @return True if the OS has been initialized successfully.
     */
    bool_t isInitialized() const
    {
        return isInitialized_;
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
	
private:
    
    bool_t isInitialized_;

};

} // namespace eoos

#endif // SYSTEM_HPP_
