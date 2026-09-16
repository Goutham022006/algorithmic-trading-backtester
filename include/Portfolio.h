#pragma once

#include "Trade.h"
#include <vector>

class Portfolio {
public:
    explicit Portfolio(double initialCapital);

    bool buy(const MarketData& marketData, int quantity);
    bool sell(const MarketData& marketData, int quantity);
    void markToMarket(double currentPrice);

    double cash() const;
    int holdings() const;
    double value() const;
    const std::vector<Trade>& trades() const;

private:
    double cash_;
    int holdings_ = 0;
    double value_;
    std::vector<Trade> trades_;
};
