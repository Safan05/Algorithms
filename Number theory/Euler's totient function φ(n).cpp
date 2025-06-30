#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to calculate GCD using Euclidean algorithm
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Method 1: Direct implementation - count numbers with gcd(i, n) = 1
int phi_direct(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (gcd(i, n) == 1) {
            count++;
        }
    }
    return count;
}

// Method 2: Optimized version using Euler's formula
int phi_optimized(int n) {
    if (n <= 0) return 0;
    
    int result = n;
    
    // Check for all prime factors
    for (int p = 2; p * p <= n; p++) {
        // If p is a prime factor
        if (n % p == 0) {
            // Remove all factors of p
            while (n % p == 0) {
                n /= p;
            }
            // Multiply result by (1 - 1/p)
            result -= result / p;
        }
    }
    
    // If n is still > 1, then it's a prime
    if (n > 1) {
        result -= result / n;
    }
    
    return result;
}

// Method 3: Sieve approach for multiple values (efficient for range calculations)
vector<int> phi_sieve(int maxN) {
    vector<int> phi(maxN + 1);
    
    // Initialize phi[i] = i
    for (int i = 0; i <= maxN; i++) {
        phi[i] = i;
    }
    
    // Apply Euler's formula using sieve
    for (int i = 2; i <= maxN; i++) {
        if (phi[i] == i) { // i is prime
            for (int j = i; j <= maxN; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
    
    return phi;
}

// Function to display numbers that are coprime to n
void show_coprimes(int n) {
    cout << "Numbers from 1 to " << n << " that are coprime to " << n << ": ";
    for (int i = 1; i <= n; i++) {
        if (gcd(i, n) == 1) {
            cout << i << " ";
        }
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter a positive integer n: ";
    cin >> n;
    
    if (n <= 0) {
        cout << "Please enter a positive integer." << endl;
        return 1;
    }
    
    cout << "\n=== Euler's Totient Function φ(" << n << ") ===" << endl;
    
    // Method 1: Direct counting
    int phi1 = phi_direct(n);
    cout << "φ(" << n << ") = " << phi1 << " (direct method)" << endl;
    
    // Method 2: Optimized formula
    int phi2 = phi_optimized(n);
    cout << "φ(" << n << ") = " << phi2 << " (optimized method)" << endl;
    
    // Show the actual coprime numbers
    show_coprimes(n);
    
    // Demonstrate sieve method for range 1 to n
    cout << "\n=== φ(i) for i = 1 to " << min(n, 20) << " ===" << endl;
    vector<int> phi_values = phi_sieve(min(n, 20));
    for (int i = 1; i <= min(n, 20); i++) {
        cout << "φ(" << i << ") = " << phi_values[i] << endl;
    }
    
    return 0;
}
