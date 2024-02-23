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
    BOOLEAN_KEYWORD,
    IDENTIFIER,
    INT_KEYWORD,
    FLOAT_KEYWORD,
    CHAR_KEYWORD,
    STRING_KEYWORD,
    NULL_KEYWORD,
    USER_DEFINED_TYPE, // TODO: IMPLEMENT
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
    INT_LITERAL,
    FLOAT_LITERAL,
    CHAR_LITERAL,
    STRING_LITERAL,
    USER_DATATYPE_LITERAL, // TODO: IMPLEMENT
    BACKSLASH,
    SINGLE_LINE_COMMENT,
    MULTI_LINE_COMMENT,
    UNDEFINED,
    EOF_TOKEN
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
class Tokenizer
{
public:
    /**
     * Default constuctor
     *
     * @param sourcecode string containing the source code
     */
    Tokenizer(const std::string &sourcecode) : sourcecode(sourcecode), pos(0) {}

    /**
     * Lexycal analyzer
     *
     * @return a vector of tokens
     */
    std::vector<Token> lex()
    {
        std::vector<Token> tokens;

        size_t line = 1;
        while (pos < sourcecode.length())
        {
            char current_char = sourcecode[pos];

            if (isskippable(current_char))
            {
                pos++;
                continue;
            }

            if (isnewline(current_char))
            {
                line++;
                pos++;
                continue;
            }

            // Recognize identifiers and keywords (see G-Programming-Language\docs\regex.txt)
            if (isalpha(current_char))
            {
                int length = pos;
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
                    error_message(error.str());
                    unvalidate();
                }

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
                else
                {
                    tokens.push_back({TokenType::IDENTIFIER, token_value, line, (token_value.size() <= 32)});
                }

                continue;
            }

            // Recognize int literals (see G-Programming-Language\docs\regex.txt)
            if (isdigit(current_char))
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

                while (isskippable(sourcecode[pos]))
                {
                    pos++;
                }

                std::string s = ss.str();
                if (is_number_literal_end(sourcecode[pos]))
                {
                    if (s[s.size() - 1] == '.')
                    {
                        tokens.push_back({TokenType::FLOAT_LITERAL, s, line, false});
                        std::stringstream error;
                        error << "Invalid float literal at line ";
                        error << line << ". Token found: '" << s << "'. ";
                        error << "A digit was expected after '.' character.";
                        error_message(error.str());
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
                    while (!is_number_literal_end(sourcecode[pos]))
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

                continue;
            }

            // Recognize symbols (see G-Programming-Language\docs\regex.txt)
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
                if (lookahead(sourcecode, pos) == '=')
                {
                    tokens.push_back({TokenType::EQUAL, "==", line});
                    pos++;
                }
                else
                {
                    tokens.push_back({TokenType::ASSIGN, "=", line});
                }
            }
            else if (current_char == '>')
            {
                if (lookahead(sourcecode, pos) == '=')
                {
                    tokens.push_back({TokenType::GREATER_EQUAL, ">=", line});
                    pos++;
                }
                else
                {
                    tokens.push_back({TokenType::GREATER, ">", line});
                }
            }
            else if (current_char == '<')
            {
                if (lookahead(sourcecode, pos) == '=')
                {
                    tokens.push_back({TokenType::LOWER_EQUAL, "<=", line});
                    pos++;
                }
                else
                {
                    tokens.push_back({TokenType::LOWER, "<", line});
                }
            }
            else if (current_char == '!')
            {
                if (lookahead(sourcecode, pos) == '=')
                {
                    tokens.push_back({TokenType::NOT_EQUAL, "!=", line});
                    pos++;
                }
                else
                {
                    tokens.push_back({TokenType::NOT_LOGIC, "!", line});
                }
            }
            else if (current_char == '&')
            {
                if (lookahead(sourcecode, pos) == '&')
                {
                    tokens.push_back({TokenType::AND_CONDITIONAL, "&&", line});
                    pos++;
                }
                else
                {
                    tokens.push_back({TokenType::AND_LOGIC, "&", line});
                }
            }
            else if (current_char == '|')
            {
                if (lookahead(sourcecode, pos) == '|')
                {
                    tokens.push_back({TokenType::OR_CONDITIONAL, "||", line});
                    pos++;
                }
                else
                {
                    tokens.push_back({TokenType::OR_LOGIC, "|", line});
                }
            }
            else if (current_char == '+')
            {
                if (lookahead(sourcecode, pos) == '+')
                {
                    tokens.push_back({TokenType::INC, "++", line});
                    pos++;
                }
                else
                {
                    tokens.push_back({TokenType::PLUS, "+", line});
                }
            }
            else if (current_char == '-')
            {
                if (lookahead(sourcecode, pos) == '-')
                {
                    tokens.push_back({TokenType::DEC, "--", line});
                    pos++;
                }
                else
                {
                    tokens.push_back({TokenType::MINUS, "-", line});
                }
            }
            else if (current_char == '*')
            {
                tokens.push_back({TokenType::MULTIPLY, "*", line});
            }
            else if (current_char == '/')
            {
                if (sourcecode[pos + 1] == '/')
                {
                    size_t size = sourcecode.size();
                    std::stringstream ss;
                    while (!isnewline(sourcecode[pos]) && pos < size)
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
                std::stringstream ss;
                bool error = false;
                size_t backslash = 0;
                while (sourcecode[pos] != '\'')
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

                if (token_size > 1)
                {
                    std::stringstream error;
                    error << "Invalid character literal at line ";
                    error << line << ". Token found: '" << token_value << "'. ";
                    error << "A char literal has to be 1 character long.";
                    error_message(error.str());
                    unvalidate();
                }

                if (error)
                {
                    std::stringstream error;
                    error << "Invalid character literal at line ";
                    error << line << ". Token found: '" << token_value << "'. ";
                    error << "Escape characters: \\<char>.";
                    error_message(error.str());
                    unvalidate();
                }

                tokens.push_back({TokenType::CHAR_LITERAL, token_value, line, (token_size <= 1)});
            }
            else if (current_char == '\"')
            {
                pos++;
                std::stringstream ss;
                bool error = false;
                size_t backslash = 0;
                while (sourcecode[pos] != '\"')
                {
                    if (sourcecode[pos] == '\\')
                    {
                        char c = sourcecode[pos + 1];
                        if (c == '\'')
                        {
                            ss << c;
                            pos += 2;
                            backslash++;
                        }
                        else if (c == '"')
                        {
                            for (int i = 0; i < 2; i++)
                            {
                                ss << sourcecode[pos++];
                            }
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

                if (error)
                {
                    std::stringstream error;
                    error << "Invalid character literal at line ";
                    error << line << ". Token found: '" << token_value << "'. ";
                    error << "Escape characters: \\<char>.";
                    error_message(error.str());
                    unvalidate();
                }

                tokens.push_back({TokenType::STRING_LITERAL, ss.str(), line});
            }
            else
            {
                std::stringstream ss;
                ss << "Invalid character '" << current_char;
                ss << "' at line " << line << ".";
                error_message(ss.str());
                ss.clear();
                ss << current_char;
                tokens.push_back({TokenType::UNDEFINED, ss.str(), line, false});
                unvalidate();
                pos++;
            }
            pos++;
        }

        tokens.push_back({TokenType::EOF_TOKEN, "EOF", line, true});

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
     * Source code
     */
    std::string sourcecode;

    /**
     * Index of the current char
     */
    size_t pos;

    /**
     * If all tokens are valid
     */
    bool valid = true;

    /**
     * Unabled constructor
     */
    Tokenizer() {}

    /**
     * Sets valid property to false
     */
    void unvalidate()
    {
        this->valid = false;
    }
};

#endif // G_TOKENIZER_HPP