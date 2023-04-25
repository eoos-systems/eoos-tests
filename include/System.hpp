/**
 * @file      System.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "sys.Call.hpp"
#include "sys.System.hpp"
#include "Tests.hpp"

namespace eoos
{

/**
 * @class System
 * @brief Operating system for Unit Tests.
 */
class System
{
public:

    /**
     * @brief Constructor.
     */
    System()
    {
    }

    /**
     * @brief Destructor.
     */
    ~System()
    {
    }
    
    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const
    {
        return eoos_.isConstructed();
    }

    /**
     * @brief Executes the operating system.
     *
     * @return zero, or error code if the execution has been terminated.
     */
    int32_t execute()
    {
        return eoos_.execute();
    }
    
    /**
     * @brief Executes the operating system.
     *
     * @param argc The number of arguments passed to the program.
     * @param argv An array of c-string of arguments where the last one - argc + 1 is null.  
     * @return Zero, or error code if the execution has been terminated.
     */
    int32_t execute(int32_t argc, char_t* argv[])
    {
        return eoos_.execute(argc, argv);
    }

private:
    
    sys::System eoos_;

};

} // namespace eoos

#endif // SYSTEM_HPP_
