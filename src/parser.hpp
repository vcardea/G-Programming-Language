/**
 * @file    G-Programming-Language/Compiler/parser.hpp
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.1
 * @date    2023-18-02
 *
 * @copyright Copyright (c) 2023
 */

#ifndef G_PARSER_HPP
#define G_PARSER_HPP
#pragma once

#include <string>
#include <stack>
#include <sstream>
#include "./tokenizer.hpp"

/**
 * Convert token type to string
 *
 * @param type of token
 * @return token name
 */
std::string convert_token(TokenType type)
{
    if (type == TokenType::FALSE)
    {
        return "boolean: false";
    }
    else if (type == TokenType::TRUE)
    {
        return "boolean: true";
    }
    else if (type == TokenType::BOOLEAN_KEYWORD)
    {
        return "boolean";
    }
    else if (type == TokenType::IDENTIFIER)
    {
        return "identifier";
    }
    else if (type == TokenType::INT_KEYWORD)
    {
        return "int";
    }
    else if (type == TokenType::FLOAT_KEYWORD)
    {
        return "float";
    }
    else if (type == TokenType::CHAR_KEYWORD)
    {
        return "char";
    }
    else if (type == TokenType::STRING_KEYWORD)
    {
        return "string";
    }
    else if (type == TokenType::NULL_KEYWORD)
    {
        return "NULL";
    }
    else if (type == TokenType::DOT)
    {
        return ".";
    }
    else if (type == TokenType::COLON)
    {
        return ":";
    }
    else if (type == TokenType::COMMA)
    {
        return ",";
    }
    else if (type == TokenType::SEMICOLON)
    {
        return ";";
    }
    else if (type == TokenType::ASSIGN)
    {
        return "=";
    }
    else if (type == TokenType::EQUAL)
    {
        return "==";
    }
    else if (type == TokenType::NOT_EQUAL)
    {
        return "!=";
    }
    else if (type == TokenType::GREATER_EQUAL)
    {
        return ">=";
    }
    else if (type == TokenType::LOWER_EQUAL)
    {
        return "<=";
    }
    else if (type == TokenType::NOT_LOGIC)
    {
        return "!";
    }
    else if (type == TokenType::AND_CONDITIONAL)
    {
        return "&&";
    }
    else if (type == TokenType::AND_LOGIC)
    {
        return "&";
    }
    else if (type == TokenType::OR_CONDITIONAL)
    {
        return "||";
    }
    else if (type == TokenType::OR_LOGIC)
    {
        return "|";
    }
    else if (type == TokenType::XOR_LOGIC)
    {
        return "^";
    }
    else if (type == TokenType::OPEN_PARENTHESIS)
    {
        return "(";
    }
    else if (type == TokenType::CLOSE_PARENTHESIS)
    {
        return ")";
    }
    else if (type == TokenType::OPEN_SQUARE)
    {
        return "[";
    }
    else if (type == TokenType::CLOSE_SQUARE)
    {
        return "]";
    }
    else if (type == TokenType::OPEN_CURLY)
    {
        return "{";
    }
    else if (type == TokenType::CLOSE_CURLY)
    {
        return "}";
    }
    else if (type == TokenType::PLUS)
    {
        return "+";
    }
    else if (type == TokenType::MINUS)
    {
        return "-";
    }
    else if (type == TokenType::INC)
    {
        return "++";
    }
    else if (type == TokenType::DEC)
    {
        return "--";
    }
    else if (type == TokenType::MULTIPLY)
    {
        return "*";
    }
    else if (type == TokenType::DIVIDE)
    {
        return "/";
    }
    else if (type == TokenType::MODULO)
    {
        return "%";
    }
    else if (type == TokenType::INT_LITERAL)
    {
        return "int literal";
    }
    else if (type == TokenType::FLOAT_LITERAL)
    {
        return "float literal";
    }
    else if (type == TokenType::CHAR_LITERAL)
    {
        return "char literal";
    }
    else if (type == TokenType::STRING_LITERAL)
    {
        return "string literal";
    }
    else if (type == TokenType::EOF_TOKEN)
    {
        return "EOF";
    }
    return "invalid token";
}

/**
 * Provides a method Parser.parse() to
 * syntactically analyze tokens
 */
class Parser
{
public:
    /**
     * Default constructor
     *
     * @param tokens obtained from Tokenizer.lex()
     */
    Parser(std::vector<Token> &tokens) : tokens(tokens), index(-1)
    {
    }

