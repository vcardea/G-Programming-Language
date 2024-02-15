/**
 * @file    tokenizer.hpp - G-Programming-Language/Compiler/Tokenizer
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

enum class TokenType {
    _false,
    _true,
    identifier,
    integerType,
    characterType,
    assign,
    equal,
    greater,
    lower,
    greater_equal,
    lower_equal,
    plus,
    minus,
    multiply,
    divide,
    modulo,
    int_literal,
    char_literal,
    semicolon
};

typedef struct GToken Token;
struct GToken {
    std::string token_name = "a";
    TokenType type;
};

class Tokenizer
{
    public:
        std::vector<Token> tokens;
        
        explicit Tokenizer(std::string& src)
        {
            this -> sourcecode = src;
            this -> left = 0;
            this -> right = 0;
        }

        std::vector<Token> lex()
        {
            

            return tokens;
        }

    private:
        std::string sourcecode;
        long long left;
        long long right;
};

#endif //G_TOKENIZER_HPP