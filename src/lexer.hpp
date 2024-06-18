/**
 * @file    G-Programming-Language/Compiler/tokenizer.hpp
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.1
 * @date    2023-15-02
 *
 * @copyright Copyright (c) 2023
 */

#ifndef G_TOKENIZER_HPP
#define G_TOKENIZER_HPP
#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include "./utils.hpp"

/**
 * List of all types of token
 */
enum class TokenType
{
    FALSE,
    TRUE,
    IDENTIFIER,
    BOOLEAN_KEYWORD,
    INT_KEYWORD,
    FLOAT_KEYWORD,
    CHAR_KEYWORD,
    STRING_KEYWORD,
    NULL_KEYWORD,
    DEFINE_USER_TYPE_KEYWORD,
    USER_DEFINED_TYPE,
    DOT,
    COLON,
    COMMA,
    SEMICOLON,
    ASSIGN,
    EQUAL,
    NOT_EQUAL,
    GREATER,
    LOWER,
    GREATER_EQUAL,
    LOWER_EQUAL,
    NOT_LOGIC,
    AND_CONDITIONAL,
    AND_LOGIC,
    OR_CONDITIONAL,
    OR_LOGIC,
    XOR_LOGIC,
    OPEN_PARENTHESIS,
    CLOSE_PARENTHESIS,
    OPEN_SQUARE,
    CLOSE_SQUARE,
    OPEN_CURLY,
    CLOSE_CURLY,
    PLUS,
    MINUS,
    INC,
    DEC,
    MULTIPLY,
    DIVIDE,
    MODULO,
    LOGIC_OPERATOR,
    ARITHMETIC_OPERATOR,
    ARITHMETIC_LOGIC_OPERATOR,
    INT_LITERAL,
    FLOAT_LITERAL,
    CHAR_LITERAL,
    STRING_LITERAL,
    USER_DATATYPE_LITERAL, // TODO: IMPLEMENT
    BACKSLASH,
    SINGLE_LINE_COMMENT,
    MULTI_LINE_COMMENT,
    UNDEFINED,
    _EOF
};

/**
 * Token struct definition
 */
struct Token
{
    /**
     * Type of token
     */
    TokenType type;

    /**
     * String value of the token
     */
    std::string value;

    /**
     * Line where the token was found
     */
    size_t line = 1;

    /**
     * If a token is lexycally valid
     */
    bool isvalid = true;
};

/**
 * Provides the method Tokenizer.lex() to
 * perform a lexycal analysis of the source code
 */
class Lexer
{
public:
    /**
     * Default constuctor
     *
     * @param sourcecode string containing the source code
     */
    Lexer(const std::string &sourcecode) : sourcecode(sourcecode), pos(0) {}

    /**
     * Lexycal analyzer
     *
     * @return a vector of tokens
     */
    std::vector<Token> lex()
    {
        line = 1;
        while (pos < sourcecode.size())
        {
            current_char = sourcecode[pos];

            if (isSkippable(current_char))
            {
                pos++;
                continue;
            }

            if (isNewLine(current_char))
            {
                line++;
                pos++;
                continue;
            }

            // Recognize identifiers and keywords (see G-Programming-Language\docs\regex.txt)
            if (isalpha(current_char))
            {
                identifierOrKeyword();
                continue;
            }

            // Recognize int literals (see G-Programming-Language\docs\regex.txt)
            if (isdigit(current_char))
            {
                numberLiteral();
                continue;
            }

            // Recognize symbols (see G-Programming-Language\docs\regex.txt)
            operators();

            pos++;
        }

        tokens.push_back({TokenType::_EOF, "_EOF", line});
        return tokens;
    }

    /**
     * Tells if all tokens are valid
     */
    bool areValid()
    {
        return this->valid;
    }

private:
    /**
     * Vector of tokens
     */
    std::vector<Token> tokens;

    /**
     * Source code
     */
    std::string sourcecode;

