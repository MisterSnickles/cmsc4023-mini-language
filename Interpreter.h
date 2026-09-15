#pragma once
#include <string>
#include <vector>
#include "SymbolTable.h"

class Interpreter {
private:
    SymbolTable symbolTable;

    // Helper method to split input lines into tokens
    std::vector<std::string> tokenize(const std::string& line, bool& syntaxError) const;

    // Command handlers
    void handleDeclare(const std::vector<std::string>& tokens);
    void handleSet(const std::vector<std::string>& tokens);
    void handlePrint(const std::vector<std::string>& tokens) const;
    void handleShow(const std::vector<std::string>& tokens) const;

public:
    Interpreter() = default;

    // Processes a single input command. Returns false when EXIT is encountered.
    bool processLine(const std::string& line);
};