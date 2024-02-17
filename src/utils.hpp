/**
 * @file    G-Programming-Language/Compiler/utils.hpp
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.1
 * @date    2023-
 *
 * @copyright Copyright (c) 2023
 */

#ifndef G_UTILS_HPP
#define G_UTILS_HPP
#pragma once

#include <iostream>

void error_message(std::string msg)
{
    std::cout << "[!] " << msg << std::endl;
}

bool isskippable(char c)
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

bool isnewline(char c)
{
    return (c == '\n');
}

bool is_aritmethic_op(char c)
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

bool is_conditional_logical_op(char c)
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

bool is_number_literal_end(char c)
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

    // aritmethic operation
    if (is_aritmethic_op(c))
    {
        return true;
    }

    // conditional or logical operators
    if (is_conditional_logical_op(c))
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