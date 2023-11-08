/**
 * @file    tokenizer.hpp - G-Programming-Language/Compiler/Tokenizer
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.1
 * @date    2023-11-08
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef G_TOKENIZER_HPP
#define G_TOKENIZER_HPP
#pragma once

#include <iostream>

#include <vector>
#include <string>

short int charToInt(char c)
{
	if (c == '0') return 0;
	if (c == '1') return 1;
	if (c == '2') return 2;
	if (c == '3') return 3;
	if (c == '4') return 4;
	if (c == '5') return 5;
	if (c == '6') return 6;
	if (c == '7') return 7;
	if (c == '8') return 8;
	return 9;
}

enum class TokenType {
    _return,
    identifier,
    integer,
    semicolon
};

struct Token
{
    TokenType type;
};

class Tokenizer
{
    public:
        explicit Tokenizer(std::string& src)
        {
            this -> sourcecode = src;
            this -> currChar = sourcecode[0];
            this -> currCharIndex = 0;
        }

        std::vector<Token> lex()
        {
            std::vector<Token> tokens;
            std::string sToken;

            while (currCharIndex < sourcecode.length())
            {
            	std::cout << currChar << "[" << currCharIndex << "]" << std::endl;

                sToken = "";
                if (std::isalpha(currChar))
                {
                    while (!std::isspace(currChar))
                    {
                        sToken += currChar;
                        currChar = consume();
                    }

                    if (sToken == "return")
                    {
                        tokens.push_back({ .type = TokenType::_return });
                    }
                    else if (sToken == ";")
                    {
                        tokens.push_back({ .type = TokenType::semicolon });
                    }
                    else
                    {
                        tokens.push_back({ .type = TokenType::identifier });
                    }

                    currChar = consume();
                }
                else if (std::isdigit(currChar))
                {
                    long long integer = charToInt(currChar);
                    currChar = consume();
                    while (std::isdigit(currChar))
                    {
                    	integer *= 10;
						integer += charToInt(currChar);
						currChar = consume();
					}
                    tokens.push_back({ .type = TokenType::integer });
                }
                else if (std::isspace(currChar))
                {
					currChar = consume();
                }
                else
                {
                    if (sToken == ";")
                    {
                        tokens.push_back({ .type = TokenType::semicolon });
                        currChar = consume();
                    }
                }
            }

            return tokens;
        }

    private:
        std::string sourcecode;
        char currChar;
        long long currCharIndex;

        char next(const long long offset = 1)
        {
            return sourcecode[currCharIndex + offset];
        }

        char consume()
        {
            this -> currCharIndex++;
            return sourcecode[currCharIndex];
        }
};

#endif //G_TOKENIZER_HPP
