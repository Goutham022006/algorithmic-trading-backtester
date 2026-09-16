#include "Portfolio.h"

Portfolio::Portfolio(double initialCapital)
    : cash_(initialCapital), value_(initialCapital) {}

bool Portfolio::buy(const MarketData& data, int quantity) {
    if (quantity <= 0 || data.close <= 0.0) return false;
    const double cost = data.close * quantity;
    if (cost > cash_) return false;

    cash_ -= cost;
    holdings_ += quantity;
    trades_.push_back({data.date, TradeType::Buy, data.close, quantity, cost});
    markToMarket(data.close);
    return true;
}

bool Portfolio::sell(const MarketData& data, int quantity) {
    if (quantity <= 0 || quantity > holdings_ || data.close <= 0.0) return false;
    const double proceeds = data.close * quantity;

    cash_ += proceeds;
    holdings_ -= quantity;
    trades_.push_back({data.date, TradeType::Sell, data.close, quantity, proceeds});
    markToMarket(data.close);
    return true;
}

void Portfolio::markToMarket(double currentPrice) {
    value_ = cash_ + holdings_ * currentPrice;
}

double Portfolio::cash() const { return cash_; }
int Portfolio::holdings() const { return holdings_; }
double Portfolio::value() const { return value_; }
const std::vector<Trade>& Portfolio::trades() const { return trades_; }
