#pragma once

#include <string>

enum class TradeType { Buy, Sell };

struct Trade {
    std::string date;
    TradeType type;
    double price{};
    int quantity{};
    double value{};
};
