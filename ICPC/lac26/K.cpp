/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-15
 * Contest: 
 * Problem: K
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

    using T = array<int, 2>;
    vector<T> cats(n);
    rep(i, 0, n) {
        cin >> cats[i][0];
        cin >> cats[i][1];
    }

    ll curr = 0;
    vl len(n, 0);
    vector<T> pos;

    ll ans = 0;
    vector<bool> visited(2 * n, false);
    function<void(int, int)> dfs;
    dfs = [&](int ni, int par) {
        int node = ni/2;
        int v = ni % 2;

        rep(x, 0, 2 * n) {
            if (x == par) continue;
            int xnode = x/2;
            int xv = ni % 2;
            int nv = v ^ 1;
            if (xv != nv) continue;
            
            if (visited[x]) {
                ans = max(ans, curr - len[x]);
                continue;
            }

            if (sz(pos) == 0) {
                pos.pb(cats[]);
            }

            curr += 
            len.pb(curr);
            dfs(x, ni);
        }
    };

    rep(i, 0, 2 * n) {
        if (!visited[i]) {
            dfs(i, -1);
        }
    }

    cout << ans << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}