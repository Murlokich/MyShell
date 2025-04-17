/** \file main.cpp
 *  \brief This file runs event loop for shell implementation for course COMP-354 project in University Of Nicosia
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 17/04/2025
*/

#include <iostream>
#include <string>

const std::string EXIT_COMMAND = "exit";


/**
 * <code>main</code> is the main function of this program.
 * <BR>
 * @return Returns 0 if success, any other value otherwise.
 */
int main() {
    std::string command = "";

    while (command != EXIT_COMMAND) {
        std::getline(std::cin, command);
        std::cout << command << std::endl;
    }
}