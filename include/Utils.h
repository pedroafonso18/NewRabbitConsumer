#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <chrono>

class Utils {
public:
    Utils() = delete;
    static std::chrono::system_clock::time_point getTimestamp(std::string timestamp);
};

#endif //UTILS_H
