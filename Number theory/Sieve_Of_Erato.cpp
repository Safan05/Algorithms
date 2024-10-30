#include <vector>
#include <iostream>
#include <map>
#include <cmath>
using namespace std;
const int N = 1e6;
vector<bool> sieve(N, 1);
void init_Sieve() {
    sieve[0] = 0;
    sieve[1] = 0;
    for (int i = 2; i < N; i++) {
        if (sieve[i]) {
            for (int j = i + i; j < N; j += i)
                sieve[j] = 0;
        }
    }
}
/*
Supposing all numbers from 2 to N are primes 
then getting to the smallest prime and make all it's multiples not prime and so all
it's place complexity is O(N) , time complexity is  O(N*lg(lg(N)))
 */