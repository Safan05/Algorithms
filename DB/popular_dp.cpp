#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MOD = 1e9 + 7;
const int MAXN = 1005;

// ==============================================
// CLASSIC DP PROBLEMS
// ==============================================

// Fibonacci - Basic DP
long long fibonacci(int n) {
    if (n <= 1) return n;

    vector<long long> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

// Space optimized Fibonacci
long long fibonacci_optimized(int n) {
    if (n <= 1) return n;

    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// ==============================================
// KNAPSACK PROBLEMS
// ==============================================

// 0/1 Knapsack
int knapsack_01(vector<int>& weights, vector<int>& values, int W) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w],
                    dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W];
}

// Space optimized 0/1 Knapsack
int knapsack_01_optimized(vector<int>& weights, vector<int>& values, int W) {
    vector<int> dp(W + 1, 0);

    for (int i = 0; i < weights.size(); i++) {
        for (int w = W; w >= weights[i]; w--) {
            dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
        }
    }

    return dp[W];
}

// Unbounded Knapsack
int knapsack_unbounded(vector<int>& weights, vector<int>& values, int W) {
    vector<int> dp(W + 1, 0);

    for (int w = 1; w <= W; w++) {
        for (int i = 0; i < weights.size(); i++) {
            if (weights[i] <= w) {
                dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
            }
        }
    }

    return dp[W];
}

// ==============================================
// LONGEST COMMON SUBSEQUENCE (LCS)
// ==============================================

int lcs(string& s1, string& s2) {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[m][n];
}

// Space optimized LCS
int lcs_optimized(string& s1, string& s2) {
    int m = s1.length(), n = s2.length();
    vector<int> prev(n + 1, 0), curr(n + 1, 0);

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                curr[j] = prev[j - 1] + 1;
            }
            else {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }
        prev = curr;
    }

    return prev[n];
}

// Print LCS
string print_lcs(string& s1, string& s2) {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    string result = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            result = s1[i - 1] + result;
            i--; j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }

    return result;
}

// ==============================================
// LONGEST INCREASING SUBSEQUENCE (LIS)
// ==============================================

// O(n^2) LIS
int lis_n2(vector<int>& arr) {
    int n = arr.size();
    vector<int> dp(n, 1);

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    return *max_element(dp.begin(), dp.end());
}

// O(n log n) LIS using binary search
int lis_nlogn(vector<int>& arr) {
    vector<int> tails;

    for (int x : arr) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) {
            tails.push_back(x);
        }
        else {
            *it = x;
        }
    }

    return tails.size();
}

// Print LIS
vector<int> print_lis(vector<int>& arr) {
    int n = arr.size();
    vector<int> dp(n, 1);
    vector<int> parent(n, -1);

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
    }

    int max_length = *max_element(dp.begin(), dp.end());
    int max_idx = max_element(dp.begin(), dp.end()) - dp.begin();

    vector<int> lis;
    int curr = max_idx;
    while (curr != -1) {
        lis.push_back(arr[curr]);
        curr = parent[curr];
    }

    reverse(lis.begin(), lis.end());
    return lis;
}

// ==============================================
// EDIT DISTANCE
// ==============================================

int edit_distance(string& s1, string& s2) {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    // Base cases
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = 1 + min({ dp[i - 1][j],     // deletion
                                   dp[i][j - 1],     // insertion
                                   dp[i - 1][j - 1] }); // substitution
            }
        }
    }

    return dp[m][n];
}

// ==============================================
// COIN CHANGE PROBLEMS
// ==============================================

// Minimum coins to make amount
int coin_change_min(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INF);
    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (coin <= i && dp[i - coin] != INF) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    return dp[amount] == INF ? -1 : dp[amount];
}

// Number of ways to make amount
int coin_change_ways(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;

    for (int coin : coins) {
        for (int i = coin; i <= amount; i++) {
            dp[i] += dp[i - coin];
        }
    }

    return dp[amount];
}

// ==============================================
// PALINDROME PROBLEMS
// ==============================================

