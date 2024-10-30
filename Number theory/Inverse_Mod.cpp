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

// uses little fermat theorem that a^-1 mod M == a^(M-1) mod M ans use modular exponential function which takes time of O(lg N)
