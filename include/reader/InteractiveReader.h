/** \file InteractiveReader.h
 *  \brief This file declares InteractiveReader class for shells interactive mode, implements IReader
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 26/04/2025
*/

#ifndef INTERACTIVE_READER_H
#define INTERACTIVE_READER_H

#include "IReader.h"

class InteractiveReader: public IReader {
    bool finished = false;
public:
    virtual std::optional<std::string> readLine() final;
    InteractiveReader();
};

#endif // INTERACTIVE_READER_H