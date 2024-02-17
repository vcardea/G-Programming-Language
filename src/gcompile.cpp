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
 * 4. AST transformed a lil bit
 * 5. conversion to ASM/C
 * 6. write ASM/C code to a file
 * 7. interpret/compile and execute
 */

#include <iostream>
#include "file.hpp"
#include "tokenizer.hpp"

void check(Token token)
{
    if (!token.isvalid)
    {
        std::cout << "(token non valido: " << token.value << ")";
    }
}

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

    // for (const auto &token : tokens)
    // {
    //     std::cout << "Tipo: ";

    //     if (token.type == TokenType::FALSE)
    //     {
    //         std::cout << "Valore booleano false ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::TRUE)
    //     {
    //         std::cout << "Valore booleano true ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::IDENTIFIER)
    //     {
    //         std::cout << "Identificatore '" << token.value << "' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::INT_KEYWORD)
    //     {
    //         std::cout << "Parola chiave 'int' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::FLOAT_KEYWORD)
    //     {
    //         std::cout << "Parola chiave 'float' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::CHAR_KEYWORD)
    //     {
    //         std::cout << "Parola chiave 'char' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::DOT)
    //     {
    //         std::cout << "Punto fermo '.' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::COLON)
    //     {
    //         std::cout << "Due punti ':' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::COMMA)
    //     {
    //         std::cout << "Virgola ',' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::SEMICOLON)
    //     {
    //         std::cout << "Punto e virgola ';' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::ASSIGN)
    //     {
    //         std::cout << "Operatore di assegnazione '=' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::EQUAL)
    //     {
    //         std::cout << "Operatore di uguaglianza '==' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::NOT_EQUAL)
    //     {
    //         std::cout << "Operatore di disuguaglianza '!=' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::GREATER)
    //     {
    //         std::cout << "Operatore di maggiore '>' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::LOWER)
    //     {
    //         std::cout << "Operatore di minore '<' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::GREATER_EQUAL)
    //     {
    //         std::cout << "Operatore di maggiore o uguale '>=' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::LOWER_EQUAL)
    //     {
    //         std::cout << "Operatore di minore o uguale '<=' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::NOT_LOGIC)
    //     {
    //         std::cout << "Operatore logico NOT '!' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::AND_CONDITIONAL)
    //     {
    //         std::cout << "Operatore condizionale AND '&&' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::AND_LOGIC)
    //     {
    //         std::cout << "Operatore logico AND '&' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::OR_CONDITIONAL)
    //     {
    //         std::cout << "Operatore condizionale OR '||' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::OR_LOGIC)
    //     {
    //         std::cout << "Operatore logico OR '|' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::XOR_LOGIC)
    //     {
    //         std::cout << "Operatore logico XOR '^' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::PLUS)
    //     {
    //         std::cout << "Operatore di addizione '+' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::MINUS)
    //     {
    //         std::cout << "Operatore di sottrazione '-' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::INC)
    //     {
    //         std::cout << "Operatore di incremento '++' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::DEC)
    //     {
    //         std::cout << "Operatore di decremento '--' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::MULTIPLY)
    //     {
    //         std::cout << "Operatore di moltiplicazione '*' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::DIVIDE)
    //     {
    //         std::cout << "Operatore di divisione '/' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::MODULO)
    //     {
    //         std::cout << "Operatore modulo '%' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::BACKSLASH)
    //     {
    //         std::cout << "Carattere backslash '\\' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::OPEN_PARENTHESIS)
    //     {
    //         std::cout << "Parentesi tonda aperta '(' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::CLOSE_PARENTHESIS)
    //     {
    //         std::cout << "Parentesi tonda chiusa ')' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::OPEN_SQUARE)
    //     {
    //         std::cout << "Parentesi quadra aperta '[' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::CLOSE_SQUARE)
    //     {
    //         std::cout << "Parentesi quadra chiusa ']' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::OPEN_CURLY)
    //     {
    //         std::cout << "Parentesi graffa aperta '{' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::CLOSE_CURLY)
    //     {
    //         std::cout << "Parentesi graffa chiusa '}' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::INT_LITERAL)
    //     {
    //         std::cout << "Numero intero " << token.value << " ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::FLOAT_LITERAL)
    //     {
    //         std::cout << "Numero con virgola mobile " << token.value << " ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::CHAR_LITERAL)
    //     {
    //         std::cout << "Carattere '" << token.value << "' ";
    //         check(token);
    //     }
    //     else if (token.type == TokenType::STRING_LITERAL)
    //     {
    //         std::cout << "Stringa costante '" << token.value << "' ";
    //         check(token);
    //     }
    //     else
    //     {
    //         std::cout << "Token non riconosciuto." << std::endl;
    //     }

    //     std::cout << std::endl;
    // }

    // std::cout << "[6] Building the Abstract Syntax Tree..." << std::endl;
    // (3) Abstract Syntax Tree
    /* TODO: AST stuff
     * vector<SyntaxToken> ast = AST.build();
     */
    // std::cout << "[7] AST built successfully." << std::endl;

    std::cout << "Compilation terminated successfully" << std::endl;

    return SUCCESSFUL_COMPILATION;
}
