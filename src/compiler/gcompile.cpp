/**
 * @file    G-Programming-Language/Compiler/main.cpp
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.1
 * @date    2023-
 *
 * @copyright Copyright (c) 2023
 */

/*
 * 1. read source code
 * 2. lexycal analysis
 * 3. syntax analysis (Abstract Syntax Tree)
 * 4. AST trasformed a lil bit
 * 5. conversion to ASM/C
 * 6. write ASM/C code to a file
 * 7. interpret/compile and execute
 */

#include <iostream>
#include "file.hpp"
#include "tokenizer.hpp"

enum exit_codes
{
    SUCCESSFUL_COMPILATION,
    MISSING_ARGUMENT,
    FILE_DOESNT_EXIST,
    SOURCE_CODE_IS_EMPTY,
    NO_TOKENS_FOUND
};

int main(int argc, char *argv[])
{
    if (argc != 2) // 2 args necessary
    {
        std::cout << "[!] Usage: " << argv[0] << " <filepath> " << std::endl;
        return MISSING_ARGUMENT;
    }

    std::string path = argv[1];
    File file(path);

    std::cout << "[0] Checking if file exists..." << std::endl;
    if (!file.exists())
    {
        std::cerr << "[!] File does not exist." << std::endl;
        return FILE_DOESNT_EXIST;
    }
    std::cout << "[1] File found." << std::endl;

    // (1) Reading from source code
    std::string sourcecode = file.read();

    std::cout << "[2] Reading source code..." << std::endl;
    // (2) Lexycal analysis
    if (sourcecode.empty())
    {
        std::cerr << "[!] File is empty." << std::endl;
        return SOURCE_CODE_IS_EMPTY;
    }
    std::cout << "[3] Source code read." << std::endl;

    std::cout << "[4] Analysing tokens..." << std::endl;
    Tokenizer tokenizer(sourcecode);
    std::vector<Token> tokens = tokenizer.lex();
    if (tokens.empty())
    {
        std::cerr << "[!] Error while analyzing tokens. No tokens were found." << std::endl;
        return NO_TOKENS_FOUND;
    }
    std::cout << "[5] Tokens analysed successfully." << std::endl;

    // Stampa i token riconosciuti
    for (const auto &token : tokens)
    {
        std::cout << "Tipo: ";
        switch (token.type)
        {
        case TokenType::FALSE:
            std::cout << "Valore booleano false";
            break;
        case TokenType::TRUE:
            std::cout << "Valore booleano true";
            break;
        case TokenType::IDENTIFIER:
            std::cout << "Identificatore: " << token.value;
            break;
        case TokenType::INT_KEYWORD:
            std::cout << "Parola chiave 'int'";
            break;
        case TokenType::CHAR_KEYWORD:
            std::cout << "Parola chiave 'char'";
            break;
        case TokenType::ASSIGN:
            std::cout << "Operatore di assegnazione '='";
            break;
        case TokenType::EQUAL:
            std::cout << "Operatore di uguaglianza '=='";
            break;
        case TokenType::NOT_EQUAL:
            std::cout << "Operatore di disuguaglianza '!='";
            break;
        case TokenType::GREATER:
            std::cout << "Operatore di maggiore '>";
            break;
        case TokenType::LOWER:
            std::cout << "Operatore di minore '<'";
            break;
        case TokenType::GREATER_EQUAL:
            std::cout << "Operatore di maggiore o uguale '>='";
            break;
        case TokenType::LOWER_EQUAL:
            std::cout << "Operatore di minore o uguale '<='";
            break;
        case TokenType::PLUS:
            std::cout << "Operatore di addizione '+'";
            break;
        case TokenType::MINUS:
            std::cout << "Operatore di sottrazione '-'";
            break;
        case TokenType::MULTIPLY:
            std::cout << "Operatore di moltiplicazione '*'";
            break;
        case TokenType::DIVIDE:
            std::cout << "Operatore di divisione '/'";
            break;
        case TokenType::MODULO:
            std::cout << "Operatore modulo '%'";
            break;
        case TokenType::INT_LITERAL:
            std::cout << "Letterale intero: " << token.value;
            break;
        case TokenType::CHAR_LITERAL:
            std::cout << "Letterale carattere: " << token.value;
            break;
        case TokenType::SEMICOLON:
            std::cout << "Punto e virgola ';'";
            break;
        default:
            std::cout << "Token non riconosciuto." << std::endl;
        }

        std::cout << std::endl;
    }

    // std::cout << "[6] Building the Abstract Syntax Tree..." << std::endl;
    // (3) Abstract Syntax Tree
    /* TODO: AST stuff
     * vector<SyntaxToken> ast = AST.build();
     */
    // std::cout << "[7] AST built successfully." << std::endl;

    std::cout << "Compilation terminated successfully" << std::endl;

    return SUCCESSFUL_COMPILATION;
}
