#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Stores details of a completed transaction
struct Transaction {
    int buyDay;
    int sellDay;
    int profit;
};

class StockTradingSimulator {
public:

    // Calculates maximum profit using at most k transactions
    int getMaxProfit(const vector<int>& prices,
                     int k,
                     vector<Transaction>& transactions) {

        int n = prices.size();

        if (n == 0 || k == 0)
            return 0;

        // If k is large enough, unlimited transactions are possible
        if (k >= n / 2) {
            return greedyStrategy(prices, transactions);
        }

        // dp[t][d] = maximum profit using at most
        // t transactions until day d
        vector<vector<int>> dp(
            k + 1,
            vector<int>(n, 0)
        );

        // Calculate DP table
        for (int t = 1; t <= k; t++) {

            int maxDiff = -prices[0];

            for (int d = 1; d < n; d++) {

                // Option 1: Do nothing today
                // Option 2: Sell the stock today
                dp[t][d] = max(
                    dp[t][d - 1],
                    prices[d] + maxDiff
                );

                // Best value for buying before a future sale
                maxDiff = max(
                    maxDiff,
                    dp[t - 1][d] - prices[d]
                );
            }
        }

        // Recover the actual buy/sell transactions
        extractTransactions(
            dp,
            prices,
            k,
            transactions
        );

        return dp[k][n - 1];
    }

    // Displays a simple terminal-based price chart
    void visualizePriceChart(const vector<int>& prices) {

        cout << "\nPrice Chart (10 units per #):\n";

        for (int day = 0; day < prices.size(); day++) {

            cout << "Day "
                 << setw(2)
                 << day
                 << " | ";

            int bars = prices[day] / 10;

            for (int i = 0; i < bars; i++) {
                cout << "#";
            }

            cout << " (" << prices[day] << ")\n";
        }

        cout << endl;
    }

private:

    // Greedy strategy for unlimited transactions
    int greedyStrategy(
        const vector<int>& prices,
        vector<Transaction>& transactions) {

        int totalProfit = 0;

        for (int i = 1; i < prices.size(); i++) {

            // Price increased from previous day
            if (prices[i] > prices[i - 1]) {

                int profit = prices[i] - prices[i - 1];

                totalProfit += profit;

                transactions.push_back({
                    i - 1,
                    i,
                    profit
                });
            }
        }

        return totalProfit;
    }

    // Backtracks through the DP table to find transactions
    void extractTransactions(
        const vector<vector<int>>& dp,
        const vector<int>& prices,
        int k,
        vector<Transaction>& transactions) {

        int t = k;
        int day = prices.size() - 1;

        while (t > 0 && day > 0) {

            // No transaction was completed today
            if (dp[t][day] == dp[t][day - 1]) {

                day--;
            }
            else {

                int sellDay = day;
                int currentProfit = dp[t][day];

                // Find the corresponding buy day
                for (int buyDay = day - 1;
                     buyDay >= 0;
                     buyDay--) {

                    if (dp[t - 1][buyDay]
                        - prices[buyDay]
                        == currentProfit
                        - prices[sellDay]) {

                        transactions.push_back({
                            buyDay,
                            sellDay,
                            prices[sellDay] - prices[buyDay]
                        });

                        day = buyDay;
                        break;
                    }
                }

                t--;
            }
        }

        // Transactions were found backwards
        reverse(
            transactions.begin(),
            transactions.end()
        );
    }
};

int main() {

    // Sample stock prices for each day
    vector<int> prices = {
        100, 180, 260, 310,
        40, 535, 695
    };

    // Maximum number of transactions
    int k = 2;

    StockTradingSimulator simulator;

    vector<Transaction> transactions;

    // Calculate maximum profit
    int maxProfit = simulator.getMaxProfit(
        prices,
        k,
        transactions
    );

    // Display result
    cout << "Maximum Profit with "
         << k
         << " transactions: "
         << maxProfit
         << "\n\n";

    // Display transaction history
    cout << "Transaction Log:\n";

    for (const auto& transaction : transactions) {

        cout << "Buy on Day "
             << transaction.buyDay
             << " at "
             << prices[transaction.buyDay]

             << " | Sell on Day "
             << transaction.sellDay
             << " at "
             << prices[transaction.sellDay]

             << " | Profit: "
             << transaction.profit
             << "\n";
    }

    // Display price visualization
    simulator.visualizePriceChart(prices);

    return 0;
}