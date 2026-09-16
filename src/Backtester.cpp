#include "Backtester.h"

std::vector<PortfolioSnapshot> Backtester::run(
    const std::vector<MarketData>& data,
    Strategy& strategy,
    Portfolio& portfolio) {
    std::vector<PortfolioSnapshot> snapshots;

    for (std::size_t i = 0; i < data.size(); ++i) {
        const Signal signal = strategy.generateSignal(data, i);

        if (signal == Signal::Buy && portfolio.holdings() == 0) {
            const int quantity = static_cast<int>(portfolio.cash() / data[i].close);
            portfolio.buy(data[i], quantity);
        } else if (signal == Signal::Sell && portfolio.holdings() > 0) {
            portfolio.sell(data[i], portfolio.holdings());
        }

        portfolio.markToMarket(data[i].close);
        snapshots.push_back({data[i].date, portfolio.value(), portfolio.cash(), portfolio.holdings()});
    }

    return snapshots;
}
