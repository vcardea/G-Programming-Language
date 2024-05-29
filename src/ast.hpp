/**
 * @file    G-Programming-Language/Compiler/ast.hpp
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.1
 * @date    2023-15-05
 *
 * @copyright Copyright (c) 2023
 */
#ifndef G_AST_HPP
#define G_AST_HPP
#pragma once

#include <memory>
#include "./parser.hpp"

class ParseTreeNode {
public:
    virtual ~ParseTreeNode() = default;
    virtual void print(int depth = 0) const = 0;
};

class NonTerminalNode : ParseTreeNode {
public:
    NonTerminalNode(std::string& label) : label(label) {}

    void print(int depth = 0) const override {
        for (int i = 0; i < depth; ++i) {
            std::cout << " ";
        }
        std::cout << label << "\n";
        for (const auto& child : children) {
            child->print(depth + 1);
        }
    }

private:
    std::string label;
    std::vector<std::shared_ptr<ParseTreeNode>> children;
};

class TerminalNode : ParseTreeNode {
public:
    TerminalNode(std::string& value) : value(value) {}

    void print(int depth = 0) const override {
        for (int i = 0; i < depth; ++i) {
            std::cout << " ";
        }
        std::cout << this->value << "\n";
    }

private:
    std::string value;
};



#endif // G_AST_HPP