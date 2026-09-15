#include <iostream>
#include <string>

#include "Interpreter.h"

int main() {
Interpreter interpreter;
    std::string line;

    std::cout << "Type HELP to get started." << std::endl;

    while (true) {
        std::cout << "> ";
        
        // Read input line
        if (!std::getline(std::cin, line)) {
            break; 
        }

        // Pass raw line directly to Interpreter
        // Interpreter handles tokenization, blank lines, EXIT, and dispatching
        if (!interpreter.processLine(line)) {
            break;
        }
    }

    return 0;
}