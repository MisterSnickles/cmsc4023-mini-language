#include "Interpreter.h"
#include "Validator.h"
#include <cctype>
#include <iostream>

std::vector<std::string> Interpreter::tokenize(const std::string &line, bool &syntaxError) const
{
    std::vector<std::string> tokens;
    std::string currentToken;

    bool inQuotes = false;
    syntaxError = false;

    // for loop to iterate parsed characters
    for (size_t i = 0; i < line.size(); i++)
    {
        char c = line[i];

        // If during the character parsing we find a quotation
        if (c == '"')
        {
            inQuotes = !inQuotes;
            currentToken += c;
        }

        // If during character parsing we find a space
        else if (std::isspace(c))
        {
            // if have reached the end of a word
            if (inQuotes == false && currentToken != "")
            {
                tokens.push_back(currentToken);
                // once current token is pushed, make sure to clear it
                currentToken = "";
            }
        }

        // else treat like a normal character
        else
        {
            currentToken += c;
        }
    }

    // if quotes are unclosed
    if (inQuotes == true)
    {
        syntaxError = true;
        return {};
    }

    if (currentToken != "")
    {
        tokens.push_back(currentToken);
    }

    return tokens;
}

void Interpreter::handleDeclare(const std::vector<std::string> &tokens)
{
    // A decalare command from user looks like (DECLARE INT count) which has 3 tokens
    // Verify user input has 4 tokens
    if (tokens.size() != 3)
    {
        std::cout << "Syntax Error: DECLARE expects 3 arguments (type, name, value)." << std::endl;
        return;
    }

    // define variables to check if is valid, type, identifier, match
    bool typeCheck = Validator::isValidType(tokens[1]);
    bool identifierCheck = Validator::isValidIdentifier(tokens[2]);

    // Throw error messages if above are false
    if (!typeCheck)
    {
        std::cout << "Syntax Error: Invalid type '" << tokens[1] << "'.\n";
        return;
    }
    else if (!identifierCheck)
    {
        std::cout << "Syntax Error: Invalid identifier '" << tokens[2] << "'.\n";
        return;
    }


    if (symbolTable.isDeclared(tokens[2]))
    {
        std::cout << "Redeclaration Error:  Variable " << tokens[2] << " already exists." << std::endl;
        return;
    }

    symbolTable.declareVariable(tokens[2], tokens[1]);
}


void Interpreter::handleSet(const std::vector<std::string> &tokens)
{

    // Token size should be 3 for setting
     if (tokens.size() != 3)
    {
        std::cout << "Syntax Error: SET expects 2 arguments (name, value)." << std::endl;
        return;
    }

    if (!symbolTable.isDeclared(tokens[1])) 
    {
        std::cout << "Undeclared Variable Error" << std::endl;
        return;
    }

    // get the symbol pointer to check if type matches
    const Symbol* symbol = symbolTable.getVariable(tokens[1]);

    // check if type matches
    if (!Validator::matchesType(symbol->type, tokens[2])) {
        std::cout << "Type Error: Cannot assign '" << tokens[2] << "' to variable of type " << symbol->type << "." << std::endl;
        return;
    }
    
    // If above passes, set variable to new value
    symbolTable.setVariable(tokens[1], tokens[2]);
}

void Interpreter::handlePrint(const std::vector<std::string> &tokens) const
{

    if (tokens.size() != 2)
    {
        std::cout << "Syntax Error: PRINT expects 1 argument (name)." << std::endl;
        return;
    }

    const std::string& name = tokens[1];

    if (!symbolTable.isDeclared(name)) {
        std::cout << "Undeclared Variable Error: '" << name << "' does not exist.\n";
        return;
    }

    const Symbol* sym = symbolTable.getVariable(name);
    std::cout << sym->value << std::endl;
}

void Interpreter::handleShow(const std::vector<std::string> &tokens) const
{

    if (tokens.size() != 1) {
        std::cout << "Syntax Error: SHOW command does not accept extra arguments.\n";
        return;
    }
    symbolTable.displayAll();
}

bool Interpreter::processLine(const std::string &line)
{
    bool syntaxError = false;
    const std::vector<std::string> tokens = tokenize(line, syntaxError);

    if (syntaxError)
    {
        std::cout << "Syntax Error: Unclosed quotation mark.\n";
        return true;
    }

    if (tokens.empty())
        return true;

    if (tokens[0] == "EXIT")
        return tokens.size() == 1 ? false : true;
    if (tokens[0] == "DECLARE")
        handleDeclare(tokens);
    else if (tokens[0] == "SET")
        handleSet(tokens);
    else if (tokens[0] == "PRINT")
        handlePrint(tokens);
    else if (tokens[0] == "SHOW")
        handleShow(tokens);
    else
        std::cout << "Syntax Error: Unknown command '" << tokens[0] << "'.\n";

    return true;
}
