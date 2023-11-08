/**
 * @file    file.hpp - G-Programming-Language/Compiler/Files management 
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.1
 * @date    2023-11-08
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef G_FILE_HPP
#define G_FILE_HPP

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <sys/stat.h>

class File
{
    public:
        File() = default;

        explicit File(const std::string& fp)
        {
            this -> filepath = fp;
            this -> setFileName();
        }

        std::string getFileName()
        {
            return this -> filename;
        }

        std::string getFilePath()
        {
            return filepath;
        }

        bool exists()
        {
            struct stat buffer{};
            return (stat(filepath.c_str(), &buffer) == 0);
        }

        std::string read()
        {
            std::fstream input(filepath, std::ios::in);
            std::stringstream stream;
            stream << input.rdbuf();
            input.close();
            return stream.str();
        }

        void setFilePath(const std::string& fp)
        {
            this -> filepath = fp;
            this -> setFileName();
        }

        void write(const std::string& code)
        {
            // TODO: writing on file
        }

    private:
        std::string filepath;
        std::string filename;

        void setFileName()
        {
            std::string path = filepath;
            bool end = false;
            size_t i = path.length() - 1;
            while (i && !end)
            {
                if (path[i] == '/' || path[i] == '\\')
                {
                    end = true;
                }
                --i;
            }
            this -> filename = path.substr(path.length() + 2, path.length());
        }
};

#endif // G_FILE_HPP