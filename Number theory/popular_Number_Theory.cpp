#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 5;

// ==============================================
// BASIC NUMBER THEORY
// ==============================================

// GCD using Euclidean algorithm
long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

// LCM
long long lcm(long long a, long long b) {
    return (a / gcd(a, b)) * b;
}

// Extended Euclidean Algorithm
long long extended_gcd(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    long long x1, y1;
    long long gcd_val = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd_val;
}

// Modular inverse using Extended Euclidean
long long mod_inverse(long long a, long long m) {
    long long x, y;
    long long g = extended_gcd(a, m, x, y);
    if (g != 1) return -1; // inverse doesn't exist
    return (x % m + m) % m;
}

// ==============================================
// MODULAR ARITHMETIC
// ==============================================

// Fast modular exponentiation
long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// Modular inverse using Fermat's little theorem (when mod is prime)
long long mod_inverse_fermat(long long a, long long p) {
    return mod_pow(a, p - 2, p);
}

// Modular factorial and its inverse
vector<long long> fact, inv_fact;

void precompute_factorials(int n) {
    fact.resize(n + 1);
    inv_fact.resize(n + 1);
    
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i-1] * i) % MOD;
    }
    
    inv_fact[n] = mod_inverse_fermat(fact[n], MOD);
    for (int i = n - 1; i >= 0; i--) {
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % MOD;
    }
}

// nCr mod p
long long nCr(int n, int r) {
    if (r > n || r < 0) return 0;
    return (fact[n] * inv_fact[r] % MOD) * inv_fact[n - r] % MOD;
}

// ==============================================
// PRIME NUMBERS
// ==============================================

// Sieve of Eratosthenes
vector<bool> is_prime;
vector<int> primes;

void sieve(int n) {
    is_prime.assign(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
}

// Segmented Sieve for large ranges
vector<bool> segmented_sieve(long long L, long long R) {
    long long lim = sqrt(R);
    sieve(lim);
    
    vector<bool> is_prime_range(R - L + 1, true);
    
    for (long long p : primes) {
        long long start = max(p * p, (L + p - 1) / p * p);
        
        for (long long j = start; j <= R; j += p) {
            is_prime_range[j - L] = false;
        }
    }
    
    if (L == 1) is_prime_range[0] = false;
    
    return is_prime_range;
}

// Miller-Rabin Primality Test
bool miller_rabin(long long n, long long a) {
    if (n <= 1 || (n > 2 && n % 2 == 0)) return false;
    if (n == 2 || n == 3) return true;
    
    long long d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }
    
    long long x = mod_pow(a, d, n);
    if (x == 1 || x == n - 1) return true;
    
    for (int i = 0; i < r - 1; i++) {
        x = (x * x) % n;
        if (x == n - 1) return true;
    }
    
    return false;
}

bool is_prime_mr(long long n) {
    if (n <= 1) return false;
    vector<long long> witnesses = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    
    for (long long a : witnesses) {
        if (a >= n) break;
        if (!miller_rabin(n, a)) return false;
    }
    return true;
}

// ==============================================
// FACTORIZATION
// ==============================================

// Prime factorization
vector<pair<long long, int>> factorize(long long n) {
    vector<pair<long long, int>> factors;
    
    for (long long p : primes) {
        if (p * p > n) break;
        if (n % p == 0) {
            int count = 0;
            while (n % p == 0) {
                n /= p;
                count++;
            }
            factors.push_back({p, count});
        }
    }
    
    if (n > 1) {
        factors.push_back({n, 1});
    }
    
    return factors;
}

// All divisors of a number
vector<long long> get_divisors(long long n) {
    vector<long long> divisors;
    
    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (i != n / i) {
                divisors.push_back(n / i);
            }
        }
    }
    
    sort(divisors.begin(), divisors.end());
    return divisors;
}

// Count of divisors
long long count_divisors(long long n) {
    auto factors = factorize(n);
    long long count = 1;
    
    for (auto& f : factors) {
        count *= (f.second + 1);
    }
    
    return count;
}

// Sum of divisors
long long sum_divisors(long long n) {
    auto factors = factorize(n);
    long long sum = 1;
    
    for (auto& f : factors) {
        long long p = f.first;
        int k = f.second;
        sum *= (mod_pow(p, k + 1, MOD) - 1 + MOD) % MOD;
        sum %= MOD;
        sum = (sum * mod_inverse_fermat(p - 1, MOD)) % MOD;
    }
    
    return sum;
}

