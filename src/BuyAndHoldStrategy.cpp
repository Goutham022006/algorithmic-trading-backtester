#include "BuyAndHoldStrategy.h"

Signal BuyAndHoldStrategy::generateSignal(const std::vector<MarketData>&, std::size_t index) const {
    return index == 0 ? Signal::Buy : Signal::Hold;
}
