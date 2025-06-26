#include <iostream>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>
// ordered_set is a set that supports order statistics
// It allows you to find the index of element O(log n) and insert in O(log n) time

int main() {
    ordered_set s;
    for (int i = 5; i >= 0; i--) {
        int x = rand() % 10;
        s.insert(x);
        cout << "Inserted: " << x <<" at idx: "<<s.order_of_key(x)<< endl;
    }
}