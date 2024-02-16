/**
 * @file    file.hpp - G-Programming-Language/Compiler/file.hpp
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.1
 * @date    2023-
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
     * @param str to write
     */
    void write(const std::string &str)
    {
        // TODO: writing on file
    }

private:
    std::string filepath;
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
            --i;
        }
        this->filename = path.substr(i, path.length());
    }
};

#endif // G_FILE_HPP