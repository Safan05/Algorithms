   #include <vector>
#include <iostream>
#include <map>
#include <cmath>
using namespace std;
#define read(a) for(auto &i: a) cin>>i
#define write(a) for(auto &i: a) cout<<i<<" "
#define SafanMan ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
// my competitive programming journey is dedicated to my love *******
int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<int> scanline(n+1,0);
    read(a);
    for (int i = 0; i < q; i++) {
        int l, r,val;
        cin >> l >> r>>val;
        l--;
        r--;
        scanline[l] += val;
        scanline[r+1] -= val;
    }
    for (int i = 1; i < n; i++)
        scanline[i] += scanline[i - 1];
    for (int i = 0; i < n; i++)
        a[i] += scanline[i];
    write(a);
}