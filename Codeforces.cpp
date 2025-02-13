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
#include <climits>
#include <math.h>
using namespace std;
#define ll long long
#define int long long
#define endl "\n"
#define read(a) for(auto &i: a) cin>>i
#define write(a) for(auto &i: a) cout<<i<<" "
#define SafanMan ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(0);
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
bool notunique(int y) {
    int a = y % 10;
    y /= 10;
    int b = y % 10;
    y /= 10;
    int c = y % 10;
    y /= 10;
    if (y != c && c != b && b != a && c!=a && y!=b && y!=a)
        return false;
    return true;
}
void solve() {
    cout<<"Hello World !\n";
}

signed main() {
    // freopen("mex.in", "r", stdin);
// freopen("mex.in", "r", stdout);
    SafanMan
        int t{ 1 };
    //  cin >> t;
    while (t--)
    {
        solve();
    }
}
/*
5
9
0 1 5
0 2 3
1 3 6
1 2 2
2 4 4
2 5 2
2 3 7
3 4 -1
4 5 -2
*/