// Longest Palindromic Subsequence
int longest_palindromic_subsequence(string s) {
    int n = s.length();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Every single character is a palindrome
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }

    // Check for palindromes of length 2 and more
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;

            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            }
            else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[0][n - 1];
}

// Minimum insertions to make palindrome
int min_insertions_palindrome(string s) {
    return s.length() - longest_palindromic_subsequence(s);
}

// Check if string can be palindrome by removing at most k characters
bool can_be_palindrome(string s, int k) {
    int n = s.length();
    return longest_palindromic_subsequence(s) >= n - k;
}

// ==============================================
// MATRIX CHAIN MULTIPLICATION
// ==============================================

int matrix_chain_multiplication(vector<int>& dimensions) {
    int n = dimensions.size() - 1; // number of matrices
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            dp[i][j] = INF;

            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] +
                    dimensions[i] * dimensions[k + 1] * dimensions[j + 1];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[0][n - 1];
}

// ==============================================
// SUBSET SUM PROBLEMS
// ==============================================

// Subset sum exists
bool subset_sum(vector<int>& arr, int target) {
    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int num : arr) {
        for (int j = target; j >= num; j--) {
            dp[j] = dp[j] || dp[j - num];
        }
    }

    return dp[target];
}

// Count subsets with given sum
int count_subsets(vector<int>& arr, int target) {
    vector<int> dp(target + 1, 0);
    dp[0] = 1;

    for (int num : arr) {
        for (int j = target; j >= num; j--) {
            dp[j] += dp[j - num];
        }
    }

    return dp[target];
}

// Partition into equal sum subsets
bool can_partition(vector<int>& arr) {
    int sum = accumulate(arr.begin(), arr.end(), 0);
    if (sum % 2 != 0) return false;

    return subset_sum(arr, sum / 2);
}

// ==============================================
// STOCK PROBLEMS
// ==============================================

// Best time to buy and sell stock (one transaction)
int max_profit_one_transaction(vector<int>& prices) {
    int min_price = INT_MAX;
    int max_profit = 0;

    for (int price : prices) {
        min_price = min(min_price, price);
        max_profit = max(max_profit, price - min_price);
    }

    return max_profit;
}

// Best time to buy and sell stock (unlimited transactions)
int max_profit_unlimited(vector<int>& prices) {
    int profit = 0;

    for (int i = 1; i < prices.size(); i++) {
        if (prices[i] > prices[i - 1]) {
            profit += prices[i] - prices[i - 1];
        }
    }

    return profit;
}

// Best time to buy and sell stock (at most k transactions)
int max_profit_k_transactions(vector<int>& prices, int k) {
    int n = prices.size();
    if (n <= 1 || k == 0) return 0;

    // If k >= n/2, we can do unlimited transactions
    if (k >= n / 2) {
        return max_profit_unlimited(prices);
    }

    vector<vector<int>> buy(k + 1, vector<int>(n, -INF));
    vector<vector<int>> sell(k + 1, vector<int>(n, 0));

    for (int i = 1; i <= k; i++) {
        buy[i][0] = -prices[0];
        for (int j = 1; j < n; j++) {
            buy[i][j] = max(buy[i][j - 1], sell[i - 1][j - 1] - prices[j]);
            sell[i][j] = max(sell[i][j - 1], buy[i][j - 1] + prices[j]);
        }
    }

    return sell[k][n - 1];
}

// ==============================================
// PATH PROBLEMS
// ==============================================

// Unique paths in grid
int unique_paths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 1));

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }

    return dp[m - 1][n - 1];
}

// Minimum path sum in grid
int min_path_sum(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dp(m, vector<int>(n));

    dp[0][0] = grid[0][0];

    // Fill first row
    for (int j = 1; j < n; j++) {
        dp[0][j] = dp[0][j - 1] + grid[0][j];
    }

    // Fill first column
    for (int i = 1; i < m; i++) {
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    }

    // Fill the rest
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
        }
    }

    return dp[m - 1][n - 1];
}