    /**
     * Index of the current char
     */
    size_t pos;

    /**
     * Current line
     */
    size_t line;

    /**
     * Current char
     */
    char current_char;

    /**
     * If all tokens are valid
     */
    bool valid = true;

    /**
     * Unabled constructor
     */
    Lexer() {}

    /**
     * Consumes a char from the stream
     *
     * @return the new index
     */
    size_t consume()
    {
        pos = std::min(pos + 1, sourcecode.size());
        return pos;
    }

    /**
     * Looks at the (pos + offset)th char
     *
     * @param offset
     * @return char
     */
    char lookahead(size_t offset = 1)
    {
        size_t index = std::min(pos + offset, sourcecode.size());
        return sourcecode[index];
    }

    /**
     * Sets valid property to false
     */
    void unvalidate()
    {
        this->valid = false;
    }

    /**
     * Recognises a string as identifier or keyword
     */
    void identifierOrKeyword()
    {
        if (isalpha(sourcecode[pos]))
        {
            std::stringstream ss;
            while (isalnum(sourcecode[pos]) || sourcecode[pos] == '_')
            {
                ss << sourcecode[pos++];
            }
            std::string token_value = ss.str();

            size_t token_size = token_value.size();
            if (token_size > 32)
            {
                std::stringstream error;
                error << "Too long name for identifier at line ";
                error << line << ". It can't be more than 32 characters long.";
                errorMessage(error.str());
                unvalidate();
            }

            recogniseKeyword(token_value);
        }
    }

    /**
     * Recognises a keyword
     *
     * @param token_value string value of the token
     */
    void recogniseKeyword(std::string token_value)
    {
        if (token_value == "false")
        {
            tokens.push_back({TokenType::FALSE, token_value, line});
        }
        else if (token_value == "true")
        {
            tokens.push_back({TokenType::TRUE, token_value, line});
        }
        else if (token_value == "boolean")
        {
            tokens.push_back({TokenType::BOOLEAN_KEYWORD, token_value, line});
        }
        else if (token_value == "int")
        {
            tokens.push_back({TokenType::INT_KEYWORD, token_value, line});
        }
        else if (token_value == "float")
        {
            tokens.push_back({TokenType::FLOAT_KEYWORD, token_value, line});
        }
        else if (token_value == "char")
        {
            tokens.push_back({TokenType::CHAR_KEYWORD, token_value, line});
        }
        else if (token_value == "string")
        {
            tokens.push_back({TokenType::STRING_KEYWORD, token_value, line});
        }
        else if (token_value == "NULL")
        {
            tokens.push_back({TokenType::NULL_KEYWORD, token_value, line});
        }
        else if (token_value == "define")
        {
            tokens.push_back({TokenType::DEFINE_USER_TYPE_KEYWORD, token_value, line});
        }
        else
        {
            if (!tokens.empty())
            {
                if (tokens.back().type == TokenType::DEFINE_USER_TYPE_KEYWORD)
                {
                    tokens.push_back({TokenType::USER_DEFINED_TYPE, token_value, line, (token_value.size() <= 32)});
                }
                else
                    tokens.push_back({TokenType::IDENTIFIER, token_value, line, (token_value.size() <= 32)});
            }
            else
                tokens.push_back({TokenType::IDENTIFIER, token_value, line, (token_value.size() <= 32)});
        }
    }

