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
 * 
 * CONVENTIONS
 * While defining methods for correcting syntax,
 * which are booleans, I'm going to follow a few rules.
 * 1) Functions return true if a statement is syntactically
 * correct, false if they are incorrect or simply don't match
 * the expression it was tested on
 * 2) In order to understand if a statement is syntactically
 * incorrect (giving out the correct hints for correcting it),
 * the method must first check that the first N tokens
 * (depending on the grammar) correspond to the expression
 * is being tested. In doing so, it can be assured that the user was
 * trying to explicitly use that kind of statement and nothing else.
 * After checking such tokens, any unexpected token must generate
 * an error message which has to be communicated to the user.
 * In order to go on with the syntax analysis, some recovery 
 */
class Parser
{
public:
    /**
     * Default constructor
     *
     * @param tokens obtained from Tokenizer.lex()
     */
    Parser(std::vector<Token> &tokens) : originalTokens(tokens), tokens(tokens), index(0)
    {
        this->currentToken = tokens[index];
    }

    /**
     * Executes syntax analysis
     *
     * @return if analysis was successfull
     */
    bool parse()
    {
        while (currentToken.type != TokenType::EOF_TOKEN)
        {
            assignment();
            consumeToken();
        }
        return checkTokens();
    }

private:
    /**
     * Vector of tokens received from the Tokenizer
     * (lexer or lexycal analyser).
     * These are the original tokens received by the
     * Tokenizer. These are important for comparing
     * them to the vector of tokens (Parser.tokens)
     * obtained at the end of the parsing. If they
     * don't match, some syntax errors must have
     * occurred.
     */
    const std::vector<Token> originalTokens;

    /**
     * Vector of tokens received from the Tokenizer
     * (lexer or lexycal analyser).
     * Tokens that are modified throughout the process
     * of parsing. If these tokens don't match the ones
     * in Parser.originalTokens, then some syntax errors
     * have occurred.
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
     * Checks if the original vector of tokens received from
     * the lexycal analysis (Tokenizer.lex()) matches the ones
     * obtained from the parsing. If they don't, some syntax
     * errors have occurred.
     *
     * @return if all tokens match
     */
    bool checkTokens()
    {
        for (int i = 0; i < originalTokens.size(); ++i)
        {
            if (originalTokens[i].type != tokens[i].type)
            {
                return false;
            }
        }
        return true;
    }

    /**
     * Provides one of the next tokens
     * given an offset (default 1)
     *
     * @return token at position index + offset
     */
    Token lookahead(size_t offset = 1)
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
     * Update current token's value after
     * an insertion due to a syntax error
     */
    void updateToken()
    {
        this->currentToken = tokens[index];
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
     * Checks if the type of token is a data type (built-in, such as
     * int, float, char or string, or user-defined)
     *
     * @param tt type of token. Refers to the current token's if not specified
     * @return if it is a data type
     */
    bool isDataType(TokenType tt = TokenType::UNDEFINED)
    {
        if (tt == TokenType::UNDEFINED)
        {
            tt = currentToken.type;
        }
        bool check = false;
        check |= checkTokenType(TokenType::BOOLEAN_KEYWORD);
        check |= checkTokenType(TokenType::INT_KEYWORD);
        check |= checkTokenType(TokenType::FLOAT_KEYWORD);
        check |= checkTokenType(TokenType::CHAR_KEYWORD);
        check |= checkTokenType(TokenType::STRING_KEYWORD);
        check |= checkTokenType(TokenType::USER_DEFINED_TYPE);
        return check;
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
            if (!isDataType())
            {
                return false;
            }
            consumeToken();
        }

        if (!checkTokenType(TokenType::IDENTIFIER))
        {
            expectedErrorMsg(currentToken, "identifier");
            tokens.insert(tokens.begin() + index, {TokenType::IDENTIFIER, "undefined", currentToken.line});
        }
        consumeToken();

        if (expression())
        {
            expectedErrorMsg(currentToken, "assign token '='");
            tokens.insert(tokens.begin() + index, {TokenType::ASSIGN, "undefined", currentToken.line});
            updateToken();
        }

        if (checkTokenType(TokenType::ASSIGN))
        {
            consumeToken();
            if (!expression())
            {
                expectedErrorMsg(currentToken, "an expression");
                tokens.insert(tokens.begin() + index, {TokenType::USER_DATATYPE_LITERAL, "undefined", currentToken.line});
            }
            // TODO: You should skip all tokens that are part of the expression
            consumeToken();
        }

        bool comma = checkTokenType(TokenType::COMMA);
        if (comma)
        {
            consumeToken();
            return declaration(true);
        }

        bool semicolon = checkTokenType(TokenType::SEMICOLON);
        if (!semicolon)
        {
            expectedErrorMsg(currentToken, "comma or semicolon");
            tokens.insert(tokens.begin() + index, {TokenType::SEMICOLON, "undefined", currentToken.line});
            consumeToken();
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
            return false;
        }

        if (expression(1))
        {
            Token t = lookahead(1);
            expectedErrorMsg(t, "assign token '='");
            tokens.insert(tokens.begin() + index, {TokenType::ASSIGN, "undefined", t.line});
        }

        if (checkTokenType(TokenType::ASSIGN))
        {
            consumeToken();
            if (!expression())
            {
                expectedErrorMsg(currentToken, "an expression");
                tokens.insert(tokens.begin() + index, {TokenType::USER_DATATYPE_LITERAL, "undefined", currentToken.line});
            }
            // TODO: You should skip all tokens that are part of the expression
            consumeToken();
        }

        bool comma = checkTokenType(TokenType::COMMA);
        if (comma)
        {
            consumeToken();
            return assignment();
        }

        bool semicolon = checkTokenType(TokenType::SEMICOLON);
        if (!semicolon)
        {
            expectedErrorMsg(currentToken, "comma or semicolon");
            tokens.insert(tokens.begin() + index, {TokenType::SEMICOLON, "undefined", currentToken.line});
            consumeToken();
        }
        
        return true;
    }

    /**
     * Parse an expression
     *
     * @return if there is an expression
     */
    bool expression(size_t offset = 0)
    {
        bool check = false;
        TokenType tt = lookahead(offset).type;
        check |= checkTokenType(TokenType::INT_LITERAL, tt);
        check |= checkTokenType(TokenType::FLOAT_LITERAL, tt);
        check |= checkTokenType(TokenType::CHAR_LITERAL, tt);
        check |= checkTokenType(TokenType::STRING_LITERAL, tt);
        check |= checkTokenType(TokenType::USER_DATATYPE_LITERAL, tt);
        return check;
    }
};

#endif // G_PARSER_HPP