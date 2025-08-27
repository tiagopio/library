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
    
    struct node {
        long long val;        
    };
    
    // neutral element of operation
    const node INF = {0};
    
    int N;
    vector<node> segtree;
    Seg(int n, bool flag = false) : N(n), segtree(n << 2) {
        if (flag) build(1, 0, N - 1);
    }

    node merge(node x, node y) {
        return { x.val + y.val };
    }

    node build(int p, int l, int r) {
        if (l == r) return segtree[p] = { a[l] };
        int m = (l + r) >> 1;
        return segtree[p] = merge(build(left(p), l, m), build(right(p), m + 1, r));
    }

    int query(int l, int r) { return query(l, r, 1, 0, N - 1).val; }
    node query(int a, int b, int p, int l, int r) {
        if (b < l or r < a) return INF;
        if (a <= l and r <= b) return segtree[p];
        int m = (l + r) >> 1;
        return merge(query(a, b, left(p), l, m), query(a, b, right(p), m + 1, r));
    }

    node update(int i, int x) { return update(i, x, 1, 0, N - 1); }
    node update(int i, int x, int p, int l, int r) {
        if (i < l or r < i) return segtree[p];
        if (l == r) return segtree[p] = { x };
        int m = (l + r) >> 1;
        return segtree[p] = merge(update(i, x, left(p), l, m), update(i, x, right(p), m + 1, r));
    }
};
