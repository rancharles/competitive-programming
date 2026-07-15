/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-07-14
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

void solve(){
    int n; cin >> n;

    vi par(n);
    vector<vi> children(n);
    rep(i, 0, n - 1) {
        int p; cin >> p;
        --p;
        par[i + 1] = p;
        children[p].pb(i + 1);
    }

    rep(i, 0, n) {
        sort(all(children[i]));
    }

    vi val(n);
    rep(i, 0, n) {
        cin >> val[i];
    }

    vi mn(n, INT_MAX), mx(n, INT_MIN);

    bool no = false;
    function<void(int)> dfs;
    dfs = [&](int node) {
        if (val[node] != 0) {
            mn[node] = val[node];
            mx[node] = val[node];
        }
        for (int x : children[node]) {
            dfs(x);
            if (no) return;
            mn[node] = min(mn[node], mn[x]);
            mx[node] = max(mx[node], mx[x]);
        }

        int lst;
        int m = sz(children[node]);
        int bad = 0;
        rep(i, 0, m) {
            int j = (i + 1) % m;
            if (mx[children[node][i]] >= mn[children[node][j]]) {
                bad++;
            }
        }

        if (bad > 1) {
            no = true;
        }
    };

    dfs(0);
    if (no) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }
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