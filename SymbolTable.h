#pragma once

#include <iostream>
#include <map>
#include "Symbol.h"


class SymbolTable {

    // Symbol is defined in Symbol.h (contains: 3 strings (name, type, value) and bool isInitialized)
    std::map<std::string, Symbol> symbols;


    public:

    // No need for constructor/destructor, this is handled by C++ and map library

    // Bool Checks and Setters
    bool isDeclared(const std::string& name) const;
    bool declareVariable(const std::string& name, const std::string& type, const std::string& value);
    bool setVariable(const std::string& name, const std::string& value);


    // With const at beginning (protects returned data)
    // Symbol getter, returns pointer of Symbol object that is unmodifyable, 
    // while not modifying and data in SymbolTable class (const at end)
    const Symbol* getVariable(const std::string& name) const;
    std::string getType(const std::string& name) const;

    // Displays contents of SymbolTable
    void displayAll() const;

};