// Maximum path sum in grid (can move in 4 directions)
int max_path_sum_4dir(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, -INF));

    dp[0][0] = grid[0][0];

    // Use a priority queue for Dijkstra-like approach
    priority_queue<tuple<int, int, int>> pq;
    pq.push({ grid[0][0], 0, 0 });

    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    while (!pq.empty()) {
        auto [val, x, y] = pq.top();
        pq.pop();

        if (val < dp[x][y]) continue;

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                int new_val = dp[x][y] + grid[nx][ny];
                if (new_val > dp[nx][ny]) {
                    dp[nx][ny] = new_val;
                    pq.push({ new_val, nx, ny });
                }
            }
        }
    }

    return dp[m - 1][n - 1];
}

// ==============================================
// TREE DP
// ==============================================

vector<vector<int>> tree;
vector<vector<int>> memo;

// Maximum path sum in tree (each node to be visited at most once)
int tree_dp(int node, int parent, int include) {
    if (memo[node][include] != -1) {
        return memo[node][include];
    }

    int result = 0;

    if (include) {
        // Include current node
        result = 1; // assuming each node has value 1
        for (int child : tree[node]) {
            if (child != parent) {
                result += tree_dp(child, node, 0); // children can't be included
            }
        }
    }
    else {
        // Don't include current node
        for (int child : tree[node]) {
            if (child != parent) {
                result += max(tree_dp(child, node, 0), tree_dp(child, node, 1));
            }
        }
    }

    return memo[node][include] = result;
}

// ==============================================
// DIGIT DP
// ==============================================

string num_str;
vector<vector<vector<int>>> digit_memo;

// Count numbers <= N with digit sum = target
int digit_dp(int pos, int sum, int tight) {
    if (pos == num_str.length()) {
        return (sum == 0) ? 1 : 0;
    }

    if (digit_memo[pos][sum][tight] != -1) {
        return digit_memo[pos][sum][tight];
    }

    int limit = tight ? (num_str[pos] - '0') : 9;
    int result = 0;

    for (int digit = 0; digit <= limit; digit++) {
        int new_tight = tight && (digit == limit);
        if (sum >= digit) {
            result += digit_dp(pos + 1, sum - digit, new_tight);
        }
    }

    return digit_memo[pos][sum][tight] = result;
}

int count_numbers_with_digit_sum(string n, int target_sum) {
    num_str = n;
    digit_memo.assign(n.length(), vector<vector<int>>(target_sum + 1, vector<int>(2, -1)));
    return digit_dp(0, target_sum, 1);
}

// ==============================================
// BITMASK DP
// ==============================================

// Traveling Salesman Problem
int tsp(vector<vector<int>>& dist) {
    int n = dist.size();
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));

    dp[1][0] = 0; // start from city 0

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u))) continue;

            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue;

                int new_mask = mask | (1 << v);
                dp[new_mask][v] = min(dp[new_mask][v], dp[mask][u] + dist[u][v]);
            }
        }
    }

    int result = INF;
    for (int i = 1; i < n; i++) {
        result = min(result, dp[(1 << n) - 1][i] + dist[i][0]);
    }

    return result;
}

// Assignment Problem (Hungarian Algorithm using bitmask DP)
int assignment_problem(vector<vector<int>>& cost) {
    int n = cost.size();
    vector<int> dp(1 << n, INF);
    dp[0] = 0;

    for (int mask = 0; mask < (1 << n); mask++) {
        int person = __builtin_popcount(mask);
        if (person >= n) continue;

        for (int task = 0; task < n; task++) {
            if (!(mask & (1 << task))) {
                int new_mask = mask | (1 << task);
                dp[new_mask] = min(dp[new_mask], dp[mask] + cost[person][task]);
            }
        }
    }

    return dp[(1 << n) - 1];
}

// ==============================================
// PROBABILITY DP
// ==============================================

