#pragma once

#include "MarketData.h"
#include <string>
#include <vector>

class DataLoader {
public:
    static std::vector<MarketData> load(const std::string& filePath);
};