    /**
     * Recognises int or float literals
     */
    void numberLiteral()
    {
        std::stringstream ss;
        while (isdigit(sourcecode[pos]))
        {
            ss << sourcecode[pos++];
        }

        bool is_float = false;
        if (sourcecode[pos] == '.')
        {
            is_float = true;
            ss << '.';
            pos++;
            while (isdigit(sourcecode[pos]))
            {
                ss << sourcecode[pos++];
            }
        }

        while (isSkippable(sourcecode[pos]) || isNewLine(sourcecode[pos]))
        {
            pos++;
        }

        std::string s = ss.str();
        if (isNumberLiteralEnd(sourcecode[pos]) || pos == sourcecode.size())
        {
            if (s[s.size() - 1] == '.')
            {
                tokens.push_back({TokenType::FLOAT_LITERAL, s, line, false});
                std::stringstream error;
                error << "Invalid float literal at line ";
                error << line << ". Token found: '" << s << "'. ";
                error << "A digit was expected after '.' character.";
                errorMessage(error.str());
                unvalidate();
            }
            else if (is_float)
            {
                tokens.push_back({TokenType::FLOAT_LITERAL, s, line});
            }
            else
            {
                tokens.push_back({TokenType::INT_LITERAL, s, line});
            }
        }
        else
        {
            while (!isNumberLiteralEnd(sourcecode[pos]) && pos < sourcecode.size())
            {
                ss << sourcecode[pos++];
            }

            if (is_float)
            {
                tokens.push_back({TokenType::FLOAT_LITERAL, s, line, false});
            }
            else
            {
                tokens.push_back({TokenType::INT_LITERAL, s, line, false});
            }
            unvalidate();
        }
    }

    /**
     *
     */
    void operators()
    {
        if (current_char == ';')
        {
            tokens.push_back({TokenType::SEMICOLON, ";", line});
        }
        else if (current_char == '.')
        {
            tokens.push_back({TokenType::DOT, ".", line});
        }
        else if (current_char == ':')
        {
            tokens.push_back({TokenType::COLON, ":", line});
        }
        else if (current_char == ',')
        {
            tokens.push_back({TokenType::COMMA, ",", line});
        }
        else if (current_char == '=')
        {
            assignOrEquals();
        }
        else if (current_char == '>')
        {
            greaterOrGreaterEqual();
        }
        else if (current_char == '<')
        {
            lowerOrLowerEqual();
        }
        else if (current_char == '!')
        {
            notOrNotEqual();
        }
        else if (current_char == '&')
        {
            andOperator();
        }
        else if (current_char == '|')
        {
            orOperator();
        }
        else if (current_char == '+')
        {
            plusOperator();
        }
        else if (current_char == '-')
        {
            minusOperator();
        }
        else if (current_char == '*')
        {
            tokens.push_back({TokenType::MULTIPLY, "*", line});
        }
        else if (current_char == '/')
        {
            comments();
        }
        else if (current_char == '%')
        {
            tokens.push_back({TokenType::MODULO, "%", line});
        }
        else if (current_char == '\\')
        {
            tokens.push_back({TokenType::BACKSLASH, "\\", line});
        }
        else if (current_char == '(')
        {
            tokens.push_back({TokenType::OPEN_PARENTHESIS, "(", line});
        }
        else if (current_char == ')')
        {
            tokens.push_back({TokenType::CLOSE_PARENTHESIS, ")", line});
        }
        else if (current_char == '[')
        {
            tokens.push_back({TokenType::OPEN_SQUARE, "[", line});
        }
        else if (current_char == ']')
        {
            tokens.push_back({TokenType::CLOSE_SQUARE, "]", line});
        }
        else if (current_char == '{')
        {
            tokens.push_back({TokenType::OPEN_CURLY, "{", line});
        }
        else if (current_char == '}')
        {
            tokens.push_back({TokenType::CLOSE_CURLY, "}", line});
        }
        else if (current_char == '\'')
        {
            pos++;
            std::tuple<std::string, size_t, bool> t = stringLiteral('\'');
            std::string token_value = std::get<0>(t);
            size_t token_size = std::get<1>(t);
            bool error = std::get<2>(t);

            if (token_size > 1)
            {
                std::stringstream error;
                error << "Invalid character literal at line ";
                error << line << ". Token found: '" << token_value << "'. ";
                error << "A char literal has to be 1 character long.";
                errorMessage(error.str());
                unvalidate();
            }

            if (error)
            {
                std::stringstream error;
                error << "Invalid character literal at line ";
                error << line << ". Token found: '" << token_value << "'. ";
                error << "Escape characters: \\<char>.";
                errorMessage(error.str());
                unvalidate();
            }

            tokens.push_back({TokenType::CHAR_LITERAL, token_value, line, (token_size <= 1)});
        }
        else if (current_char == '\"')
        {
            pos++;
            std::tuple<std::string, size_t, bool> t = stringLiteral('\"');
            std::string token_value = std::get<0>(t);
            size_t token_size = std::get<1>(t);
            bool error = std::get<2>(t);

            if (error)
            {
                std::stringstream error;
                error << "Invalid character literal at line ";
                error << line << ". Token found: '" << token_value << "'. ";
                error << "Escape characters: \\<char>.";
                errorMessage(error.str());
                unvalidate();
            }

            tokens.push_back({TokenType::STRING_LITERAL, token_value, line});
        }
        else
        {
            std::stringstream ss;
            ss << "Invalid character '" << current_char;
            ss << "' at line " << line << ".";
            errorMessage(ss.str());
            ss.clear();
            ss << current_char;
            tokens.push_back({TokenType::UNDEFINED, ss.str(), line, false});
            unvalidate();
            pos++;
        }
    }

