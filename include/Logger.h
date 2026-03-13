#pragma once
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include "Exceptions.h"


class Logger {
private:
    std::string   filename_;
    std::ofstream file_;
    bool          active_;

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

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    Logger(Logger&& other) noexcept
        : filename_(std::move(other.filename_)),
          file_(std::move(other.file_)),
          active_(other.active_)
    {
        other.active_ = false;
    }

    Logger& operator=(Logger&& other) noexcept {
        if (this != &other) {
            if (active_) { try { write("[SESSION END]"); file_.close(); } catch (...) {} }
            filename_ = std::move(other.filename_);
            file_ = std::move(other.file_);
            active_ = other.active_;
            other.active_ = false;
        }
        return *this;
    }

    void write(const std::string& message) {
        if (!active_ || !file_.is_open()) return;

        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);
        std::tm tm_buf{};
#ifdef _WIN32
        localtime_s(&tm_buf, &time_t_now);
#else
        localtime_r(&time_t_now, &tm_buf);
#endif
        char ts[20];
        std::strftime(ts, sizeof(ts), "%H:%M:%S", &tm_buf);

        file_ << "[" << ts << "] " << message << "\n";
        file_.flush();
    }

    bool isOpen() const { return active_; }
};