// Probability of reaching target sum with dice
double dice_probability(int n_dice, int n_faces, int target) {
    vector<vector<double>> dp(n_dice + 1, vector<double>(target + 1, 0.0));
    dp[0][0] = 1.0;

    for (int i = 1; i <= n_dice; i++) {
        for (int j = i; j <= min(target, i * n_faces); j++) {
            for (int k = 1; k <= min(n_faces, j); k++) {
                dp[i][j] += dp[i - 1][j - k] / n_faces;
            }
        }
    }

    return dp[n_dice][target];
}

// ==============================================
// UTILITY FUNCTIONS
// ==============================================

// Print DP table (for debugging)
template<typename T>
void print_dp_table(vector<vector<T>>& dp) {
    for (auto& row : dp) {
        for (auto& val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

// Memoization helper
map<pair<int, int>, int> memo_map;

int solve_with_memo(int param1, int param2) {
    pair<int, int> key = { param1, param2 };
    if (memo_map.find(key) != memo_map.end()) {
        return memo_map[key];
    }

    // Base case
    if (param1 == 0 || param2 == 0) {
        return memo_map[key] = 0;
    }

    // Recursive case
    int result = solve_with_memo(param1 - 1, param2) + solve_with_memo(param1, param2 - 1);
    return memo_map[key] = result;
}

// ==============================================
// EXAMPLE USAGE AND TESTING
// ==============================================

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== Dynamic Programming Algorithms Demo ===" << endl;

    // Fibonacci
    cout << "Fibonacci(10): " << fibonacci(10) << endl;
    cout << "Fibonacci Optimized(10): " << fibonacci_optimized(10) << endl;

    // Knapsack
    vector<int> weights = { 1, 3, 4, 5 };
    vector<int> values = { 1, 4, 5, 7 };
    int W = 7;
    cout << "0/1 Knapsack: " << knapsack_01(weights, values, W) << endl;
    cout << "Unbounded Knapsack: " << knapsack_unbounded(weights, values, W) << endl;

    // LCS
    string s1 = "AGGTAB", s2 = "GXTXAYB";
    cout << "LCS length: " << lcs(s1, s2) << endl;
    cout << "LCS string: " << print_lcs(s1, s2) << endl;

    // LIS
    vector<int> arr = { 10, 9, 2, 5, 3, 7, 101, 18 };
    cout << "LIS length: " << lis_nlogn(arr) << endl;

    // Edit Distance
    string str1 = "sunday", str2 = "saturday";
    cout << "Edit Distance: " << edit_distance(str1, str2) << endl;

    // Coin Change
    vector<int> coins = { 1, 2, 5 };
    int amount = 11;
    cout << "Min coins for " << amount << ": " << coin_change_min(coins, amount) << endl;
    cout << "Ways to make " << amount << ": " << coin_change_ways(coins, amount) << endl;

    // Palindrome
    string pal = "bbbab";
    cout << "Longest Palindromic Subsequence: " << longest_palindromic_subsequence(pal) << endl;

    // Matrix Chain Multiplication
    vector<int> dimensions = { 1, 2, 3, 4 };
    cout << "Matrix Chain Multiplication: " << matrix_chain_multiplication(dimensions) << endl;

    // Subset Sum
    vector<int> subset_arr = { 3, 34, 4, 12, 5, 2 };
    int target = 9;
    cout << "Subset sum " << target << " exists: " << (subset_sum(subset_arr, target) ? "Yes" : "No") << endl;

    // Stock Problems
    vector<int> stock_prices = { 7, 1, 5, 3, 6, 4 };
    cout << "Max profit (one transaction): " << max_profit_one_transaction(stock_prices) << endl;
    cout << "Max profit (unlimited): " << max_profit_unlimited(stock_prices) << endl;

    // Path Problems
    cout << "Unique paths (3x3 grid): " << unique_paths(3, 3) << endl;

    // Digit DP
    cout << "Numbers <= 123 with digit sum 6: " << count_numbers_with_digit_sum("123", 6) << endl;

    // Probability DP
    cout << "Probability of sum 10 with 2 dice: " << dice_probability(2, 6, 10) << endl;

    return 0;
}