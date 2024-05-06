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
    Parser(std::vector<Token> &tokens) : tokens(tokens), index(0)
    {
        this->currentToken = tokens[index];
    }

    /**
     * Get the Tokens object
     *
     * @return vector tokens as a result of the parsing
     */
    std::vector<Token> &getTokens()
    {
        return this->tokens;
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
            declaration();
            assignment();
            updateToken();
            consumeToken();
        }
        return isValid;
    }

private:
    /**
     * Vector of tokens received from the Tokenizer
     * (lexer or lexycal analyser).
     * Tokens that are modified throughout the process
     * of parsing
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
     * True if the code is syntactically valid.
     * False otherwise
     */
    bool isValid = true;

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
        int new_index = index + offset;
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
        index = std::min(index + 1, tokens.size() - 1);
        currentToken = tokens[index];
    }

    /**
     * Reads the previous token
     */
    void restoreToken()
    {
        index = std::max(index - 1, 0ULL);
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
        invalidate();
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
     * Sets the isValid boolean to false
     */
    void invalidate()
    {
        this->isValid = false;
    }

    /**
     * Sets the isValid boolean to true
     */
    void validate()
    {
        this->isValid = true;
    }

    /**
     * Checks if a declaration statement is used
     *
     * @return if the statement is a declaration
     */
    bool declaration()
    {
        return (idDeclaration() | userTypeDeclaration() | functionDeclaration());
    }

    /**
     * Checks if an identifier declaration statement is used
     *
     * @return if the statement is an identifier declaration
     */
    bool idDeclaration(bool skip = false)
    {
        if (checkTokenType(TokenType::EOF_TOKEN))
        {
            return false;
        }

        if (!skip)
        {
            if (!isDataType())
            {
                return false;
            }
        }

        int offset = 1 - skip;
        if (!checkTokenType(TokenType::IDENTIFIER, lookahead(offset).type))
        {
            Token t = lookahead();
            expectedErrorMsg(t, "identifier");
            tokens.insert(tokens.begin() + index + 1, {TokenType::IDENTIFIER, "undefined", t.line});
        }

        offset++;
        if (checkTokenType(TokenType::OPEN_PARENTHESIS, lookahead(offset).type))
        {
            return false;
        }

        for (int i = 0; i < 2 - skip; i++)
        {
            consumeToken();
        }

        if (expression(offset - skip))
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
            return idDeclaration(true);
        }

        bool semicolon = checkTokenType(TokenType::SEMICOLON);
        if (!semicolon)
        {
            expectedErrorMsg(currentToken, "comma or semicolon");
            tokens.insert(tokens.begin() + index, {TokenType::SEMICOLON, "undefined", currentToken.line});
            updateToken();
        }

        return true;
    }

    /**
     * Parses a block of code within curly brackets
     *
     * @param endToken token that shows the end of the block
     * @return if there are valid statements
     */
    bool parseBlock()
    {
        while (currentToken.type != TokenType::EOF_TOKEN && currentToken.type != TokenType::CLOSE_CURLY)
        {
            declaration();
            assignment();
            updateToken();
            consumeToken();
        }

        return true;
    }

    /**
     * Checks if a statement is a declaration of a user-defined
     * type of data
     *
     * @return if the statement is a declaration of a user-defined type
     */
    bool userTypeDeclaration()
    {
        if (checkTokenType(TokenType::EOF_TOKEN))
        {
            return false;
        }

        if (!checkTokenType(TokenType::DEFINE_USER_TYPE_KEYWORD))
        {
            return false;
        }
        consumeToken();

        if (!checkTokenType(TokenType::USER_DEFINED_TYPE))
        {
            expectedErrorMsg(currentToken, "data type name");
            tokens.insert(tokens.begin() + index, {TokenType::USER_DEFINED_TYPE, "undefined", currentToken.line});
        }
        consumeToken();

        if (!checkTokenType(TokenType::OPEN_CURLY))
        {
            expectedErrorMsg(currentToken, "opened curly bracket '{'");
            tokens.insert(tokens.begin() + index, {TokenType::OPEN_CURLY, "undefined", currentToken.line});
        }
        consumeToken();

        parseBlock();

        if (!checkTokenType(TokenType::CLOSE_CURLY))
        {
            expectedErrorMsg(currentToken, "closed curly bracket '}'");
            tokens.insert(tokens.begin() + index, {TokenType::CLOSE_CURLY, "undefined", currentToken.line});
        }
        consumeToken();

        if (!checkTokenType(TokenType::SEMICOLON))
        {
            expectedErrorMsg(currentToken, "semicolon");
            tokens.insert(tokens.begin() + index, {TokenType::SEMICOLON, "undefined", currentToken.line});
            updateToken();
        }

        return true;
    }

    /**
     * Parses the definition the list of arguments to pass to the function
     * is valid
     *
     * @return if the list of arguments is syntactically correct
     */
    bool parseFunctionDeclarationArgs()
    {
        if (checkTokenType(TokenType::EOF_TOKEN))
        {
            return false;
        }

        /*
         * ) EOF | !
         * 0 0   0 1
         * 1 0   1 0
         * 0 1   1 0
         */
        size_t args = 0;
        while (!(checkTokenType(TokenType::CLOSE_PARENTHESIS) || checkTokenType(TokenType::OPEN_CURLY) || checkTokenType(TokenType::EOF_TOKEN)))
        {
            if (isDataType())
            {
                consumeToken();
                // type function(type ___)
                if (!checkTokenType(TokenType::IDENTIFIER))
                {
                    expectedErrorMsg(currentToken, "argument's name");
                    tokens.insert(tokens.begin() + index, {TokenType::IDENTIFIER, "undefined", currentToken.line});
                }
                consumeToken();
                args++;
                // type function(type identifier_ [,)]
                if (!checkTokenType(TokenType::COMMA) && !checkTokenType(TokenType::CLOSE_PARENTHESIS))
                {
                    expectedErrorMsg(currentToken, "comma or closed parenthesis");
                    tokens.insert(tokens.begin() + index, {TokenType::COMMA, "undefined", currentToken.line});
                    updateToken();
                }
            }
            // type function(___ identifier)
            else if (checkTokenType(TokenType::IDENTIFIER))
            {
                expectedErrorMsg(currentToken, "data type");
                tokens.insert(tokens.begin() + index, {TokenType::USER_DEFINED_TYPE, "undefined", currentToken.line});
                restoreToken();
            }
            // type function(___ ___,)
            else if (checkTokenType(TokenType::COMMA))
            {
                expectedErrorMsg(currentToken, "data type and argument's name");
                tokens.insert(tokens.begin() + index, {TokenType::IDENTIFIER, "undefined", currentToken.line});
                tokens.insert(tokens.begin() + index, {TokenType::USER_DEFINED_TYPE, "undefined", currentToken.line});
                restoreToken();
            }

            if (!checkTokenType(TokenType::CLOSE_PARENTHESIS))
            {
                consumeToken();
            }
        }

        // type function(type identifier, ___ ___)
        if (checkTokenType(TokenType::CLOSE_PARENTHESIS) && checkTokenType(TokenType::COMMA, tokens[index - 1].type))
        {
            expectedErrorMsg(currentToken, "data type and argument's name");
            tokens.insert(tokens.begin() + index, {TokenType::IDENTIFIER, "undefined", currentToken.line});
            tokens.insert(tokens.begin() + index, {TokenType::USER_DEFINED_TYPE, "undefined", currentToken.line});
            consumeToken();
            consumeToken();
            args++;
        }

        return checkTokenType(TokenType::CLOSE_PARENTHESIS);
    }

    /**
     * Checks if a statement is a function declaration
     *
     * @return if the statement is a function declaration
     */
    bool functionDeclaration()
    {
        if (checkTokenType(TokenType::EOF_TOKEN))
        {
            return false;
        }

        if (!isDataType())
        {
            return false;
        }

        if (!checkTokenType(TokenType::IDENTIFIER, lookahead().type))
        {
            expectedErrorMsg(currentToken, "identifier");
            tokens.insert(tokens.begin() + index, {TokenType::IDENTIFIER, "undefined", currentToken.line});
        }
        consumeToken();
        consumeToken();

        if (!checkTokenType(TokenType::OPEN_PARENTHESIS))
        {
            expectedErrorMsg(currentToken, "open parenthesis");
            tokens.insert(tokens.begin() + index, {TokenType::OPEN_PARENTHESIS, "undefined", currentToken.line});
        }
        consumeToken();

        if (!parseFunctionDeclarationArgs())
        {
            return false;
        }
        consumeToken();

        if (!checkTokenType(TokenType::OPEN_CURLY))
        {
            expectedErrorMsg(currentToken, "opened curly bracket");
            tokens.insert(tokens.begin() + index, {TokenType::OPEN_CURLY, "undefined", currentToken.line});
        }
        consumeToken();

        parseBlock();

        if (!checkTokenType(TokenType::CLOSE_CURLY))
        {
            expectedErrorMsg(currentToken, "closed curly bracket");
            tokens.insert(tokens.begin() + index, {TokenType::CLOSE_CURLY, "undefined", currentToken.line});
            updateToken();
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
            return false;
        }

        if (!checkTokenType(TokenType::IDENTIFIER))
        {
            return false;
        }

        if (checkTokenType(TokenType::OPEN_PARENTHESIS, lookahead().type))
        {
            return false;
        }

        if (expression(1))
        {
            Token t = lookahead();
            expectedErrorMsg(t, "assign token '='");
            tokens.insert(tokens.begin() + index + 1, {TokenType::ASSIGN, "undefined", t.line});
        }

        bool isAssigning = false;
        if (checkTokenType(TokenType::ASSIGN, lookahead().type))
        {
            isAssigning = true;
            consumeToken();
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

        if (!isAssigning)
        {
            consumeToken();
        }

        bool semicolon = checkTokenType(TokenType::SEMICOLON);
        if (!semicolon)
        {
            expectedErrorMsg(currentToken, "comma or semicolon");
            tokens.insert(tokens.begin() + index, {TokenType::SEMICOLON, "undefined", currentToken.line});
            updateToken();
        }

        return true;
    }

    /**
     * Parse an expression
     *
     * @return if there is an expression
     */
    bool expression(int offset = 0)
    {
        bool check = false;
        TokenType tt = lookahead(offset).type;
        check |= checkTokenType(TokenType::INT_LITERAL, tt);
        check |= checkTokenType(TokenType::FLOAT_LITERAL, tt);
        check |= checkTokenType(TokenType::CHAR_LITERAL, tt);
        check |= checkTokenType(TokenType::STRING_LITERAL, tt);
        check |= checkTokenType(TokenType::USER_DATATYPE_LITERAL, tt);
        // check |= checkTokenType(TokenType::IDENTIFIER, tt);
        return check;
    }
};

#endif // G_PARSER_HPP