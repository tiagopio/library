/*
    Lowest Commom Ancestor
    1-indexed
    dfs: O(N*log(N))
    check: O(1) - true if u is an ancestor o v
    lca: O(log(N))
    dist: O(log(N)) - distance from u to v
*/

struct LCA {
    int N, LOG, timer, root;
    vector<int> tin, tout, d;
    vector<vector<int>> &graph, up;

    LCA(int n, vector<vector<int>> &graph, int root = 1) : N(n), graph(graph), root(root) {
        tin.resize(N + 1), tout.resize(N + 1);
        d.resize(N + 1, 0);
        timer = 0;
        LOG = ceil(log2(N));
        up.resize(N + 1, vector<int>(LOG + 1));
        dfs(root, root);
    }

    void dfs(int v, int p) {
        tin[v] = ++timer;
        up[v][0] = p;
        
        for (int i = 1; i < LOG; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }

        for (auto u : graph[v]) {
            if (u != p) {
                d[u] = d[v] + 1;
                dfs(u, v);
            }
        }
        tout[v] = ++timer;
    }

    bool check(int u, int v) {
        return tin[u] <= tin[v] and tout[u] >= tout[v];
    }

    int lca(int u, int v) {
        if (check(u, v)) return u;
        if (check(v, u)) return v;

        for (int i = LOG - 1; i >= 0; i--) {
            if (!check(up[u][i], v)) {
                u = up[u][i];
            }
        }
        return up[u][0];
    }

    int dist(int u, int v) {
        return d[u] + d[v] - 2 * d[lca(u, v)];
    }
};
