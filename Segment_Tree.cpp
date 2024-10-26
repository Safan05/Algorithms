struct Node {
private:
    int val;
public:
    Node(int v = 0, int O = 0, int C = 0) {
        val = v;
    }
    void setVal(int v = 0) {
        val = v;
    }
    Node merge(Node n1, Node n2) {
        Node x;
        x.val = n1.val + n2.val;
        return x;
    }
    int Get() {
        return val;
    }
};
struct SegmentTree {
#define mid (r+l)/2
#define L node*2+1
#define R node*2+2
private:
    vector<Node> seg;
    int size;
    void build(int l, int r, int node, vector<int>& a) {
        if (l == r) {
            if (l < a.size()) {
                seg[node].setVal(a[l]);
            }
            return;
        }
        build(l, mid, L, a);
        build(mid + 1, r, R, a);
        Node x;
        seg[node] = x.merge(seg[L], seg[R]);
    }
    Node query(int l, int r, int node, int ql, int qr) {
        if (l > qr || r < ql)
            return 0;
        if (l >= ql && r <= qr)
            return seg[node];
        Node left = query(l, mid, L, ql, qr);
        Node right = query(mid + 1, r, R, ql, qr);
        return left.merge(left, right);
    }
    void update(int idx, int val, int node,int l,int r) {
        if (l == r) {
            seg[node].setVal(val);
            return;
        }
        if (idx <= mid)
            update(idx, val, L, l, mid);
        else 
            update(idx, val, R, mid+1, r);
        seg[node] = seg[node].merge(seg[L], seg[R]);
    }
public:
    SegmentTree(vector<int>& v) {
        int n = v.size();
        size = 1;
        while (size < n)
            size *= 2;
        seg = vector<Node>(2 * size);
        build(0, size - 1, 0, v);
    }
    int query(int l, int r) {
        return query(0, size - 1, 0, l, r).Get();
    }
    void update(int idx, int val) {
        update(idx, val,0,0,size-1);
    }
#undef mid
#undef L
#undef R
};

// changed by changing the question