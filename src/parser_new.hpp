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

#include <memory>
#include <sstream>
#include <unordered_map>
#include "./lexer.hpp"

bool symbolTableOk = true;

void symTableError()
{
    symbolTableOk = false;
}

/**
 * Convert token type to string
 *
 * @param type of token
 * @return token name
 */
std::string convertToken(TokenType type)
{
    if (type == TokenType::FALSE)
    {
        return "false";
    }
    else if (type == TokenType::TRUE)
    {
        return "true";
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
    else if (type == TokenType::_EOF)
    {
        return "_EOF";
    }
    return "invalid token";
}

enum class SymbolType
{
    BOOLEAN = (int)TokenType::BOOLEAN_KEYWORD,
    INT,
    FLOAT,
    CHAR,
    STRING,
    UNDEFINED = (int)TokenType::UNDEFINED
};

class Symbol
{
public:
    SymbolType type;
    std::string name;
    std::string value;
    int line;
};

class SymbolTable
{
public:
    void addSymbol(SymbolType type, const std::string name, int line, const std::string value = "NULL")
    {
        auto it = symbols.find(name);
        if (it != symbols.end())
        {
            std::stringstream ss;
            ss << "Variable '" << name << "' already declared on line ";
            ss << it->second.line << ".";
            errorMessage(ss.str());
            symTableError();
        }
        else
        {
            symbols[name] = {type, name, value, line};
        }
    }

    const Symbol &lookupSymbol(const std::string name) const
    {
        auto it = symbols.find(name);
        if (it == symbols.end())
        {
            std::stringstream ss;
            ss << "Variable " << name << " not found.";
            errorMessage(ss.str());
            symTableError();
        }
        return it->second;
    }

    void setValue(const std::string name, const std::string value, const int line)
    {
        auto it = symbols.find(name);
        if (it != symbols.end())
        {
            symbols[name].value = value;
        }
        else
        {
            std::stringstream ss;
            ss << "Undeclared variable '" << name << "' was used ";
            ss << "on line " << line << ".";
            errorMessage(ss.str());
            symTableError();
        }
    }

    void print()
    {
        for (auto it = symbols.begin(); it != symbols.end(); ++it)
        {
            std::cout << "Variable: type:  " << convertToken((TokenType)((int)it->second.type)) << "\n";
            std::cout << "          name:  " << it->second.name << "\n";
            std::cout << "          value: " << it->second.value << "\n";
            std::cout << "          line:  " << it->second.line << "\n";
        }
    }

private:
    std::unordered_map<std::string, Symbol> symbols;
};

class ParseTreeNode
{
public:
    virtual ~ParseTreeNode() = default;
    virtual std::string generateCode(int indentation = 1) const = 0;
    virtual std::string getValue()
    {
        return "";
    }
    virtual void print(int depth = 0) const = 0;
};

class NonTerminalNode : public ParseTreeNode
{
public:
    NonTerminalNode(const std::string &label) : label(label) {}

    void addChild(const std::shared_ptr<ParseTreeNode> &child)
    {
        children.push_back(child);
    }

    std::string generateCode(const int indentation = 1) const override
    {
        std::string indent = std::string(indentation, '\t');
        std::stringstream code;
        if (label == "program")
        {
            code << "#include<iostream>\n";
            code << "int main(int argc, char* argv[])\n{\n";
            for (const auto &child : children)
            {
                code << child->generateCode();
            }
            code << "\treturn 0;\n}";
        }
        else if (label == "statement")
        {
            code << children.at(0)->generateCode();
        }
        else if (label == "declaration")
        {
            // only one child
            code << children.at(0)->generateCode();
            code << ";\n";
        }
        else if (label == "id_declaration")
        {
            code << indent << children.at(0)->getValue() << " " << children.at(1)->getValue();
            // there is an assignment
            if (children.size() == 3)
            {
                code << " = ";
                code << children.at(2)->generateCode();
            }
        }
        else if (label == "assignment")
        {
            // identifier
            code << indent << children.at(0)->generateCode();
            code << " = ";
            // whole expression
            code << children.at(1)->generateCode();
            code << ";\n";
        }
        else if (label == "expression")
        {
            for (const auto &child : children)
            {
                code << child->generateCode();
            }
        }
        else if (label == "primary")
        {
            code << children.at(0)->getValue();
        }
        return code.str();
    }

    std::string getValue()
    {
        std::stringstream ss;
        for (const auto& child : children)
        {
            ss << child->getValue();
        }
        return ss.str();
    }

    std::string getValue(int i)
    {
        return children.at(i)->getValue();
    }

    void print(int depth = 0) const override
    {
        for (int i = 0; i < depth; ++i)
        {
            std::cout << " ";
        }
        std::cout << label << "\n";
        for (const auto &child : children)
        {
            child->print(depth + 1);
        }
    }

private:
    std::string label;
    std::vector<std::shared_ptr<ParseTreeNode>> children;
};

class TerminalNode : public ParseTreeNode
{
public:
    TerminalNode(const std::string &value) : value(value) {}

    std::string generateCode(int indentation = 0) const override
    {
        return this->value;
    }

    std::string getValue()
    {
        return this->value;
    }

    void print(int depth = 0) const override
    {
        for (int i = 0; i < depth; ++i)
        {
            std::cout << " ";
        }
        std::cout << this->value << "\n";
    }

private:
    std::string value;
};

/**
 *
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
     * Get the Symbol Table object
     *
     * @return symbol table
     */
    SymbolTable getSymbolTable()
    {
        return this->st;
    }

    /**
     * Executes syntax analysis
     *
     * @return if analysis was successfull
     */
    std::shared_ptr<ParseTreeNode> parse()
    {
        auto p = parseProgram();
        st.print();
        return p;
    }

    bool isValid()
    {
        return this->valid && symbolTableOk;
    }

private:
    /**
     * Vector of tokens received from the Lexer
     */
    std::vector<Token> tokens;

    /**
     * Token at the position 'index'
     */
    Token currentToken;

    /**
     *
     */
    SymbolTable st;

    /**
     * Index of the current token analysed
     */
    int index;

    /**
     *
     */
    bool valid = true;

    // TODO:REMOVE - FOR DEBUGGING
    void print(int offset = 0)
    {
        std::cout << lookahead(offset).value << "\n";
    }

    /**
     * Unabled constructor
     */
    Parser() {}

    void consume()
    {
        index = std::min(index + 1, (int)tokens.size() - 1);
        currentToken = tokens[index];
    }

    Token lookahead(int offset = 1)
    {
        int size = tokens.size() - 1;
        int i = index + offset;
        if (i > size)
        {
            i = size;
        }
        else if (i < 0)
        {
            i = 0;
        }
        return tokens[i];
    }

    bool checkTokenType(TokenType first, TokenType second = TokenType::UNDEFINED)
    {
        if (second == TokenType::UNDEFINED)
        {
            second = currentToken.type;
        }
        return first == second;
    }

    bool checkTokenType(std::vector<TokenType> first, TokenType second = TokenType::UNDEFINED)
    {
        if (second == TokenType::UNDEFINED)
        {
            second = currentToken.type;
        }
        for (TokenType type : first)
        {
            if (type == second)
            {
                return true;
            }
        }
        return false;
    }

    bool isDataType()
    {
        return checkTokenType(
            {TokenType::BOOLEAN_KEYWORD,
             TokenType::INT_KEYWORD,
             TokenType::FLOAT_KEYWORD,
             TokenType::CHAR_KEYWORD,
             TokenType::STRING_KEYWORD});
    }

    void notValid()
    {
        this->valid = false;
    }

    void expected(Token t, std::string msg)
    {
        std::stringstream ss;
        ss << "Expected " << msg << ". ";
        ss << "Token '" << t.value;
        ss << "' was given at line " << t.line << ".";
        errorMessage(ss.str());
        notValid();
    }

    // void insert(int offset, TokenType tt, std::string name, int line)
    // {
    //     tokens.insert(tokens.begin() + offset, {tt, name, line});
    //     update();
    // }

    void skip(TokenType tt = TokenType::SEMICOLON)
    {
        while (currentToken.type != tt && currentToken.type != TokenType::_EOF)
        {
            consume();
        }
        consume();
    }

    void update()
    {
        currentToken = tokens[index];
    }

    SymbolType getSymbolType(const std::string &type)
    {
        SymbolType st = SymbolType::UNDEFINED;
        if (type == "int")
        {
            st = SymbolType::INT;
        }
        else if (type == "float")
        {
            st = SymbolType::FLOAT;
        }
        else if (type == "char")
        {
            st = SymbolType::CHAR;
        }
        else if (type == "string")
        {
            st = SymbolType::STRING;
        }
        else
        {
            std::stringstream ss;
            ss << "Unknown type " << type << ".";
            errorMessage(ss.str());
            symTableError();
        }
        return st;
    }

    SymbolType getSymbolType(const TokenType type)
    {
        SymbolType st = SymbolType::UNDEFINED;
        if (type == TokenType::INT_KEYWORD)
        {
            st = SymbolType::INT;
        }
        else if (type == TokenType::FLOAT_KEYWORD)
        {
            st = SymbolType::FLOAT;
        }
        else if (type == TokenType::CHAR_KEYWORD)
        {
            st = SymbolType::CHAR;
        }
        else if (type == TokenType::STRING_KEYWORD)
        {
            st = SymbolType::STRING;
        }
        else
        {
            std::stringstream ss;
            ss << "Unknown type " << convertToken(type) << ".";
            errorMessage(ss.str());
            symTableError();
        }
        return st;
    }

    bool isDeclaration()
    {
        return isDataType();
    }

    bool isIdDeclaration()
    {
        bool check = false;
        if (checkTokenType(TokenType::IDENTIFIER, lookahead().type))
        {
            if (checkTokenType({TokenType::ASSIGN, TokenType::SEMICOLON}, lookahead(2).type))
            {
                check = true;
            }
        }
        return check;
    }

    bool isAssignment()
    {
        if (!checkTokenType(TokenType::IDENTIFIER))
        {
            return false;
        }
        return checkTokenType(TokenType::ASSIGN, lookahead().type);
    }

    bool isExpression()
    {
        return checkTokenType({TokenType::TRUE,
                               TokenType::FALSE,
                               TokenType::INT_LITERAL,
                               TokenType::FLOAT_LITERAL,
                               TokenType::CHAR_LITERAL,
                               TokenType::STRING_LITERAL});
    }

    std::shared_ptr<ParseTreeNode> parsePrimary()
    {
        auto node = std::make_shared<TerminalNode>(currentToken.value);
        consume();
        return node;
    }

    std::shared_ptr<ParseTreeNode> parseExpression()
    {
        auto node = std::make_shared<NonTerminalNode>("expression");
        node->addChild(parsePrimary());
        return node;
    }

    std::shared_ptr<ParseTreeNode> parseIdDeclaration()
    {
        auto node = std::make_shared<NonTerminalNode>("id_declaration");
        node->addChild(std::make_shared<TerminalNode>(currentToken.value));
        SymbolType dataType = getSymbolType(currentToken.type);
        consume();
        if (!checkTokenType(TokenType::IDENTIFIER))
        {
            expected(currentToken, "identifier");
            tokens.insert(tokens.begin() + index, {TokenType::IDENTIFIER, "undefined", currentToken.line});
            update();
        }
        node->addChild(std::make_shared<TerminalNode>(currentToken.value));
        std::string name = currentToken.value;
        int line = currentToken.line;
        consume();

        if (isExpression())
        {
            expected(currentToken, "assign symbol '='");
            tokens.insert(tokens.begin() + index, {TokenType::ASSIGN, "undefined", currentToken.line});
            update();
        }

        std::string value = "nullptr";
        if (checkTokenType(TokenType::ASSIGN))
        {
            consume();
            if (!isExpression())
            {
                expected(currentToken, "expression");
                tokens.insert(tokens.begin() + index, {TokenType::NULL_KEYWORD, "undefined", currentToken.line});
                update();
            }
            node->addChild(parseExpression());
            value = currentToken.value;
        }

        if (!checkTokenType(TokenType::SEMICOLON))
        {
            expected(currentToken, "semicolon");
            tokens.insert(tokens.begin() + index, {TokenType::SEMICOLON, "undefined", currentToken.line});
            update();
        }
        consume();

        st.addSymbol(dataType, name, line, value);
        return node;
    }

    std::shared_ptr<ParseTreeNode> parseDeclaration()
    {
        auto node = std::make_shared<NonTerminalNode>("declaration");
        node->addChild(parseIdDeclaration());
        return node;
    }

    std::shared_ptr<ParseTreeNode> parseAssignment()
    {
        auto node = std::make_shared<NonTerminalNode>("assignment");
        node->addChild(std::make_shared<TerminalNode>(currentToken.value));
        std::string id = currentToken.value;
        consume();
        consume();
        if (!isExpression())
        {
            expected(currentToken, "expression");
            tokens.insert(tokens.begin() + index, {TokenType::NULL_KEYWORD, "undefined", currentToken.line});
            update();
        }
        node->addChild(parseExpression());
        
        if (!checkTokenType(TokenType::SEMICOLON))
        {
            expected(currentToken, "semicolon");
            tokens.insert(tokens.begin() + index, {TokenType::SEMICOLON, "undefined", currentToken.line});
            update();
        }
        consume();

        st.setValue(id, node->getValue(1), currentToken.line);
        return node;
    }

    std::shared_ptr<ParseTreeNode> parseStatement()
    {
        std::shared_ptr<NonTerminalNode> node = std::make_shared<NonTerminalNode>("statement");
        if (isDeclaration())
        {
            node->addChild(parseDeclaration());
        }
        else if (isAssignment())
        {
            node->addChild(parseAssignment());
        }
        else
        {
            std::stringstream ss;
            ss << "Unable to determine kind of statement at line " << currentToken.line << ".";
            errorMessage(ss.str());
            // Skips all tokens until next statement or EOF
            while (!checkTokenType({TokenType::SEMICOLON, TokenType::_EOF}))
            {
                consume();
            }
            notValid();
            consume();
        }
        return node;
    }

    std::shared_ptr<ParseTreeNode> parseProgram()
    {
        auto node = std::make_shared<NonTerminalNode>("program");
        while (!checkTokenType(TokenType::_EOF))
        {
            node->addChild(parseStatement());
        }
        return node;
    }
};

class CodeGenerator
{
public:
    CodeGenerator(const SymbolTable &st) : st(st) {}

    std::string generateCode(std::shared_ptr<ParseTreeNode> &parseTree) const
    {
        return parseTree->generateCode();
    }

private:
    const SymbolTable &st;
};

#endif // G_PARSER_HPP