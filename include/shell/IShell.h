/** \file IShell.h
 *  \brief This file declares interface for shell
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 25/04/2025
*/

#ifndef ISHELL_H
#define ISHELL_H

class IShell {
public:
    virtual void run() = 0;
    
    virtual ~IShell() = default;
};

#endif // ISHELL_H