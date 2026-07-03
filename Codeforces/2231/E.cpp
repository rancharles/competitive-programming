/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-07-01
 * Contest: 
 * Problem: E
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

void solve(){
    int n, d; cin >> n >> d;

    vector<vi> adj(n);
    rep(i, 0, n - 1) {
        int a, b; cin >> a >> b;
        --a; --b;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    ll ans = 0;

    function<void(int, int, int, vi&)> getDist;
    getDist = [&](int node, int par, int curr, vi& dists) {
        dists.pb(curr);
        for (int x : adj[node]) {
            if (x == par) continue;
            getDist(x, node, curr + 1, dists);
        }
    };

    ll cc = 0;
    vi depth(n, 0);
    function<void(int, int)> dfs;
    dfs = [&](int node, int par) {
        // if (depth[node] >= d - 1) {
        //     ans++;
        // }

        for (int x : adj[node]) {
            if (x == par) continue;
            depth[x] = depth[node] + 1;
            dfs(x, node);
        }

        int k = sz(adj[node]);
        int mx = 0;
        vector<vl> ld;
        for (int x : adj[node]) {
            vi dists;
            getDist(x, node, 1, dists);
            int m = *max_element(all(dists));
            mx = max(mx, m);
            vl ds(m + 1, 0);
            for (int dist : dists) {
                ds[dist]++;
            }

            ld.pb(ds);
        }

        vl totd(mx + 1, 0);
        rep(i, 0, k) {
            rep(j, 1, sz(ld[i])) {
                totd[j] += ld[i][j];
            }
        }

        ll cnt = 0;
        rep(i, 0, k) {
            rep(j, 0, k) {
                if (i == j) continue;
                rep(a, 1, sz(ld[i])) {
                    rep(b, 1, sz(ld[j])) {
                        int want = d - a - b - 1;
                        if (want < 0) continue;
                        if (want > mx) continue;

                        if (want == 0) {
                            cc += ld[i][a] * ld[j][b];
                            continue;
                        }

                        ll iwant = 0, jwant = 0;
                        if (want < sz(ld[i])) {
                            iwant += ld[i][want];
                        }
                        if (want < sz(ld[j])) {
                            jwant += ld[j][want];
                        }

                        cnt += ld[i][a] * ld[j][b] * (totd[want] - iwant - jwant);
                    }
                }
            }
        }

        ans += cnt/6;
    };

    dfs(0, -1);

    cc /= 2;
    cc /= d - 2;

    ans += cc;

    cout << ans << endl;
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