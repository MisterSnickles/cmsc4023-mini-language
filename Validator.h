#pragma once

#include <string>


class Validator {
private:
    static bool isValidInt(const std::string& val);
    static bool isValidFloat(const std::string& val);
    static bool isValidString(const std::string& val);

public:

    Validator() = delete; // disables object instatiation
    
    // using static functions for utility/readability so we don't need to create a validator object
    // Identifier and type check
    static bool isValidIdentifier(const std::string& token);
    static bool isValidType(const std::string& type);

    // Type binding check
    static bool matchesType(const std::string& type, const std::string& value);

};