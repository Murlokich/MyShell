/** \file main.cpp
 *  \brief This file runs event loop for shell implementation for course COMP-354 project in University Of Nicosia
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 17/04/2025
*/

#include "../include/shell/Wish.h"

/**
 * <code>main</code> is the main function of this program.
 * <BR>
 * @return Returns 0 if success, any other value otherwise.
 */
int main(int argc, const char * argv[]) {
    auto wish = Wish(argc, argv);
    auto res = wish.run();
    if (res != 0) {
        Wish::printError();
    }
    exit(res);
}