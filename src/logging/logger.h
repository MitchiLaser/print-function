/*
 * logger.h
 *
 *  simple logging directives based on a given log level
 *  compile with -DLOG_LEVEL=LOG_DEBUG to enable debug logging
 *  or choose any other level
 *  */

#pragma once
#include <fstream>
#include <string>

// every logging level contains the levels below it
#define LOG_DEBUG 1
#define LOG_INFO 2
#define LOG_WARNING 3
#define LOG_ERROR 4
#define LOG_NOLOG 5

// if there is no LOG level defined, set it to LOG_NOLOG
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_NOLOG
#endif

template <typename T> class logger {
private:
    std::ofstream logfile;
    void write(const std::string level, const T& message);
    std::string name;
public:
    logger(const std::string& filename, std::string component_name = "") {
        logfile.open(filename, std::ios::app); // append to file
        name = component_name;
    }
    ~logger() {
        if (logfile.is_open()) {
            logfile.close();
        }
    }

    void debug(const T& message) {
#if LOG_LEVEL <= LOG_DEBUG
        write("[DEBUG] ", message);
#endif
    }

    void info(const T& message) {
#if LOG_LEVEL <= LOG_INFO
        write("[INFO] ", message);
#endif
    }

    void warning(const T& message) {
#if LOG_LEVEL <= LOG_WARNING
        write("[WARNING] ", message);
#endif
    }

    void error(const T& message) {
#if LOG_LEVEL <= LOG_ERROR
        write("[ERROR] ", message);
#endif
    }
};

template <typename T>
void logger<T>::write(const std::string level, const T& message) {
    logfile << level <<  name << ": " << message << std::endl;
}