    /**
     * Checks on all escape characters within a string or char literal
     *
     * @param ch either ' or "
     * @return tuple containins: string value of the token, size of the token, if there was an error
     */
    std::tuple<std::string, size_t, bool> stringLiteral(char ch)
    {
        std::stringstream ss;
        bool error = false;
        size_t backslash = 0;
        while (sourcecode[pos] != ch)
        {
            if (sourcecode[pos] == '\\')
            {
                char c = sourcecode[pos + 1];
                if (c == '\'')
                {
                    for (int i = 0; i < 2; i++)
                    {
                        ss << sourcecode[pos++];
                    }
                    backslash++;
                }
                else if (c == '"')
                {
                    ss << c;
                    pos += 2;
                    backslash++;
                }
                else if (c == '?')
                {
                    ss << c;
                    pos += 2;
                    backslash++;
                }
                else if (c == '\\')
                {
                    for (int i = 0; i < 2; i++)
                    {
                        ss << sourcecode[pos++];
                    }
                    backslash++;
                }
                else if (c == 'a')
                {
                    for (int i = 0; i < 2; i++)
                    {
                        ss << sourcecode[pos++];
                    }
                    backslash++;
                }
                else if (c == 'b')
                {
                    for (int i = 0; i < 2; i++)
                    {
                        ss << sourcecode[pos++];
                    }
                    backslash++;
                }
                else if (c == 'f')
                {
                    for (int i = 0; i < 2; i++)
                    {
                        ss << sourcecode[pos++];
                    }
                    backslash++;
                }
                else if (c == 'n')
                {
                    for (int i = 0; i < 2; i++)
                    {
                        ss << sourcecode[pos++];
                    }
                    backslash++;
                }
                else if (c == 'r')
                {
                    for (int i = 0; i < 2; i++)
                    {
                        ss << sourcecode[pos++];
                    }
                    backslash++;
                }
                else if (c == 't')
                {
                    for (int i = 0; i < 2; i++)
                    {
                        ss << sourcecode[pos++];
                    }
                    backslash++;
                }
                else if (c == 'v')
                {
                    for (int i = 0; i < 2; i++)
                    {
                        ss << sourcecode[pos++];
                    }
                    backslash++;
                }
                else
                {
                    error = true;
                }
            }
            else
            {
                ss << sourcecode[pos++];
            }
        }
        std::string token_value = ss.str();
        size_t token_size = token_value.size() - backslash;

        return {token_value, token_size, error};
    }

