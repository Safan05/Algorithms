#include <iostream>
using namespace std;

int modExp(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int modInverse(int a, int mod) {
    return modExp(a, mod - 2, mod);
}
// Precompute fact and invFact
void precompute() {
    fact[0] = 1;
    for (int i = 1; i <= N; ++i)
        fact[i] = fact[i - 1] * i % MOD;

    invFact[N] = modInverse(fact[N], MOD); // Fermat's inverse
    for (int i = N - 1; i >= 0; --i)
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
}

// Calculate nCr % MOD
long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

// uses little fermat theorem that a^-1 mod M == a^(M-1) mod M ans use modular exponential function which takes time of O(lg N)
