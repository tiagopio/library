/*
    Disjoint Set Union
    1-indexed
    find: O(a(n)) ~= O(1) amortized
    unite: O(a(n)) ~= O(1) amortized
    max_size: O(1)
*/

struct DSU { 
    vector<int> parent, size;
    // largest component size, number of components
    int mx_size, comps;
    DSU(int n) : parent(n + 1), size(n + 1, 1), mx_size(-1), comps(n) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int u) {
        return parent[u] = (parent[u] == u ? u : find(parent[u]));
    }

    void unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (size[u] > size[v]) swap(u, v);
        parent[u] = v, size[v] += size[u];
        mx_size = max(mx_size, size[v]);
    }

    int components() { return comps; }
    int max_size() { return mx_size; }
};
