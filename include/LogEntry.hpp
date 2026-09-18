#ifndef LOG_ENTRY_HPP
#define LOG_ENTRY_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

class LogEntry {
public:
    std::string originalLine;
    std::string datetimeKey; // Format: YYYYMMDDHHMMSS

    LogEntry() = default;

    LogEntry(const std::string& line) {
        parseLogEntry(line);
    }

    bool operator<(const LogEntry& other) const {
        return datetimeKey < other.datetimeKey;
    }

    bool operator<=(const LogEntry& other) const {
        return datetimeKey <= other.datetimeKey;
    }

    bool operator>(const LogEntry& other) const {
        return datetimeKey > other.datetimeKey;
    }

    bool operator>=(const LogEntry& other) const {
        return datetimeKey >= other.datetimeKey;
    }

    bool operator==(const LogEntry& other) const {
        return datetimeKey == other.datetimeKey;
    }

private:
    std::string monthToIntString(const std::string& month) const {
        if (month == "Jan") return "01";
        if (month == "Feb") return "02";
        if (month == "Mar") return "03";
        if (month == "Apr") return "04";
        if (month == "May") return "05";
        if (month == "Jun") return "06";
        if (month == "Jul") return "07";
        if (month == "Aug") return "08";
        if (month == "Sep") return "09";
        if (month == "Oct") return "10";
        if (month == "Nov") return "11";
        if (month == "Dec") return "12";
        return "00";
    }

    void parseLogEntry(const std::string& line) {
        originalLine = line;

        if (line.length() < 20) return; // Fallback for invalid lines

        std::string month = line.substr(0, 3);
        std::string day = line.substr(4, 2);
        std::string year = line.substr(7, 4);
        std::string time = line.substr(12, 8); // HH:MM:SS
        
        std::string hour = time.substr(0, 2);
        std::string min = time.substr(3, 2);
        std::string sec = time.substr(6, 2);

        datetimeKey = year + monthToIntString(month) + day + hour + min + sec;
    }
};

#endif // LOG_ENTRY_HPP
