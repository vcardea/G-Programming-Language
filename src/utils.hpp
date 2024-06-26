/**
 * @file    G-Programming-Language/Compiler/utils.hpp
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.1
 * @date    2023-15-02
 *
 * @copyright Copyright (c) 2023
 */

#ifndef G_UTILS_HPP
#define G_UTILS_HPP
#pragma once

#include <iostream>

/**
 * Prints the given error message
 *
 * @param msg message to print
 */
void errorMessage(std::string msg)
{
    std::cout << "[!] " << msg << std::endl;
}

/**
 * Prints a warning message, which doesn't
 * oblige to stop the compilation process
 * 
 * @param msg message to print
 */
void warningMessage(std::string msg)
{
    std::cout << "(!) " << msg << std::endl;
}

/**
 * Checks if a character is '\n'
 *
 * @param c character
 * @return  if it is '\n'
 */
bool isNewLine(char c)
{
    return (c == '\n');
}

/**
 * Checks if a character is skippable
 *
 * @param c character
 * @return  if it is skippable
 */
bool isSkippable(char c)
{
    if (c == ' ')
    {
        return true;
    }

    if (c == '\f')
    {
        return true;
    }

    if (c == '\r')
    {
        return true;
    }

    if (c == '\t')
    {
        return true;
    }

    if (c == '\v')
    {
        return true;
    }

    return false;
}

/**
 * Checks if a character is an arithmetic operator
 *
 * @param c character
 * @return  if it is an arithmetic operator
 */
bool isArithmeticOp(char c)
{
    if (c == '+')
    {
        return true;
    }

    if (c == '-')
    {
        return true;
    }

    if (c == '*')
    {
        return true;
    }

    if (c == '/')
    {
        return true;
    }

    if (c == '%')
    {
        return true;
    }

    return false;
}

/**
 * Checks if a character is a conditional or
 * logical operator
 *
 * @param c character
 * @return  if it is a cond. or log. operator
 */
bool isConditionalLogicalOp(char c)
{
    if (c == '&')
    {
        return true;
    }

    if (c == '|')
    {
        return true;
    }

    if (c == '^')
    {
        return true;
    }

    if (c == '>')
    {
        return true;
    }

    if (c == '<')
    {
        return true;
    }

    if (c == '=')
    {
        return true;
    }

    return false;
}

/**
 * Checks if a character is one of those
 * which should come right after a number
 * literal
 *
 * @param c character
 * @return  if it is one of those characters
 */
bool isNumberLiteralEnd(char c)
{
    // multiple number declaration
    if (c == ',')
    {
        return true;
    }

    // end of number declaration
    if (c == ';')
    {
        return true;
    }

    // arithmetic operation
    if (isArithmeticOp(c))
    {
        return true;
    }

    // conditional or logical operators
    if (isConditionalLogicalOp(c))
    {
        return true;
    }

    // letters
    if (isalpha(c))
    {
        return true;
    }

    // function parameter
    if (c == ')')
    {
        return true;
    }

    // array declaration
    if (c == ']')
    {
        return true;
    }

    return false;
}

/**
 * Look at the (pos + offset)th character of the source code
 *
 * @param src    source code
 * @param pos    index of the character currently pointed
 * @param offset offset of the char to look at
 * @return       character found at position: pos + offset
 */
char lookahead(std::string src, size_t pos, size_t offset = 1)
{
    return src[pos + offset];
}

#endif // G_UTILS_HPP