/** \file FileReader.h
 *  \brief This file declares FileReader class for shells file mode, implements IReader
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 25/04/2025
*/

#ifndef FILE_READER_H
#define FILE_READER_H

#include "IReader.h"

class FileReader: public IReader {
public:
    virtual std::string readLine() final;
    virtual bool isFinished() final;
    FileReader();
};

#endif // FILE_READER_H