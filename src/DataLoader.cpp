#include "DataLoader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

std::vector<MarketData> DataLoader::load(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open CSV file: " + filePath);
    }

    std::vector<MarketData> data;
    std::string line;
    bool firstLine = true;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (firstLine) {
            firstLine = false;
            if (line.find("date") != std::string::npos) continue;
        }

        std::stringstream stream(line);
        std::string date;
        std::string closeText;

        if (!std::getline(stream, date, ',') ||
            !std::getline(stream, closeText, ',')) {
            throw std::runtime_error("Invalid CSV row: " + line);
        }

        data.push_back({date, std::stod(closeText)});
    }

    if (data.empty()) {
        throw std::runtime_error("CSV file contains no market data.");
    }
    return data;
}