// ==============================================
// EULER'S TOTIENT FUNCTION
// ==============================================

// Single phi(n)
long long phi(long long n) {
    long long result = n;
    
    for (long long p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    
    if (n > 1) result -= result / n;
    return result;
}

// Sieve for phi (multiple values)
vector<long long> phi_sieve(int n) {
    vector<long long> phi(n + 1);
    
    for (int i = 0; i <= n; i++) phi[i] = i;
    
    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) { // i is prime
            for (int j = i; j <= n; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
    
    return phi;
}

// ==============================================
// CHINESE REMAINDER THEOREM
// ==============================================

// CRT for two equations
pair<long long, long long> crt_two(long long a1, long long m1, long long a2, long long m2) {
    long long x, y;
    long long g = extended_gcd(m1, m2, x, y);
    
    if ((a2 - a1) % g != 0) return {-1, -1}; // no solution
    
    long long lcm_val = m1 / g * m2;
    long long result = (a1 + m1 * (a2 - a1) / g * x % (m2 / g)) % lcm_val;
    if (result < 0) result += lcm_val;
    
    return {result, lcm_val};
}

// CRT for multiple equations
long long chinese_remainder_theorem(vector<long long>& a, vector<long long>& m) {
    if (a.empty()) return 0;
    
    long long result = a[0];
    long long mod = m[0];
    
    for (int i = 1; i < a.size(); i++) {
        auto crt_result = crt_two(result, mod, a[i], m[i]);
        if (crt_result.first == -1) return -1; // no solution
        
        result = crt_result.first;
        mod = crt_result.second;
    }
    
    return result;
}

// ==============================================
// DISCRETE LOGARITHM
// ==============================================

// Baby-step Giant-step algorithm
long long discrete_log(long long a, long long b, long long m) {
    if (b == 1) return 0;
    
    long long n = sqrt(m) + 1;
    
    // Baby steps
    unordered_map<long long, long long> baby_steps;
    long long gamma = 1;
    
    for (long long j = 0; j < n; j++) {
        if (baby_steps.find(gamma) == baby_steps.end()) {
            baby_steps[gamma] = j;
        }
        gamma = (gamma * a) % m;
    }
    
    // Giant steps
    long long factor = mod_inverse_fermat(mod_pow(a, n, m), m);
    long long beta = b;
    
    for (long long i = 0; i < n; i++) {
        if (baby_steps.find(beta) != baby_steps.end()) {
            long long result = i * n + baby_steps[beta];
            if (result > 0) return result;
        }
        beta = (beta * factor) % m;
    }
    
    return -1; // no solution
}

// ==============================================
// QUADRATIC RESIDUES
// ==============================================

// Legendre symbol
int legendre_symbol(long long a, long long p) {
    return mod_pow(a, (p - 1) / 2, p);
}

// Tonelli-Shanks algorithm for square root modulo prime
long long sqrt_mod(long long a, long long p) {
    if (legendre_symbol(a, p) != 1) return -1; // not a quadratic residue
    
    if (p % 4 == 3) return mod_pow(a, (p + 1) / 4, p);
    
    // Tonelli-Shanks algorithm
    long long q = p - 1;
    int s = 0;
    while (q % 2 == 0) {
        q /= 2;
        s++;
    }
    
    if (s == 1) return mod_pow(a, (p + 1) / 4, p);
    
    // Find quadratic non-residue
    long long z = 2;
    while (legendre_symbol(z, p) != p - 1) z++;
    
    long long m = s;
    long long c = mod_pow(z, q, p);
    long long t = mod_pow(a, q, p);
    long long r = mod_pow(a, (q + 1) / 2, p);
    
    while (t != 1) {
        // Find smallest i such that t^(2^i) = 1
        long long temp = t;
        int i = 1;
        while (temp != 1) {
            temp = (temp * temp) % p;
            i++;
        }
        
        long long b = mod_pow(c, 1LL << (m - i - 1), p);
        m = i;
        c = (b * b) % p;
        t = (t * c) % p;
        r = (r * b) % p;
    }
    
    return r;
}

// ==============================================
// SPECIAL NUMBER SEQUENCES
// ==============================================

// Catalan numbers
vector<long long> catalan(int n) {
    vector<long long> dp(n + 1, 0);
    dp[0] = dp[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            dp[i] = (dp[i] + dp[j] * dp[i - 1 - j]) % MOD;
        }
    }
    
    return dp;
}

// Fibonacci matrix exponentiation
pair<long long, long long> fib_matrix(long long n) {
    if (n == 0) return {0, 1};
    
    auto p = fib_matrix(n / 2);
    long long c = p.first * (2 * p.second - p.first);
    long long d = p.first * p.first + p.second * p.second;
    
    if (n % 2 == 0) return {c, d};
    else return {d, c + d};
}

// Lucas numbers
long long lucas(long long n) {
    if (n == 0) return 2;
    if (n == 1) return 1;
    
    auto fib_pair = fib_matrix(n);
    return (2 * fib_pair.second - fib_pair.first + MOD) % MOD;
}

// ==============================================
// MOBIUS FUNCTION
// ==============================================

vector<int> mobius_sieve(int n) {
    vector<int> mu(n + 1, 1);
    vector<bool> is_prime(n + 1, true);
    
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i; j <= n; j += i) {
                is_prime[j] = false;
                mu[j] *= -1;
            }
            
            for (long long j = (long long)i * i; j <= n; j += (long long)i * i) {
                mu[j] = 0;
            }
        }
    }
    
    return mu;
}

