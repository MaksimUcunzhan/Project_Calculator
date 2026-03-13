#pragma once
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include "Exceptions.h"


class Logger {
public:
    explicit Logger(const std::string& filename)
        : filename_(filename), active_(false)
    {
        file_.open(filename_, std::ios::out | std::ios::app);
        if (!file_.is_open()) {
            throw FileIOException(filename_);
        }
        active_ = true;
        write("[SESSION START]");
    }

    ~Logger() {
        if (active_) {
            try {
                write("[SESSION END]");
                file_.close();
            } catch (...) {}
        }
    }
};