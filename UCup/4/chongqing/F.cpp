/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-29
 * Contest: 
 * Problem: F
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

const int INF = 1e8;

void solve(){
    int n; cin >> n;

    vector<vi> children(n);
    vi par(n, -1);
    rep(i, 1, n) {
        cin >> par[i];
        --par[i];

        children[par[i]].pb(i);
    }

    vi dp1(n, 0);
    vi dpr(n, 0);
    vi dp2(n, -INF);
    vi depth(n, 0);
    function<void(int)> dfs;
    dfs = [&](int node) {
        vector<pii> dps;
        vi dprs;
        for (int x : children[node]) {
            depth[x] = 1 + depth[node];
            dfs(x);
            dps.pb({dp1[x], x});
            if (dp1[x] != 0) {
                dprs.pb(dp1[x]);
            }
        }

        sort(all(dprs));
        if (sz(dprs) == 0) {
            dpr[node] = 0;
        } else {
            int mx = 1 + dprs[0];
            rep(i, 1, sz(dprs)) {
                int d = dprs[i];
                mx = 1 + max(d, 1 + mx);
            }

            dpr[node] = mx;
        }

        sort(all(dps));
        int m = sz(dps);
        if (m == 0) {
            dp1[node] = 0;
        } else {
            int mx = 1 + dps[0].first;
            rep(i, 1, m) {
                pii d = dps[i];
                mx = 1 + max(d.first, 1 + mx);
            }

            dp1[node] = mx;
        }

        multiset<int> lo;
        multiset<int> hi;
        for (int i = m - 1; i >= 1; i--) {
            int add = 1 + (m - 1 - i) * 2;
            hi.insert(add + dps[i].first);
        }
        rep(i, 0, m) {
            pii d = dps[i];
            if (m == 1) {
                dp2[d.second] = -INF;
                break;
            }

            int l = 0, h = 0;
            if (!lo.empty()) {
                l = *prev(lo.end());
            }
            if (!hi.empty()) {
                h = *prev(hi.end());
            }
            dp2[d.second] = max(l, h);

            int add = 1 + (m - 1 - i - 1) * 2;
            if (i != m - 1) {
                hi.erase(hi.find(add + dps[i + 1].first));
                lo.insert(add + d.first);
            }
        }
    };

    dfs(0);

    vi ans(n, -INF);
    vi up(n, -INF);
    function<void(int)> dfs2;
    dfs2 = [&](int node) {
        if (par[node] != -1) {
            up[node] = 1 + max(dp2[node], up[par[node]]);
        }

        bool down = false;
        for (int x : children[node]) {
            dfs2(x);
            if (sz(children[x]) != 0) {
                down = true;
            }
        }

        ans[node] = up[node];
        if (down) {
            ans[node] = max(ans[node], dpr[node]);
        }

        // ans[node] = max(dp1[node], up[node]);
    };

    dfs2(0);

    // rep(i, 0, n) {
    //     cout << dp1[i] << " ";
    // }
    // cout << endl;
    // rep(i, 0, n) {
    //     cout << dp2[i] << " ";
    // }
    // cout << endl;

    rep(i, 0, n) {
        int e = depth[i] + sz(children[i]);
        if (e == n - 1) {
            cout << 0 << " ";
            continue;
        }

        cout << ans[i] << " ";
    }

    cout << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; ++t){
        // cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}