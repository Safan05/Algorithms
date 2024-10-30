#include <iostream>
#include <map>
#include <cmath>
using namespace std;

map<int, int> primeFactorization(int n) {
    map<int, int> factors;

    // Check for factor of 2
    while (n % 2 == 0) {
        factors[2]++;
        n /= 2;
    }

    // Check for odd factors from 3 to sqrt(n)
    for (int i = 3; i <= sqrt(n); i += 2) {
        while (n % i == 0) {
            factors[i]++;
            n /= i;
        }
    }

    // If n is still greater than 2, then n itself is a prime factor
    if (n > 2) {
        factors[n]++;
    }

    return factors;
}