/**
 * @file    G-Programming-Language/Compiler/main.cpp
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.1
 * @date    2023-15-02
 *
 * @copyright Copyright (c) 2023
 */

/*
 * 1. read source code
 * 2. lexycal analysis
 * 3. syntax analysis (Abstract Syntax Tree)
 * 4. AST transformed a lil bit
 * 5. conversion to ASM/C++
 * 6. write ASM/C++ code to a file
 * 7. compile and execute
 */

#include <iostream>
#include <chrono>
#include "file.hpp"
#include "./parser_new.hpp"

using namespace std::chrono;

/**
 * Checks if a token is valid
 *
 * @param token
 */
void check(Token token)
{
    if (!token.isvalid)
    {
        std::cout << "(token non valido: " << token.value << ")";
    }
}

/**
 * Print all tokens
 *
 * @param tokens list of all tokens
 */
void print(std::vector<Token> &tokens)
{
    for (const auto &token : tokens)
    {
        std::cout << "Tipo: ";

        if (token.type == TokenType::FALSE)
        {
            std::cout << "Valore booleano false ";
            check(token);
        }
        else if (token.type == TokenType::TRUE)
        {
            std::cout << "Valore booleano true ";
            check(token);
        }
        else if (token.type == TokenType::BOOLEAN_KEYWORD)
        {
            std::cout << "Parola chiave 'boolean'";
            check(token);
        }
        else if (token.type == TokenType::IDENTIFIER)
        {
            std::cout << "Identificatore '" << token.value << "' ";
            check(token);
        }
        else if (token.type == TokenType::INT_KEYWORD)
        {
            std::cout << "Parola chiave 'int' ";
            check(token);
        }
        else if (token.type == TokenType::FLOAT_KEYWORD)
        {
            std::cout << "Parola chiave 'float' ";
            check(token);
        }
        else if (token.type == TokenType::CHAR_KEYWORD)
        {
            std::cout << "Parola chiave 'char' ";
            check(token);
        }
        else if (token.type == TokenType::STRING_KEYWORD)
        {
            std::cout << "Parola chiave 'string' ";
            check(token);
        }
        else if (token.type == TokenType::NULL_KEYWORD)
        {
            std::cout << "Parola chiave 'NULL' ";
            check(token);
        }
        else if (token.type == TokenType::USER_DEFINED_TYPE)
        {
            std::cout << "ID del tipo di dato dell'utente: '" << token.value << "' ";
            check(token);
        }
        else if (token.type == TokenType::DEFINE_USER_TYPE_KEYWORD)
        {
            std::cout << "Parola chiave 'define' ";
            check(token);
        }
        else if (token.type == TokenType::DOT)
        {
            std::cout << "Punto fermo '.' ";
            check(token);
        }
        else if (token.type == TokenType::COLON)
        {
            std::cout << "Due punti ':' ";
            check(token);
        }
        else if (token.type == TokenType::COMMA)
        {
            std::cout << "Virgola ',' ";
            check(token);
        }
        else if (token.type == TokenType::SEMICOLON)
        {
            std::cout << "Punto e virgola ';' ";
            check(token);
        }
        else if (token.type == TokenType::ASSIGN)
        {
            std::cout << "Operatore di assegnazione '=' ";
            check(token);
        }
        else if (token.type == TokenType::EQUAL)
        {
            std::cout << "Operatore di uguaglianza '==' ";
            check(token);
        }
        else if (token.type == TokenType::NOT_EQUAL)
        {
            std::cout << "Operatore di disuguaglianza '!=' ";
            check(token);
        }
        else if (token.type == TokenType::GREATER)
        {
            std::cout << "Operatore di maggiore '>' ";
            check(token);
        }
        else if (token.type == TokenType::LOWER)
        {
            std::cout << "Operatore di minore '<' ";
            check(token);
        }
        else if (token.type == TokenType::GREATER_EQUAL)
        {
            std::cout << "Operatore di maggiore o uguale '>=' ";
            check(token);
        }
        else if (token.type == TokenType::LOWER_EQUAL)
        {
            std::cout << "Operatore di minore o uguale '<=' ";
            check(token);
        }
        else if (token.type == TokenType::NOT_LOGIC)
        {
            std::cout << "Operatore logico NOT '!' ";
            check(token);
        }
        else if (token.type == TokenType::AND_CONDITIONAL)
        {
            std::cout << "Operatore condizionale AND '&&' ";
            check(token);
        }
        else if (token.type == TokenType::AND_LOGIC)
        {
            std::cout << "Operatore logico AND '&' ";
            check(token);
        }
        else if (token.type == TokenType::OR_CONDITIONAL)
        {
            std::cout << "Operatore condizionale OR '||' ";
            check(token);
        }
        else if (token.type == TokenType::OR_LOGIC)
        {
            std::cout << "Operatore logico OR '|' ";
            check(token);
        }
        else if (token.type == TokenType::XOR_LOGIC)
        {
            std::cout << "Operatore logico XOR '^' ";
            check(token);
        }
        else if (token.type == TokenType::PLUS)
        {
            std::cout << "Operatore di addizione '+' ";
            check(token);
        }
        else if (token.type == TokenType::MINUS)
        {
            std::cout << "Operatore di sottrazione '-' ";
            check(token);
        }
        else if (token.type == TokenType::INC)
        {
            std::cout << "Operatore di incremento '++' ";
            check(token);
        }
        else if (token.type == TokenType::DEC)
        {
            std::cout << "Operatore di decremento '--' ";
            check(token);
        }
        else if (token.type == TokenType::MULTIPLY)
        {
            std::cout << "Operatore di moltiplicazione '*' ";
            check(token);
        }
        else if (token.type == TokenType::DIVIDE)
        {
            std::cout << "Operatore di divisione '/' ";
            check(token);
        }
        else if (token.type == TokenType::MODULO)
        {
            std::cout << "Operatore modulo '%' ";
            check(token);
        }
        else if (token.type == TokenType::BACKSLASH)
        {
            std::cout << "Carattere backslash '\\' ";
            check(token);
        }
        else if (token.type == TokenType::OPEN_PARENTHESIS)
        {
            std::cout << "Parentesi tonda aperta '(' ";
            check(token);
        }
        else if (token.type == TokenType::CLOSE_PARENTHESIS)
        {
            std::cout << "Parentesi tonda chiusa ')' ";
            check(token);
        }
        else if (token.type == TokenType::OPEN_SQUARE)
        {
            std::cout << "Parentesi quadra aperta '[' ";
            check(token);
        }
        else if (token.type == TokenType::CLOSE_SQUARE)
        {
            std::cout << "Parentesi quadra chiusa ']' ";
            check(token);
        }
        else if (token.type == TokenType::OPEN_CURLY)
        {
            std::cout << "Parentesi graffa aperta '{' ";
            check(token);
        }
        else if (token.type == TokenType::CLOSE_CURLY)
        {
            std::cout << "Parentesi graffa chiusa '}' ";
            check(token);
        }
        else if (token.type == TokenType::INT_LITERAL)
        {
            std::cout << "Numero intero " << token.value << " ";
            check(token);
        }
        else if (token.type == TokenType::FLOAT_LITERAL)
        {
            std::cout << "Numero con virgola mobile " << token.value << " ";
            check(token);
        }
        else if (token.type == TokenType::CHAR_LITERAL)
        {
            std::cout << "Carattere '" << token.value << "' ";
            check(token);
        }
        else if (token.type == TokenType::STRING_LITERAL)
        {
            std::cout << "Stringa costante '" << token.value << "' ";
            check(token);
        }
        else if (token.type == TokenType::SINGLE_LINE_COMMENT)
        {
            std::cout << "Commento su singola linea: '" << token.value << "'.";
        }
        else if (token.type == TokenType::MULTI_LINE_COMMENT)
        {
            std::cout << "Commento su linee multiple: '" << token.value << "'.";
        }
        else if (token.type == TokenType::_EOF)
        {
            std::cout << "End Of File: _EOF token.";
        }
        else
        {
            std::cout << "Token non riconosciuto." << std::endl;
        }

        std::cout << std::endl;
    }
}

