/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-04-04
 * Contest: 
 * Problem: G
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
const ll MOD = 676767677;

void solve(){
    int n, m; cin >> n >> m;

    vector<vi> times(m);
    vi b(n);
    rep(i, 0, n) {
        cin >> b[i];
        times[b[i]].pb(i);
    }

    vi sat(n, m);
    ll ans = 1;
    int p = 0;
    int seated = 0;
    for (int idx : times[0]) {
        sat[idx] = 0;
        seated++;   
    }
    rep(t, 1, m) {
        int ns = 0;
        for (int idx : times[t]) {
            bool good = false;
            int mnSat = m;
            if (idx != 0 && sat[idx - 1] != m) {
                good = true;
                mnSat = min(mnSat, sat[idx - 1]);
            }
            if (idx != n - 1 && sat[idx + 1] != m) {
                good = true;
                mnSat = min(mnSat, sat[idx + 1]);
            }

            if (!good) {
                cout << 0 << "\n";
                return;
            }

            ns++;
            if (mnSat == t - 1) {
                ans *= seated;
                ans %= MOD;
            } else {
                ans *= seated - p;
                ans %= MOD;
            }
        }

        for (int idx : times[t]) {
            sat[idx] = t;
        }

        p = seated;
        seated += ns;
    }

    cout << ans << "\n";
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