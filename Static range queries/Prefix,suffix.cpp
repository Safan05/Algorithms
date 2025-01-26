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
    SafanMan
    int n;
    cin>>n;
    vector<int> a(n);
    read(a);
    // 1) prefix sum
    vector<int> pref(n,0);
    pref[0]=a[0];
    for(int i=1;i<n;i++){
        pref[i]=pref[i-1]+a[i];
    }
    // 2) suffix sum
    vector<int> suff(n,0);
    suff[n-1]=a[n-1];
    for(int i=n-2;i>=0;i--){
        suff[i]=suff[i+1]+a[i];
    }
    // 3) freq array , can be map or vector
    map<int,int> freq;
    for(int i=0;i<n;i++)
        freq[a[i]]++;
    return 0;
}