// ==============================================
// UTILITY FUNCTIONS
// ==============================================

// Check if number is perfect square
bool is_perfect_square(long long n) {
    long long root = sqrt(n);
    return root * root == n;
}

// Count trailing zeros in n!
long long trailing_zeros_factorial(long long n) {
    long long count = 0;
    for (long long i = 5; i <= n; i *= 5) {
        count += n / i;
    }
    return count;
}

// Binary exponentiation for matrices
vector<vector<long long>> matrix_multiply(vector<vector<long long>>& a, vector<vector<long long>>& b) {
    int n = a.size();
    vector<vector<long long>> c(n, vector<long long>(n, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    
    return c;
}

vector<vector<long long>> matrix_power(vector<vector<long long>> base, long long exp) {
    int n = base.size();
    vector<vector<long long>> result(n, vector<long long>(n, 0));
    
    // Initialize identity matrix
    for (int i = 0; i < n; i++) {
        result[i][i] = 1;
    }
    
    while (exp > 0) {
        if (exp & 1) result = matrix_multiply(result, base);
        base = matrix_multiply(base, base);
        exp >>= 1;
    }
    
    return result;
}

// ==============================================
// EXAMPLE USAGE
// ==============================================

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Number Theory Algorithms Demo ===" << endl;
    
    // Precompute primes up to 100
    sieve(100);
    cout << "First 10 primes: ";
    for (int i = 0; i < min(10, (int)primes.size()); i++) {
        cout << primes[i] << " ";
    }
    cout << endl;
    
    // Precompute factorials
    precompute_factorials(20);
    cout << "C(10, 3) = " << nCr(10, 3) << endl;
    
    // GCD and LCM
    cout << "gcd(48, 18) = " << gcd(48, 18) << endl;
    cout << "lcm(48, 18) = " << lcm(48, 18) << endl;
    
    // Modular arithmetic
    cout << "2^10 mod 1000007 = " << mod_pow(2, 10, 1000007) << endl;
    cout << "Inverse of 3 mod 7 = " << mod_inverse(3, 7) << endl;
    
    // Euler's totient function
    cout << "phi(12) = " << phi(12) << endl;
    
    // Prime factorization
    auto factors = factorize(60);
    cout << "Prime factorization of 60: ";
    for (auto& f : factors) {
        cout << f.first << "^" << f.second << " ";
    }
    cout << endl;
    
    // Divisors
    auto divs = get_divisors(12);
    cout << "Divisors of 12: ";
    for (long long d : divs) {
        cout << d << " ";
    }
    cout << endl;
    
    // Fibonacci using matrix exponentiation
    auto fib_10 = fib_matrix(10);
    cout << "Fibonacci(10) = " << fib_10.first << endl;
    
    // Catalan numbers
    auto cat = catalan(5);
    cout << "First 6 Catalan numbers: ";
    for (int i = 0; i <= 5; i++) {
        cout << cat[i] << " ";
    }
    cout << endl;
    
    return 0;
}
