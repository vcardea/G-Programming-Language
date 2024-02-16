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

#endif // G_UTILS_HPP