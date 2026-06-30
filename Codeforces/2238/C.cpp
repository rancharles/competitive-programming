/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-06-29
 * Contest: 
 * Problem: C
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

    vi par(n, -1);
    vector<vi> children(n);
    rep(i, 0, n - 1) {
        int p; cin >> p;
        --p;

        par[i + 1] = p;
        children[p].pb(i + 1);
    }

    function<pair<ll, ll>(int)> dfs;
    dfs = [&](int node) {
        ll ans = 1;
        ll d = 0;
        vl arr;
        for (int x : children[node]) {
            auto [k, dd] = dfs(x);
            d = max(d, dd);
            ans += k;
            arr.pb(dd);
        }
        sort(all(arr));
        ll sb = 0;
        if (sz(arr) > 1) {
            sb = arr[sz(arr) - 2];
        }
        
        return pair<ll, ll>{ans + sb, d + 1};
    };

    cout << dfs(0).first << endl;
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