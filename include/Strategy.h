#pragma once

#include "MarketData.h"
#include <vector>

enum class Signal { Buy, Hold, Sell };

class Strategy {
public:
    virtual Signal generateSignal(const std::vector<MarketData>& data, std::size_t index) const = 0;
    virtual ~Strategy() = default;
};
