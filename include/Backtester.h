#pragma once

#include "Portfolio.h"
#include "Strategy.h"
#include <vector>

struct PortfolioSnapshot {
    std::string date;
    double value;
    double cash;
    int holdings;
};

class Backtester {
public:
    static std::vector<PortfolioSnapshot> run(
        const std::vector<MarketData>& data,
        Strategy& strategy,
        Portfolio& portfolio);
};
