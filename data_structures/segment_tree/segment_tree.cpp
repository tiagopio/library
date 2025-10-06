/*
    Segment Tree
    0-indexed vector
    build: O(4*N)
    query: O(4*log(N))
    update: O(4*log(N))
*/

struct Seg {
    // left and right child of p
    inline int left(int p) { return (p << 1); }
    inline int right(int p) { return (left(p) | 1); }
    
    // neutral element of operation
    const int INF = 0;
    
    int n;
    vector<int> &a, segtree;
    Seg(int N, vector<int> A, bool flag) : n(N), a(A), segtree(N << 2) {
        build(1, 0, n - 1);
    }

    int merge(int x, int y) {
        return x + y;
    }

    int build(int p, int l, int r) {
        if (l == r) return segtree[p] = a[l];
        int m = (l + r) >> 1;
        return segtree[p] = merge(build(left(p), l, m), build(right(p), m + 1, r));
    }

    int query(int a, int b) { return query(a, b, 1, 0, n - 1); }
    int query(int a, int b, int p, int l, int r) {
        if (b < l or r < a) return INF;
        if (a <= l and r <= b) return segtree[p];
        int m = (l + r) >> 1;
        return merge(query(a, b, left(p), l, m), query(a, b, right(p), m + 1, r));
    }

    int update(int i, int x) { return update(i, x, 1, 0, n - 1); }
    int update(int i, int x, int p, int l, int r) {
        if (i < l or r < i) return segtree[p];
        if (l == r) return segtree[p] = { x };
        int m = (l + r) >> 1;
        return segtree[p] = merge(update(i, x, left(p), l, m), update(i, x, right(p), m + 1, r));
    }
};