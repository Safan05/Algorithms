#include <bits/stdc++.h>
using namespace std;

// ================================ SEGMENT TREE ================================
template<typename T>
class SegmentTree {
    vector<T> tree;
    int n;
    T identity;
    function<T(T, T)> combine;

public:
    SegmentTree(vector<T>& arr, T id, function<T(T, T)> op)
        : identity(id), combine(op) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }

    void build(vector<T>& arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = arr[tl];
        }
        else {
            int tm = (tl + tr) / 2;
            build(arr, 2 * v, tl, tm);
            build(arr, 2 * v + 1, tm + 1, tr);
            tree[v] = combine(tree[2 * v], tree[2 * v + 1]);
        }
    }

    void update(int v, int tl, int tr, int pos, T val) {
        if (tl == tr) {
            tree[v] = val;
        }
        else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(2 * v, tl, tm, pos, val);
            else
                update(2 * v + 1, tm + 1, tr, pos, val);
            tree[v] = combine(tree[2 * v], tree[2 * v + 1]);
        }
    }

    T query(int v, int tl, int tr, int l, int r) {
        if (l > r) return identity;
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        return combine(query(2 * v, tl, tm, l, min(r, tm)),
            query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r));
    }

    void update(int pos, T val) { update(1, 0, n - 1, pos, val); }
    T query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

// ================================ FENWICK TREE (BIT) ================================
template<typename T>
class FenwickTree {
    vector<T> bit;
    int n;

public:
    FenwickTree(int size) : n(size) {
        bit.assign(n + 1, 0);
    }

    FenwickTree(vector<T>& arr) : FenwickTree(arr.size()) {
        for (int i = 0; i < arr.size(); i++)
            update(i, arr[i]);
    }

    void update(int i, T delta) {
        for (++i; i <= n; i += i & -i)
            bit[i] += delta;
    }

    T query(int i) {
        T sum = 0;
        for (++i; i > 0; i -= i & -i)
            sum += bit[i];
        return sum;
    }

    T query(int l, int r) {
        return query(r) - query(l - 1);
    }

    // Find first index with prefix sum >= x
    int lower_bound(T x) {
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1) {
            if (pos + pw <= n && bit[pos + pw] < x) {
                pos += pw;
                x -= bit[pos];
            }
        }
        return pos;
    }
};

// ================================ DISJOINT SET UNION (DSU) ================================
class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) : parent(n), rank(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;

        if (rank[x] < rank[y]) swap(x, y);
        parent[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

// ================================ SPARSE TABLE ================================
template<typename T>
class SparseTable {
    vector<vector<T>> st;
    vector<int> lg;
    function<T(T, T)> combine;

public:
    SparseTable(vector<T>& arr, function<T(T, T)> op) : combine(op) {
        int n = arr.size();
        int k = 32 - __builtin_clz(n);
        st.assign(k, vector<T>(n));
        lg.assign(n + 1, 0);

        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;

        for (int i = 0; i < n; i++)
            st[0][i] = arr[i];

        for (int j = 1; j < k; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = combine(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T query(int l, int r) {
        int j = lg[r - l + 1];
        return combine(st[j][l], st[j][r - (1 << j) + 1]);
    }
};