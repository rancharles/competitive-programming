/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-07-12
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
const int mx = 18;

vector<vl> best(1 << (mx - 1) + 2, vl(mx, 1e18));

ll moves(ll a) {
    ll move = 0;
    while (a != 0) {
        if (a % 2 == 0) {
            a /= 2;
        } else {
            a--;
        }

        move++;
    }
    return move;
};

void solve(){
    int n; cin >> n;

    ll ans = LLONG_MAX;
    vl arr(n);
    rep(i, 0, n) cin >> arr[i];

    rep(p, 0, mx) {
        ll pw = 1LL << p;
        ll cand = 0;
        ll mn = LLONG_MAX;
        rep(i, 0, n) {
            ll a = arr[i];
            cand += best[a][p] - a;
        }

        cand -= (ll)(n - 1) * p;
        ans = min(ans, cand);
    }

    cout << ans << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    for (int a = sz(best) - 2; a >= 1; a--) {
        ll c = a + moves(a);
        ll aa = a;
        rep(j, 0, mx) {
            best[a][j] = best[a + 1][j];
        }
        rep(j, 0, mx) {
            best[a][j] = min(best[a][j], c);
            if (aa % 2 != 0) break;
            aa /= 2;
        }
    }

    int tc;
    cin >> tc;
    for (int t = 1; t <= tc; ++t){
        // cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}