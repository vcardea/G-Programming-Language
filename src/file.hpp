/**
 * @file    G-Programming-Language/Compiler/file.hpp
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.1
 * @date    2023-15-02
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

/**
 * Class for easily handling read/write
 * operations on files.
 */
class File
{
public:
    /**
     * Default constructor. No args needed
     */
    File() = default;

    /**
     * Sets filepath and filename
     *
     * @param fp filepath
     */
    explicit File(const std::string &fp)
    {
        this->filepath = fp;
        this->setFileName();
    }

    /**
     * Get name of the file currently in use
     *
     * @return filename
     */
    std::string getFileName()
    {
        return this->filename;
    }

    /**
     * Get path of the file currently in use
     *
     * @return filepath
     */
    std::string getFilePath()
    {
        return filepath;
    }

    /**
     * Get the path without filename and extension
     * 
     * @return the path 
     */
    std::string getPath()
    {
        return path;
    }

    /**
     * Checks if the file exists
     *
     * @return exists
     */
    bool exists()
    {
        struct stat buffer
        {
        };
        return (stat(filepath.c_str(), &buffer) == 0);
    }

    /**
     * Reads all lines from the file
     *
     * @return file content
     */
    std::string read()
    {
        std::fstream input(filepath, std::ios::in);
        std::stringstream stream;
        stream << input.rdbuf();
        input.close();
        return stream.str();
    }

    /**
     * Sets filepath and filename from the path
     *
     * @param fp filepath
     */
    void setFilePath(const std::string &fp)
    {
        this->filepath = fp;
        this->setFileName();
    }

    /**
     * Writes on the file
     *
     * @param code to write
     */
    void write(const std::string &code)
    {
        std::stringstream p;
        p << path << filename << ".cpp";
        std::ofstream output(p.str());
        output << code;
        output.close();
    }

private:
    /**
     * Path and filename with extension
     */
    std::string filepath;

    /**
     * Path only, without filename and its extension
     */
    std::string path;

    /**
     * Filename only, without path and extension
     */
    std::string filename;

    /**
     * Sets the filename based on the given filepath
     */
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
            else --i;
        }
        this->path = path.substr(0, i + 1);
        path = path.substr(i + 1, path.length());
        i = path.size() - 1;
        while (path[i] != '.')
        {
            i--;
        }
        this->filename = path.substr(0, i);
    }
};

#endif // G_FILE_HPP