#pragma once

#include "Strategy.h"

class BuyAndHoldStrategy : public Strategy {
public:
    Signal generateSignal(const std::vector<MarketData>& data, std::size_t index) const override;
};
