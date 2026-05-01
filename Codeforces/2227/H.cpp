/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-04-30
 * Contest: 
 * Problem: H
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
    vector<vi> adj(n);
    rep(i, 0, n - 1) {
        int a, b; cin >> a >> b;
        --a; --b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    int root = 0;
    rep(i, 0, n) {
        if (sz(adj[i]) > 1) {
            root = i;
            break;
        }
    }

    ll ans = 0;
    int leaf = 0;
    vi par(n, -1);
    vi dp(n, 0);
    function<int(int)> dfs;
    dfs = [&](int node) {
        int add = 0;
        for (int x : adj[node]) {
            if (x != par[node]) {
                par[x] = node;
                add += dfs(x);
            } 
        }

        if (sz(adj[node]) == 1) {
            leaf++;
            dp[node] = 1;
        } else {
            dp[node] = add % 2;
        }

        ans += dp[node];
        return dp[node];
    };

    dfs(root);

    if (leaf % 2 == 1) {
        int mn = INT_MAX;
        rep(i, 0, n) {
            int node = i;
            int curr = 0;
            if (sz(adj[node]) != 1) continue;
            while (node != -1) {
                if (dp[node] == 1) {
                    curr--;
                } else {
                    curr++;
                }

                node = par[node];
            }

            mn = min(mn, curr);
        }

        ans += mn;
    }

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