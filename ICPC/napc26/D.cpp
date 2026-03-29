/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-20
 * Contest: 
 * Problem: D
**/

#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

const int MAX_N = 1e5 + 1;
const ll MOD = 1e9 + 7;

struct DSU {
    vi parents, sizes;

    DSU(int size) : parents(size), sizes(size, 1) {
        rep(i, 0, size) {
            parents[i] = i;
        }
    }

    int find(int x) {
        return (parents[x] == x ? x : (parents[x] = find(parents[x])));
    }

    bool unite(int a, int b) {
        int pa = find(a), pb = find(b);
        if (pa == pb) return false;
        if (sizes[pa] > sizes[pb]) {
            swap(pa, pb);
        }

        sizes[pb] += sizes[pa];
        parents[pa] = pb;
        return true;
    }
};

void solve(){
    int n, m, k; cin >> n >> m >> k;

    DSU dsu(n);
    vector<array<int, 4>> other;
    vector<pii> add;
    vi idx;

    int e = 0;

    rep(i, 0, m) {
        int a, b; cin >> a >> b;

        --a; --b;

        int w; cin >> w;
        if (w == 0) {
            if (dsu.unite(a, b)) {
                idx.pb(i);
                e++;
            }
        } else {
            other.pb({w, a, b, i});
        }
    }

    int used = 0;
    ll ans = 0;

    sort(all(other));

    rep(i, 0, sz(other)) {
        if (e >= n - 1 - k) break;
        auto [w, a, b, j] = other[i];
        if (dsu.find(a) == dsu.find(b)) continue;
        dsu.unite(a, b);
        ans += w;
        e++;
        idx.pb(j);
    }

    rep(i, 1, n) {
        if (used >= k) break;
        if (dsu.find(i - 1) != dsu.find(i)) {
            add.pb({i - 1, i});
            dsu.unite(i - 1, i);
            e++;
            ans++;
            used++;
        }
    }

    cout << sz(add) << endl;

    for (pii ed : add) {
        cout << ed.first + 1 << " " << ed.second + 1 << endl;
    }

    cout << ans << endl;

    for (int j : idx) {
        cout << j + 1 << " ";
    }

    rep(i, 0, sz(add)) {
        cout << m + 1 + i << " ";
    }
    cout << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc;
    cin >> tc;
    for (int t = 1; t <= tc; ++t){
        // cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}