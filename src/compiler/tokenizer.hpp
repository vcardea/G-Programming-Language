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
#include <string>

void error_message(std::string msg)
{
    std::cout << "[!] " << msg << std::endl;
}

bool isnewline(char c)
{
    return (c == '\n');
}

enum class TokenType
{
    FALSE,
    TRUE,
    IDENTIFIER,
    INT_KEYWORD,
    CHAR_KEYWORD,
    ASSIGN,
    EQUAL,
    NOT_EQUAL,
    GREATER,
    LOWER,
    GREATER_EQUAL,
    LOWER_EQUAL,
    PLUS,
    MINUS,
    INC,
    DEC,
    MULTIPLY,
    DIVIDE,
    MODULO,
    INT_LITERAL,
    CHAR_LITERAL,
    SEMICOLON
};

struct Token
{
    TokenType type;
    std::string value;
    bool isvalid;
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

            // Ignore white spaces
            if (isspace(current_char))
            {
                pos++;
                continue;
            }

            if (isnewline(current_char))
            {
                line++;
                continue;
            }

            // Recognize identifiers and key words ()
            if (isalpha(current_char))
            {
                int length = pos;
                std::stringstream ss;
                while (isalnum(sourcecode[pos]))
                {
                    ss << sourcecode[pos++];
                }
                std::string token_value = ss.str();
                if (token_value.size() > 32)
                {
                    std::stringstream error;
                    error << "Too long name for identifier at line ";
                    error << line << ".\nIt can't be more than 32 chars long.";
                    error_message(error.str());
                }

                if (token_value == "false")
                {
                    tokens.push_back({TokenType::FALSE, token_value, true});
                }
                else if (token_value == "true")
                {
                    tokens.push_back({TokenType::TRUE, token_value, true});
                }
                else if (token_value == "int")
                {
                    tokens.push_back({TokenType::INT_KEYWORD, token_value, true});
                }
                else if (token_value == "char")
                {
                    tokens.push_back({TokenType::CHAR_KEYWORD, token_value, true});
                }
                else if (token_value == "")
                {
                    tokens.push_back({TokenType::CHAR_LITERAL, token_value, true});
                }
                else
                {
                    tokens.push_back({TokenType::IDENTIFIER, token_value, false});
                }
                continue;
            }

            // Riconoscere i numeri interi
            if (isdigit(current_char))
            {
                std::stringstream ss;
                while (isdigit(sourcecode[pos]))
                {
                    ss << sourcecode[pos++];
                }
                tokens.push_back({TokenType::INT_LITERAL, ss.str()});
                continue;
            }

            // Riconoscere i simboli
            switch (current_char)
            {
            case ';':
                tokens.push_back({TokenType::SEMICOLON, ";"});
                break;
            case '=':
                // = or ==?
                tokens.push_back({TokenType::ASSIGN, "="});
                tokens.push_back({TokenType::EQUAL, "=="});
                break;
            case '>':
                // > or >=?
                tokens.push_back({TokenType::GREATER, ">"});
                tokens.push_back({TokenType::GREATER_EQUAL, ">="});
                break;
            case '<':
                // < or <=?
                tokens.push_back({TokenType::LOWER, "<"});
                tokens.push_back({TokenType::LOWER_EQUAL, "<="});
                break;
            case '+':
                // + or ++?
                tokens.push_back({TokenType::PLUS, "+"});
                tokens.push_back({TokenType::INC, "++"});
                break;
            case '-':
                // - or --?
                tokens.push_back({TokenType::MINUS, "-"});
                tokens.push_back({TokenType::DEC, "--"});
                break;
            case '*':
                tokens.push_back({TokenType::MULTIPLY, "*"});
                break;
            case '/':
                tokens.push_back({TokenType::DIVIDE, "/"});
                break;
            case '%':
                tokens.push_back({TokenType::MODULO, "%"});
                break;
            default:
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