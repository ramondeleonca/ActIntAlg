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

    std::string ip;
    std::string eventType;
    std::string month;
    std::string day;
    std::string year;

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

    std::string dayKey() const {
        return datetimeKey.length() >= 8 ? datetimeKey.substr(0, 8) : "";
    }

    std::string dayString() const {
        return (!month.empty() && !day.empty() && !year.empty())
            ? (month + " " + day + " " + year)
            : (originalLine.length() >= 11 ? originalLine.substr(0, 11) : "");
    }

    bool isValid() const {
        return datetimeKey.length() == 14 && !ip.empty();
    }

    static std::string monthToIntString(const std::string& month) {
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

private:
    void parseLogEntry(const std::string& line) {
        originalLine = line;

        if (line.length() < 20) return; // Fallback for invalid lines

        month = line.substr(0, 3);
        day = line.substr(4, 2);
        year = line.substr(7, 4);
        std::string time = line.substr(12, 8); // HH:MM:SS
        
        std::string hour = time.substr(0, 2);
        std::string min = time.substr(3, 2);
        std::string sec = time.substr(6, 2);

        datetimeKey = year + monthToIntString(month) + day + hour + min + sec;

        if (line.length() > 21) {
            std::istringstream ss(line.substr(21));
            ss >> ip;
            std::string rest;
            if (std::getline(ss, rest) && rest.length() > 1) {
                eventType = rest.substr(1);
            }
        }
    }
};

#endif // LOG_ENTRY_HPP