/**
 * End of time measure
 */
void end_time_measure(std::chrono::_V2::system_clock::time_point t1)
{
    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << "\n[X] EXECUTION TIME: " << ms_int.count() << " ms\n";
}

/**
 * Exit codes
 */
enum exit_codes
{
    SUCCESSFUL_COMPILATION,
    MISSING_ARGUMENT,
    FILE_DOESNT_EXIST,
    SOURCE_CODE_IS_EMPTY,
    NO_TOKENS_FOUND,
    INVALID_TOKENS,
    INVALID_SYNTAX,
    CODE_NOT_GENERATED
};

int main(int argc, char *argv[])
{
    auto t1 = high_resolution_clock::now();

    // 2 args necessary
    if (argc != 2)
    {
        std::cout << "[!] Usage: " << argv[0] << " <filepath>" << std::endl;
        end_time_measure(t1);
        return MISSING_ARGUMENT;
    }

    std::cout << "[0] Checking if file exists...\n";
    std::string path = argv[1];
    File file(path);
    if (!file.exists())
    {
        std::cerr << "[!] File does not exist.\n";
        end_time_measure(t1);
        return FILE_DOESNT_EXIST;
    }
    std::cout << "[1] File found.\n";

    std::cout << "[2] Reading source code...\n";
    std::string sourcecode = file.read();
    if (sourcecode.empty())
    {
        std::cerr << "[!] File is empty.\n";
        end_time_measure(t1);
        return SOURCE_CODE_IS_EMPTY;
    }
    std::cout << "[3] Source code read.\n";

    std::cout << "[4] Analysing tokens...\n";
    Lexer lexer(sourcecode);
    std::vector<Token> tokens = lexer.lex();
    if (tokens.empty())
    {
        std::cerr << "[!] Error while analyzing tokens. No tokens were found.\n";
        end_time_measure(t1);
        return NO_TOKENS_FOUND;
    }

    // print(tokens);

    if (!lexer.areValid())
    {
        std::cerr << "[!] Error while analyzing tokens. There are invalid tokens.\n";
        end_time_measure(t1);
        return INVALID_TOKENS;
    }
    std::cout << "[5] Tokens analysed successfully.\n";

    std::cout << "[6] Analysing syntax...\n";
    Parser parser(tokens);
    std::shared_ptr<ParseTreeNode> parseTree = parser.parse();
    if (!parser.isValid())
    {
        // std::cerr << "[!] Error while analyzing syntax. Invalid syntax.\n";
        end_time_measure(t1);
        // print(parser.getTokens());
        return INVALID_SYNTAX;
    }
    parseTree->print();
    // print(parser.getTokens());
    std::cout << "[7] Correct syntax. Abstract Syntax Tree built correctly.\n";

    std::cout << "[8] Generating code...\n";
    CodeGenerator cg(parser.getSymbolTable());
    std::string code = cg.generateCode(parseTree);
    if (code == "")
    {
        std::cerr << "[!] Unknown error. Code not generated.\n";
        end_time_measure(t1);
        return CODE_NOT_GENERATED;
    }
    file.write(code);
    std::cout << code << "\n";
    std::cout << "[9] Code generated!\n";
    std::cout << "[#] Compilation terminated successfully.\n";

    end_time_measure(t1);

    return SUCCESSFUL_COMPILATION;
}
