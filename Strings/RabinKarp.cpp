#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cstdio>
#include <cstring>
#include <queue>
#include <cstdlib>
#include <algorithm>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cmath>
#include <bitset>
#include <stack>
#include <math.h>
using namespace std;
#define ll long long
#define int long long
#define endl "\n"
#define read(a) for(auto &i: a) cin>>i
#define write(a) for(auto &i: a) cout<<i<<" "
#define SafanMan ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(0);
void rabinKarp(string& pat, string& txt,int d, int q)
{
    int M = pat.size();
    int N = txt.size();
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;

    // The value of h would be "pow(d, M-1)%q"
    for (int i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of pattern and first
    // window of text
    for (int i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // Slide the pattern over text one by one
    for (int i = 0; i <= N - M; i++) {
        bool fo = true;
        if (p == t) {
            for (int j = 0; j < M; j++) {
                if (txt[i + j] != pat[j]) {
                    fo = false;
                    break;
                }
            }
            if (fo)
                cout << "Pattern found at index " << i
                << endl;
        }


        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;
            if (t < 0)
                t = (t + q);
        }
    }
}
void solve() {
    string s, t;
    cin >> s >> t;
    rabinKarp(t, s, 10, 13);
}

signed main() {
    SafanMan
        int t{ 1 };
    //  cin >> t;
    while (t--)
    {
        solve();
    }
}