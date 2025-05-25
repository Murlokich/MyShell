/** \file FileReader.h
 *  \brief Declares the FileReader class for shell file mode, implementing IReader.
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 25/04/2025
*/

#ifndef FILE_READER_H
#define FILE_READER_H

#include "IReader.h"

#include <fstream>

/** \class FileReader
 *  \brief Reads input lines from a file for non-interactive shell mode.
 *
 *  FileReader opens the specified file and provides lines to the shell
 *  via the `readLine()` method until EOF is reached.
*/
class FileReader : public IReader {
public:
    /** \brief Read the next line from the file.
     *  \return An optional containing the next line if available; std::nullopt on EOF or error.
    */
    std::optional<std::string> readLine() final;

    /** \brief Construct a FileReader for the given filename.
     *  \param filename The path to the input file to read.
    */
    explicit FileReader(const std::string &filename);

private:
    std::fstream file_;
};

#endif // FILE_READER_H
