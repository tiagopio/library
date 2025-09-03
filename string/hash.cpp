/*
    String Hash - Polynomial rolling hash
    build: O(N)
    init: O(N)
    get_hash: O(1)
    reference: github.com/gustav0leal
*/ 

const int N = 200010; // string size;
const uint64_t p = 33, mod = 1000000007, p2 = 73, mod2 = 1000000009;
uint64_t ppow[N], ppow2[N];

void build()
{
    ppow[0] = 1;
    ppow2[0] = 1;
    for (int i = 1; i < N; i++) {
        ppow[i] = (ppow[i-1] * p) % mod;
        ppow2[i] = (ppow2[i-1] * p2) % mod2;
    }
}
struct Hash {
    vector<pair<uint64_t, uint64_t>> h;
 
    Hash () {}
 
    void init(string &s) {
        h.resize(s.size() + 2);
        h[0] = {5389ULL, 5389ULL};
        for (size_t i = 0; i < s.size(); i++) {
            int code = s[i];
            h[i + 1].first = (h[i].first * p + code) % mod;
            h[i + 1].second = (h[i].second * p2 + code) % mod2;
        }
    }
 
    pair<uint64_t, uint64_t> get_hash(int i, int j) {
        pair<uint64_t, uint64_t> r;
        r.first = (h[j + 1].first - (h[i].first * ppow[j - i + 1]) % mod + mod) % mod;
        r.second = (h[j + 1].second - (h[i].second * ppow2[j - i + 1]) % mod2 + mod2) % mod2;
        return r;
    }
};