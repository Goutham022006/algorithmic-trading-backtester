#include "Backtester.h"
#include "BuyAndHoldStrategy.h"
#include "DataLoader.h"

#include <iomanip>
#include <iostream>

int main(int argc, char* argv[]) {
    const std::string filePath = argc > 1 ? argv[1] : "data/sample_prices.csv";
    constexpr double initialCapital = 100000.0;

    try {
        const auto data = DataLoader::load(filePath);
        Portfolio portfolio(initialCapital);
        BuyAndHoldStrategy strategy;

        const auto snapshots = Backtester::run(data, strategy, portfolio);
        const double totalReturn =
            (portfolio.value() - initialCapital) / initialCapital * 100.0;

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Algorithmic Trading Backtesting Engine\n";
        std::cout << "Strategy: Buy and Hold\n";
        std::cout << "Initial Capital: " << initialCapital << "\n";
        std::cout << "Final Portfolio Value: " << portfolio.value() << "\n";
        std::cout << "Total Return: " << totalReturn << "%\n";
        std::cout << "Holdings: " << portfolio.holdings() << "\n";
        std::cout << "Trades: " << portfolio.trades().size() << "\n";
        std::cout << "Tracked Sessions: " << snapshots.size() << "\n";
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