    /**
     * Executes syntax analysis
     *
     * @return if analysis was successfull
     */
    bool parse()
    {
        consumeToken();
        if (currentToken.type != TokenType::EOF_TOKEN)
        {
            bool check = declaration();
            check |= assignment();
            return (parse() && check);
        }
        return true;
    }

private:
    /**
     * Vector of tokens received from the Tokenizer
     * (lexer or lexycal analyser)
     */
    std::vector<Token> tokens;

    /**
     * Token at the position 'index'
     * within the vector
     */
    Token currentToken;

    /**
     * Index of the current token analysed
     */
    size_t index;

    /**
     * Unabled constructor
     */
    Parser() {}

    /**
     * Provides one of the next tokens
     * given an offset (default 1)
     *
     * @return token at position index + offset
     */
    Token lookahead(int offset = 1)
    {
        size_t new_index = index + offset;
        if (new_index >= 0 && new_index < tokens.size())
        {
            return tokens[new_index];
        }
        return {};
    }

    /**
     * Reads the next token
     */
    void consumeToken()
    {
        if (index + 1 < tokens.size())
        {
            index++;
        }
        currentToken = tokens[index];
    }

    /**
     * Reads the previous token
     */
    void restoreToken()
    {
        if (index - 1 >= 0)
        {
            index--;
        }
        currentToken = tokens[index];
    }

    /**
     * Compares two token types
     *
     * @param first token
     * @param second token
     * @return if they are equal
     */
    bool checkTokenType(TokenType first, TokenType second)
    {
        return (first == second);
    }

    /**
     * Compares current token type
     *
     * @param type of token
     * @return if they are equal
     */
    bool checkTokenType(TokenType type)
    {
        return (currentToken.type == type);
    }

    /**
     * Expected token error message
     *
     * @param token name of token
     */
    void expectedErrorMsg(Token token, std::string token_name)
    {
        std::stringstream ss;
        ss << "Expected " << token_name << ". ";
        ss << "Token '" << token.value;
        ss << "' was given at line " << token.line << ".";
        error_message(ss.str());
    }

    /**
     * Checks if a declaration statement is used
     *
     * @return if the statement is a declaration
     */
    bool declaration(bool skip = false)
    {
        if (checkTokenType(TokenType::EOF_TOKEN))
        {
            return true;
        }

        if (!skip)
        {
            bool check = checkTokenType(TokenType::BOOLEAN_KEYWORD);
            check |= checkTokenType(TokenType::INT_KEYWORD);
            check |= checkTokenType(TokenType::FLOAT_KEYWORD);
            check |= checkTokenType(TokenType::CHAR_KEYWORD);
            check |= checkTokenType(TokenType::STRING_KEYWORD);
            check |= checkTokenType(TokenType::USER_DEFINED_TYPE);
            if (!check)
            {
                return false;
            }
            consumeToken();
        }

        if (!checkTokenType(TokenType::IDENTIFIER))
        {
            expectedErrorMsg(currentToken, "identifier");
            return false;
        }

        if (assignment())
        {
            return true;
        }

        consumeToken();
        bool comma = checkTokenType(TokenType::COMMA);
        bool semicolon = checkTokenType(TokenType::SEMICOLON);
        if (!(comma || semicolon))
        {
            expectedErrorMsg(currentToken, "comma or semicolon");
            return false;
        }

        if (comma)
        {
            consumeToken();
            return declaration(true);
        }

        return true;
    }

    /**
     * Checks if an assignment is used
     *
     * @return if the statement is an assignment
     */
    bool assignment()
    {
        if (checkTokenType(TokenType::EOF_TOKEN))
        {
            return true;
        }

        if (!checkTokenType(TokenType::IDENTIFIER))
        {
            expectedErrorMsg(currentToken, "identifier");
            return false;
        }

        if (!checkTokenType(TokenType::ASSIGN, lookahead().type))
        {
            return false;
        }
        consumeToken();
        consumeToken();

        bool check = checkTokenType(TokenType::INT_LITERAL);
        check |= checkTokenType(TokenType::FLOAT_LITERAL);
        check |= checkTokenType(TokenType::CHAR_LITERAL);
        check |= checkTokenType(TokenType::STRING_LITERAL);
        check |= checkTokenType(TokenType::IDENTIFIER);
        check |= checkTokenType(TokenType::USER_DATATYPE_LITERAL);
        if (!check)
        {
            expectedErrorMsg(currentToken, "an expression");
            return false;
        }

        consumeToken();
        bool comma = checkTokenType(TokenType::COMMA);
        bool semicolon = checkTokenType(TokenType::SEMICOLON);
        if (!(comma || semicolon))
        {
            expectedErrorMsg(currentToken, "colon or semicolon");
            return false;
        }

        return true;
    }
};

#endif // G_PARSER_HPP