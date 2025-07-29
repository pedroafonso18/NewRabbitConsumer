#include "../include/Utils.h"
#include <chrono>
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

std::chrono::system_clock::time_point Utils::getTimestamp(std::string timestamp) {
    auto utc_timestamp = std::chrono::system_clock::from_time_t(
    std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now()));

    if (!timestamp.empty()) {
        std::tm tm = {};
        std::istringstream ss(timestamp);
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

        if (!ss.fail()) {
            utc_timestamp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
        }
    }

    return utc_timestamp;
}
