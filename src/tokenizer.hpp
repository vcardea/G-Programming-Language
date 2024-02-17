/**
 * @file    G-Programming-Language/Compiler/tokenizer.hpp
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.1
 * @date    2023-
 *
 * @copyright Copyright (c) 2023
 */

#ifndef G_TOKENIZER_HPP
#define G_TOKENIZER_HPP
#pragma once

#include <iostream>
#include <vector>
#include "./utils.hpp"

enum class TokenType
{
    FALSE,
    TRUE,
    IDENTIFIER,
    INT_KEYWORD,
    FLOAT_KEYWORD,
    CHAR_KEYWORD,
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
    BACKSLASH
};

struct Token
{
    TokenType type;
    std::string value;
    bool isvalid = true;
};

class Tokenizer
{
public:
    Tokenizer(const std::string &sourcecode) : sourcecode(sourcecode), pos(0) {}

    std::vector<Token> lex()
    {
        std::vector<Token> tokens;

        int line = 1;
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
                while (isalnum(sourcecode[pos]))
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
                }

                if (token_value == "false")
                {
                    tokens.push_back({TokenType::FALSE, token_value});
                }
                else if (token_value == "true")
                {
                    tokens.push_back({TokenType::TRUE, token_value});
                }
                else if (token_value == "int")
                {
                    tokens.push_back({TokenType::INT_KEYWORD, token_value});
                }
                else if (token_value == "float")
                {
                    tokens.push_back({TokenType::FLOAT_KEYWORD, token_value});
                }
                else if (token_value == "char")
                {
                    tokens.push_back({TokenType::CHAR_KEYWORD, token_value});
                }
                else
                {
                    tokens.push_back({TokenType::IDENTIFIER, token_value, (token_value.size() <= 32)});
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
                        tokens.push_back({TokenType::FLOAT_LITERAL, s, false});
                        std::stringstream error;
                        error << "Invalid float literal at line ";
                        error << line << ". Token found: '" << s << "'. ";
                        error << "A digit was expected after '.' character.";
                        error_message(error.str());
                    }
                    else if (is_float)
                    {
                        tokens.push_back({TokenType::FLOAT_LITERAL, s});
                    }
                    else
                    {
                        tokens.push_back({TokenType::INT_LITERAL, s});
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
                        tokens.push_back({TokenType::FLOAT_LITERAL, s, false});
                    }
                    else
                    {
                        tokens.push_back({TokenType::INT_LITERAL, s, false});
                    }
                }

                continue;
            }

            // Recognize symbols (see G-Programming-Language\docs\regex.txt)
            if (current_char == ';')
            {
                tokens.push_back({TokenType::SEMICOLON, ";"});
            }
            else if (current_char == '.')
            {
                tokens.push_back({TokenType::DOT, "."});
            }
            else if (current_char == ':')
            {
                tokens.push_back({TokenType::COLON, ":"});
            }
            else if (current_char == ',')
            {
                tokens.push_back({TokenType::COMMA, ","});
            }
            else if (current_char == '=')
            {
                if (lookahead(sourcecode, pos) == '=')
                {
                    tokens.push_back({TokenType::EQUAL, "=="});
                    pos++;
                }
                else
                {
                    tokens.push_back({TokenType::ASSIGN, "="});
                }
            }
            else if (current_char == '>')
            {
                if (lookahead(sourcecode, pos) == '=')
                {
                    tokens.push_back({TokenType::GREATER_EQUAL, ">="});
                    pos++;
                }
                else
                {
                    tokens.push_back({TokenType::GREATER, ">"});
                }
            }
            else if (current_char == '<')
            {
                if (lookahead(sourcecode, pos) == '=')
                {
                    tokens.push_back({TokenType::LOWER_EQUAL, "<="});
                    pos++;
                }
                else
                {
                    tokens.push_back({TokenType::LOWER, "<"});
                }
            }
            else if (current_char == '!')
            {
                if (lookahead(sourcecode, pos) == '=')
                {
                    tokens.push_back({TokenType::NOT_EQUAL, "!="});
                    pos++;
                }
                else
                {
                    tokens.push_back({TokenType::NOT_LOGIC, "!"});
                }
            }
            else if (current_char == '&')
            {
                if (lookahead(sourcecode, pos) == '&')
                {
                    tokens.push_back({TokenType::AND_CONDITIONAL, "&&"});
                    pos++;
                }
                else
                {
                    tokens.push_back({TokenType::AND_LOGIC, "&"});
                }
            }
            else if (current_char == '|')
            {
                if (lookahead(sourcecode, pos) == '|')
                {
                    tokens.push_back({TokenType::OR_CONDITIONAL, "||"});
                    pos++;
                }
                else
                {
                    tokens.push_back({TokenType::OR_LOGIC, "|"});
                }
            }
            else if (current_char == '+')
            {
                if (lookahead(sourcecode, pos) == '+')
                {
                    tokens.push_back({TokenType::INC, "++"});
                    pos++;
                }
                else
                {
                    tokens.push_back({TokenType::PLUS, "+"});
                }
            }
            else if (current_char == '-')
            {
                if (lookahead(sourcecode, pos) == '-')
                {
                    tokens.push_back({TokenType::DEC, "--"});
                    pos++;
                }
                else
                {
                    tokens.push_back({TokenType::MINUS, "-"});
                }
            }
            else if (current_char == '*')
            {
                tokens.push_back({TokenType::MULTIPLY, "*"});
            }
            else if (current_char == '/')
            {
                tokens.push_back({TokenType::DIVIDE, "/"});
            }
            else if (current_char == '%')
            {
                tokens.push_back({TokenType::MODULO, "%"});
            }
            else if (current_char == '\\')
            {
                tokens.push_back({TokenType::BACKSLASH, "\\"});
            }
            else if (current_char == '(')
            {
                tokens.push_back({TokenType::OPEN_PARENTHESIS, "("});
            }
            else if (current_char == ')')
            {
                tokens.push_back({TokenType::CLOSE_PARENTHESIS, ")"});
            }
            else if (current_char == '[')
            {
                tokens.push_back({TokenType::OPEN_SQUARE, "["});
            }
            else if (current_char == ']')
            {
                tokens.push_back({TokenType::CLOSE_SQUARE, "]"});
            }
            else if (current_char == '{')
            {
                tokens.push_back({TokenType::OPEN_CURLY, "{"});
            }
            else if (current_char == '}')
            {
                tokens.push_back({TokenType::CLOSE_CURLY, "}"});
            }
            else if (current_char == '\'')
            {
                pos++;
                std::stringstream ss;
                while (sourcecode[pos] != '\'')
                {
                    ss << sourcecode[pos++];
                }
                std::string token_value = ss.str();

                if (token_value.size() > 1)
                {
                    std::stringstream error;
                    error << "Invalid character literal at line ";
                    error << line << ". Token found: '" << token_value << "'. ";
                    error << "A char literal has to be 1 character long.";
                    error_message(error.str());
                }
                tokens.push_back({TokenType::CHAR_LITERAL, token_value, (token_value.size() <= 1)});
            }
            else
            {
                std::cerr << "[!] Invalid character: " << current_char << std::endl;
                pos++;
            }
            pos++;
        }

        return tokens;
    }

private:
    std::string sourcecode;
    size_t pos;
};

#endif // G_TOKENIZER_HPP