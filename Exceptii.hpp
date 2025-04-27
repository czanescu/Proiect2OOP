#ifndef EXCEPTII_H
#define EXCEPTII_H

#include <exception>
#include <string>
#include <iostream>
#include <fstream>

// Clasa de bază pentru toate excepțiile personalizate
class BaseException : public std::exception {
protected:
    std::string m_message;
public:
    explicit BaseException(const std::string& msg);
    const char* what() const noexcept;
};

// Excepție pentru fișiere
class FileException : public BaseException {
public:
    explicit FileException(const std::string& filename);
};

// Excepție pentru configurare
class ConfigException : public BaseException {
public:
    explicit ConfigException(int frameRate, int width, int height);
};

// Excepție pentru indecși
class IndexOutOfRangeException : public BaseException 
{
public:
    explicit IndexOutOfRangeException(int index, int size);
};

#endif