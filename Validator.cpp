#include "Validator.h"
#include <cctype>

bool Validator::isValidType(const std::string &type)
{
    return (type == "INT" || type == "FLOAT" || type == "STRING");
}

bool Validator::isValidIdentifier(const std::string &token)
{
    if (token.empty())
        return false;

    // Reject keywords used in mini-language
    if (token == "DECLARE" || token == "SET" || token == "PRINT" ||
        token == "SHOW" || token == "EXIT" || token == "INT" ||
        token == "FLOAT" || token == "STRING")
    {
        return false;
    }

    // identifier must begin with a letter
    if (!std::isalpha(token[0]))
    {
        return false;
    }

    // must contain only letters, digits, or underscores
    for (size_t i = 1; i < token.length(); i++)
    {
        char c = token[i];

        // if isn't alpha number and not equal to _ symbol
        if (!std::isalnum(c) && c != '_')
        {
            return false;
        }
    }

    return true;
}

bool Validator::isValidInt(const std::string &val)
{
    if (val.empty())
        return false;

    size_t start = (val[0] == '+' || val[0] == '-') ? 1 : 0;
    if (start == val.length())
        return false;

    for (size_t i = start; i < val.length(); ++i)
    {
        if (!std::isdigit(val[i]))
        {
            return false;
        }
    }

    return true;
}


bool Validator::isValidFloat(const std::string& val) {
    if (val.empty()) return false;

    size_t start = (val[0] == '+' || val[0] == '-') ? 1 : 0;
    if (start == val.length()) 
        return false;

    bool hasDot = false;
    bool hasDigit = false;

    for (size_t i = start; i < val.length(); ++i) {
        char c = val[i];
        if (c == '.') {
            if (hasDot) return false; // Max 1 decimal point
            hasDot = true;
        } else if (std::isdigit(c)) {
            hasDigit = true;
        } else {
            return false;
        }
    }
    return hasDigit;
}


bool Validator::isValidString(const std::string& val) {
    // Must have at least empty quotes ("") and start/end with quotes
    return val.length() >= 2 && val.front() == '"' && val.back() == '"';
}

bool Validator::matchesType(const std::string& type, const std::string& value)
{
    if (type == "INT")
        return isValidInt(value);
    if (type == "FLOAT")
        return isValidFloat(value);
    if (type == "STRING")
        return isValidString(value);
    return false;
}
