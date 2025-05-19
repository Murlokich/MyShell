/** \file FileReader.h
 *  \brief This file declares FileReader class for shells file mode, implements IReader
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 25/04/2025
*/

#ifndef FILE_READER_H
#define FILE_READER_H

#include "IReader.h"
#include <fstream>

class FileReader: public IReader {
    std::fstream file_;
public:
    virtual std::optional<std::string> readLine() final;
    FileReader(const std::string &filename);
};

#endif // FILE_READER_H