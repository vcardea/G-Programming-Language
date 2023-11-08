/**
 * @file    main.cpp - G-Programming-Language/Compiler/Main file 
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.1
 * @date    2023-11-08
 * 
 * @copyright Copyright (c) 2023
 */

#include <iostream>
#include "file.hpp"
#include "tokenizer.hpp"

int main(int argc, char* argv[])
{
    if (argc != 1) // 2
    {
        std::cout << "[!] Usage: " << argv[0] << " <filepath> " << std::endl;
        return -1;
    }
    
    /*
     * 1. read source code
     * 2. lexycal analysis
     * 3. syntax analysis (Abstract Syntax Tree)
     * 4. AST trasformed a lil bit
     * 5. conversion to ASM/C
     * 6. write ASM/C code to a file
     * 7. interpret/compile and execute
    */

    //std::string path = argv[1];
    std::string path = "../../easy.gio";
    File file(path);

    std::cout << "[0] Checking if file exists..." << std::endl;
    if (!file.exists())
    {
        std::cerr << "[!] File does not exist." << std::endl;
        return -2;
    }
    std::cout << "[1] File found." << std::endl;

    // (1) Reading from source code
    std::string sourcecode = file.read();

    std::cout << "[2] Reading source code..." << std::endl;
    // (2) Lexycal analysis
    if (sourcecode.empty())
    {
        std::cerr << "[!] File is empty." << std::endl;
        return -3;
    }
    std::cout << "[3] Source code read." << std::endl;

    std::cout << "[4] Analysing tokens..." << std::endl;
    Tokenizer tokenizer(sourcecode);
    std::vector<Token> tokens = tokenizer.lex();
    std::cout << "[5] Tokens analysed successfully." << std::endl;

    std::cout << "[6] Building the Abstract Syntax Tree..." << std::endl;
    // (3) Abstract Syntax Tree
    /* TODO: AST stuff
     * vector<SyntaxToken> ast = AST.build();
    */
    std::cout << "[7] AST built successfully." << std::endl;

    return 0;
}
