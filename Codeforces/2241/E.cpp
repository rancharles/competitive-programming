/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-06-30
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

const int MAX_N = 1e6 + 1;
const ll MOD = 1e9 + 7;

vector<bool> sq(MAX_N, false);

void solve(){
    int n; cin >> n;
    vi arr(n);
    rep(i, 0, n) cin >> arr[i];

    vector<vi> adj(n);
    rep(i, 0, n - 1) {
        int a, b; cin >> a >> b;

        --a; --b;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    ll ans = 0;

    function<int(int, int)> dfs;
    dfs = [&](int node, int par) {
        ll tot = 1;
        vl sizes;
        for (int x : adj[node]) {
            if (x == par) continue;
            int s = dfs(x, node);
            tot += s;
            sizes.pb(s);
        }

        if (sq[arr[node]]) {
            ans += (ll)(n - tot) * (tot - 1);

            ll c = 0, sqsum = 0;
            c += (tot - 1) * (tot - 1);

            for (ll s : sizes) {
                sqsum += s * s;
            }

            c -= sqsum;

            c /= 2;
            c *= (n - tot + 1);
            ans += c;

            c = (tot - 1) * (tot - 1) * (tot - 1);
            for (ll s : sizes) {
                c += s * s * s * 2;
            }

            c -= sqsum * (tot - 1) * 3;
            c /= 6;
        
            ans += c;
        }

        return tot;
    };

    dfs(0, -1);

    cout << ans << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    rep(i, 1, 1e3 + 1) {
        sq[i * i] = true;
    }

    int tc;
    cin >> tc;
    for (int t = 1; t <= tc; ++t){
        // cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}