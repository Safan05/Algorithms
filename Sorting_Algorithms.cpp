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
#include <numeric>
#include <string>
#include <cmath>
#include <bitset>
#include <stack>
#include <math.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define forl(i,begin,end,add)	for(ll (i)=(begin);(i)<(end);(i)+=(add)) // i , i=? , i<? , i+=?
#define rforl(i,begin,end,sub)  for(ll (i)=(end);(i)>(begin);(i)-=(sub)) // i , i=? , i>? , i-=?
// CE_MOI
void Insertion_Sort(vector<int>&a) {
    for (int i = 1; i < a.size(); i++) {
        int j = i-1;
        int t = i;
        while (a[j] > a[t]) {
            int x = a[j];
            a[j] = a[t];
            a[t] = x;
            t--;
            j--;
            if (j < 0)
                break;
        }
    }
}
void Shell_Sort(vector<int>&a) {
    int gap = a.size() / 2;
    while (gap != 0) {
        for (int i = 0; i < a.size() ; i++) { 
                int j = i - gap; // index j to compare with the element within range = gap
                int t = i;
                if (j >= 0) // check at first the j isn't negative
                while (a[j] > a[t]) { // doing insertion sort with difference = gap
                    int x = a[j];
                    a[j] = a[t];
                    a[t] = x;
                    t-=gap;
                    j -= gap;
                    if (j < 0) // always check that j isn't negative
                        break;
                }
        }
        gap /= 2;
    }
}
void Selection_sort(vector<int>& a) {
    int min = INT_MAX,ptr;
    for (int i = 0; i < a.size(); i++) {
        min = INT_MAX;
        for (int j = i; j < a.size(); j++) { // finding the min in the remaining part of array
            if (a[j] < min) {
                min = a[j];
                ptr = j;
            }
        }
        int x = a[i];
        a[i] = a[ptr];
        a[ptr] = x;
    }
}
void Max_Heapify(vector<int>& a, int i=0) { 
    if (i >= a.size())
        return;
    int l=2*i+1, r=2*i+2;
    int largest = i; // index will be to the largest one of parent and the 2 childrens
    if (l < a.size()) // check that the left child exists
        if (a[l] > a[largest])
            largest = l;
    if (r < a.size()) // check that the right child exists
        if (a[r] > a[largest])
            largest = r;
    if (largest != i) { // if the largest is one of the children swap them then do the same function with the replaced one
        int x = a[largest];
        a[largest] = a[i];
        a[i] = x;
        Max_Heapify(a, largest);
    }
}
void Build_MaxHeap(vector<int>& a) {
    for (int i = a.size()/2-1; i >= 0; i--) // repeating Max_Heapify to make sure that the largest is on the top.
        Max_Heapify(a,i);
}
void Heap_Sort(vector<int>& a) {
    vector<int>b=a;
    Build_MaxHeap(b);
    for (int i = a.size()-1 ; i >=0; i--) {
        a[i] = b[0]; // putting the largest element as the last element is a.
        swap(b[0], b[i]); // putting the largest element as the last element so we can pop it.
        b.pop_back(); // removing the largest element from b after putting it as the last on a.
        Max_Heapify(b, 0); // heapify again to put the upcoming largest element on top. 
    }
}
void Bubble_Sort(vector<int>& a) {
    for(int i=1;i<a.size();i++) // repeating the operation n-1 times to check that it is sorted
        for (int j = 0; j < a.size()-1; j++) {
            if (a[j] > a[j + 1]) // checking it's element with it's neighboring element.
                swap(a[j], a[j + 1]);
        }
}
//Quick Sort Begin
int Partition(vector<int>& a,int l,int r) {
    int k=l-1; 
    for (int i = l; i < r; i++) {
        if (a[i] < a[r]) {
            k += 1;
            swap(a[k], a[i]); // if the current element is smaller than the pivot so replace it with first greater element so we put the smaller on left , greater on right
        }
    }
    swap(a[k + 1], a[r]); // putting the pivot in it's right place
    return k + 1; // returning the position of the pivot
}
void Quick_Sort(vector<int>& a,int l,int r) {
    if (l < r) {
        int pivot = Partition(a, l, r);
        Quick_Sort(a, l, pivot - 1);
        Quick_Sort(a, pivot + 1,r);
    }
    else
        return;
}
//Quick Sort End
///Merge Sort begin
void Merge(vector<int>& a, int l, int mid, int r) {
    vector<int>N(mid - l + 2);
    vector<int>M(r - mid+1);
    int j = 0;
    for (int i = l; i <= mid; i++) { //putting the left divided part in an array N
        N[j] = a[i]; 
        j++;
    }
    j = 0;
    for (int i = mid+1; i <= r; i++) { // putting the right divided part in an array M
        M[j] = a[i];
        j++;
    }
    M[M.size() - 1] = INT_MAX; // not to put a check if the array has been finished
    N[N.size() - 1] = INT_MAX;
    int j1 = 0, j2 = 0;
    for (int i = l; i <= r; i++) { //merging N and M , note both N and M are sorted
        if (N[j1] <= M[j2]) {
            a[i] = N[j1];
            j1++;
        }
        else {
            a[i] = M[j2];
            j2++;
        }
    }
}
void Merge_Sort(vector<int>& a, int l, int r) {
    if (l >= r)
        return;
    int mid = (l + r) / 2;
    Merge_Sort(a, l, mid); // dividing from left
    Merge_Sort(a, mid+ 1, r); // dividing from right
    Merge(a, l, mid, r); // merge the left and right divided (conquer)
}
//Merge Sort End
//Abdallah_Safan
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(0);
    vector<int> a1 { 9,4,6,3,1 ,5,3,7,2,54,2,7};
    Shell_Sort(a1);
   // Merge_Sort(a1,0,a1.size()-1);
    for (int i = 0; i < a1.size(); i++)
        cout << a1[i]<<" ";
    return 0;
}