    /**
     * Detects all comments and ignores them
     */
    void comments()
    {
        if (sourcecode[pos + 1] == '/')
        {
            size_t size = sourcecode.size();
            std::stringstream ss;
            while (!isNewLine(sourcecode[pos]) && pos < size)
            {
                ss << sourcecode[pos++];
            }
            // tokens.push_back({TokenType::SINGLE_LINE_COMMENT, ss.str(), line});
        }
        else if (sourcecode[pos + 1] == '*')
        {
            size_t size = sourcecode.size();
            std::stringstream ss;
            while (!(sourcecode[pos] == '*' && sourcecode[pos + 1] == '/') && pos < size)
            {
                ss << sourcecode[pos++];
            }

            if (pos < size)
            {
                ss << sourcecode[pos++];
                ss << sourcecode[pos++];
            }
            // tokens.push_back({TokenType::MULTI_LINE_COMMENT, ss.str(), line});
        }
        else
        {
            tokens.push_back({TokenType::DIVIDE, "/", line});
        }
    }

    /**
     * Checks if the operator is a minus sign '-' or
     * a decrement operator '--'
     */
    void minusOperator()
    {
        if (lookahead() == '-')
        {
            tokens.push_back({TokenType::DEC, "--", line});
            pos++;
        }
        else
        {
            tokens.push_back({TokenType::MINUS, "-", line});
        }
    }

    /**
     * Checks if the operator is a plus sign '+' or
     * an increment operator '++'
     */
    void plusOperator()
    {
        if (lookahead() == '+')
        {
            tokens.push_back({TokenType::INC, "++", line});
            pos++;
        }
        else
        {
            tokens.push_back({TokenType::PLUS, "+", line});
        }
    }

    /**
     * Checks if the operator is either a logic OR operator '|'
     * or a conditional operator OR '||'
     */
    void orOperator()
    {
        if (lookahead() == '|')
        {
            tokens.push_back({TokenType::OR_CONDITIONAL, "||", line});
            pos++;
        }
        else
        {
            tokens.push_back({TokenType::OR_LOGIC, "|", line});
        }
    }

    /**
     * Checks if the operator is either a logic AND operator '&'
     * or a conditional operator AND '&&'
     */
    void andOperator()
    {
        if (lookahead() == '&')
        {
            tokens.push_back({TokenType::AND_CONDITIONAL, "&&", line});
            pos++;
        }
        else
        {
            tokens.push_back({TokenType::AND_LOGIC, "&", line});
        }
    }

    /**
     * Checks if the token is a not equal operator '!=' or
     * logic NOT operator '!'
     */
    void notOrNotEqual()
    {
        if (lookahead() == '=')
        {
            tokens.push_back({TokenType::NOT_EQUAL, "!=", line});
            pos++;
        }
        else
        {
            tokens.push_back({TokenType::NOT_LOGIC, "!", line});
        }
    }

    /**
     * Checks if the operator is either a lower equal '<='
     * or lower than '<' operator
     */
    void lowerOrLowerEqual()
    {
        if (lookahead() == '=')
        {
            tokens.push_back({TokenType::LOWER_EQUAL, "<=", line});
            pos++;
        }
        else
        {
            tokens.push_back({TokenType::LOWER, "<", line});
        }
    }

    /**
     * Checks if the operator is either a greater equal '>='
     * or greater than '>' operator
     */
    void greaterOrGreaterEqual()
    {
        if (lookahead() == '=')
        {
            tokens.push_back({TokenType::GREATER_EQUAL, ">=", line});
            pos++;
        }
        else
        {
            tokens.push_back({TokenType::GREATER, ">", line});
        }
    }

    /**
     * Checks if the operator is either a equals '=='
     * or assign '=' operator
     */
    void assignOrEquals()
    {
        if (lookahead() == '=')
        {
            tokens.push_back({TokenType::EQUAL, "==", line});
            pos++;
        }
        else
        {
            tokens.push_back({TokenType::ASSIGN, "=", line});
        }
    }
};

#endif // G_TOKENIZER_HPP