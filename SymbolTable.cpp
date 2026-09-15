#include "SymbolTable.h"
#include <iomanip>

bool SymbolTable::isDeclared(const std::string& name) const {
    return symbols.find(name) != symbols.end();
}

bool SymbolTable::declareVariable(const std::string& name, const std::string& type) {
    // Check if variable is declared already (if so, return)
    if (isDeclared(name)) { return false; }

    Symbol newSymbol;
    newSymbol.name = name;
    newSymbol.type = type;
    newSymbol.value = "NULL";
    newSymbol.isInitialized = false;
    
    // add symbol to symbols
    symbols[name] = newSymbol;

    return true;
}


const Symbol* SymbolTable::getVariable(const std::string& name) const {
    auto it = symbols.find(name);

    if (it != symbols.end()) {
        return &(it->second); // return address of found symbol
    }
    return nullptr;
}


bool SymbolTable::setVariable(const std::string& name, const std::string& value) {
    // Better for readability, however using isDeclared and symbols[name] will search the map twice
    if (!isDeclared(name)) {
        return false;
    }

    symbols[name].value = value;
    symbols[name].isInitialized = true;
    return true;
}

void SymbolTable::displayAll() const {
    // if (symbols.empty()) {
    //     std::cout << "Symbol table is empty.\n";
    //     return;
    // }

    // Header (left-aligned with sufficient width)
    std::cout << std::left 
              << std::setw(15) << "Name" 
              << std::setw(15) << "Type" 
              << std::setw(20) << "Value" << "\n";
    std::cout << std::string(45, '-') << "\n";

    // Data rows
    for (const auto& pair : symbols) {
        const Symbol& sym = pair.second;
        std::cout << std::left 
                  << std::setw(15) << sym.name 
                  << std::setw(15) << sym.type 
                  << std::setw(15) << sym.value << "\n";
    }
}