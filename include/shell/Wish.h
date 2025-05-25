/** \file Wish.h
 *  \brief Declares the Wish class, the core shell implementation.
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 25/04/2025
 */

#ifndef WISH_H
#define WISH_H

#include "../executor/IExecutor.h"
#include "../parser/IParser.h"
#include "../reader/IReader.h"
#include "IShell.h"

#include <memory>

/** \class Wish
 *  \brief Implements the IShell interface to run shell commands.
 *
 *  The Wish class sets up the shell’s reader, parser, and executor
 *  based on the provided input mode (interactive or file), then
 *  enters the main run loop to process commands.
 */
class Wish : public IShell {
public:
    /** \brief Execute the shell’s main loop. */
    void run() final;

    /** \brief Print the standard shell error message to stderr. */
    static void printError();

    /** \brief Construct a Wish shell with command-line arguments.
     *  \param argc The number of command-line arguments.
     *  \param argv The array of command-line argument strings.
     */
    explicit Wish(int argc, const char * argv[]);

private:
    /** \enum Mode
     *  \brief Internal mode of operation (interactive or batch).
     */
    enum class Mode;

    std::unique_ptr<IReader>   reader_;   ///< \brief Reads input lines (interactive or file).
    std::unique_ptr<IParser>   parser_;   ///< \brief Parses input lines into Command objects.
    std::unique_ptr<IExecutor> executor_; ///< \brief Executes parsed commands.
};

#endif // WISH_H
