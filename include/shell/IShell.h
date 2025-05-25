/** \file IShell.h
 *  \brief This file declares interface for shell
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 25/04/2025
*/

#ifndef ISHELL_H
#define ISHELL_H

/** \class IShell
 *  \brief Interface for a shell implementation.
 *
 *  IShell defines the contract that any shell must fulfill,
 *  namely to provide a `run()` method that drives the shell’s
 *  execution loop.
*/
class IShell {
public:
    /** \brief Execute the shell’s main loop. */
    virtual void run() = 0;
    
    virtual ~IShell() = default;
};


#endif // ISHELL_H