/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "logger.hpp"

// Custom exceptions
#if (CHECK_CORRECTION)

#include <stdexcept>
#include <string>


// Any error of loading
class LoadException : public std::exception {
 protected:
    const char* message;

 public:
    LoadException() : LoadException("Unknown error\n") {}
    LoadException(const std::string _message) : message(_message.std::string::c_str()) {
        logImportant(message);
    }
    const char* what() const noexcept override {
        return message;
    };
};

// Error of loading library
class LibararyLoadException : LoadException {
 public:
    LibararyLoadException(const std::string _library = "")
        : LoadException("Error with loading library: " + _library + '\n') {}
    const char* what() const noexcept override {
        return message;
    }
};

// Error with loading data
class DataLoadException : LoadException {
 public:
    DataLoadException(const std::string _dataType = "")
        : LoadException("Error with load file: " + _dataType + '\n') {}
    const char* what() const noexcept override {
        return message;
    }
};

#endif  // (CHECK_CORRECTION)
