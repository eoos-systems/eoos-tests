/**
 * @file      Program.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2025, Sergey Baigudin, Baigudin Software
 */
#ifndef PROGRAM_HPP_
#define PROGRAM_HPP_

#include "lib.AbstractTask.hpp"
#include "lib.NoAllocator.hpp"

namespace eoos
{

/**
 * @class Program
 * @brief Entry point to the main program task.
 */
class Program : public lib::AbstractTask<lib::NoAllocator>
{

public:

    /**
     * @brief Constructor.
     *
     * @param argc  The number of arguments passed to the program.
     * @param argv  An array of c-string of arguments where the last one - argc + 1 is null.
     */
    Program(int argc, char** argv);

    /**
     * @brief Destructor.
     */
    virtual ~Program();

    /**
     * @brief Starts executing the main program task in itself context.
     */
    virtual void start();

    /**
     * @brief Returns the program execution error.
     */
    int getError() const;

private:

    /**
     * @brief The number of arguments passed to the program.
     */
    int argc_;

    /**
     * @brief An array of c-string of arguments where the last one - argc + 1 is null.
     */
    char** argv_;

    /**
     * @brief Program execution error.
     */
    int error_;

};

} // namespace eoos
#endif // PROGRAM_HPP_
