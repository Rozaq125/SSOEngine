#ifndef SSO_LOGGER_H
#define SSO_LOGGER_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

namespace SSO {
    class Logger {
    public:
        enum class Level { INFO, WARNING, ERROR, SUCCESS };

        /**
         * @brief Logs a message to the console with color and timestamp.
         */
static void Log(Level level, const std::string& message) {
            // Get current time
            auto now = std::chrono::system_clock::now();
            auto timeT = std::chrono::system_clock::to_time_t(now);
            
            // Use localtime_s (Windows) or localtime (Cross-platform)
            // For simplicity and headers, we use localtime:
            std::tm* localTime = std::localtime(&timeT);

            // Print timestamp
            std::cout << "[" << std::put_time(localTime, "%H:%M:%S") << "] ";

            // Print level with ANSI colors
            switch (level) {
                case Level::INFO:    std::cout << "\033[36m[INFO] "; break;    // Cyan
                case Level::WARNING: std::cout << "\033[33m[WARNING] "; break; // Yellow
                case Level::ERROR:   std::cout << "\033[31m[ERROR] "; break;   // Red
                case Level::SUCCESS: std::cout << "\033[32m[SUCCESS] "; break; // Green
            }

            // Print message and reset color
            std::cout << message << "\033[0m" << std::endl;
        }
    };
}

#endif