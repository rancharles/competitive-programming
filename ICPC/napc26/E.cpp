/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-20
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
const ll MOD = 998244353;

void solve(){
    int n; ll k; cin >> n >> k;

    vector<pii> events;
    rep(i, 0, n) {
        int a, b; cin >> a >> b;
        events.pb({a, 0});
        events.pb({b, 1});
    }

    sort(all(events));

    ll curr = 0;
    ll ans = 1;

    rep(i, 0, 2 * n) {
        auto [x, c] = events[i];
        if (c == 0) {
            curr++;

            if (curr > k) {
                cout << 0 << '\n';
                return;
            }

            ans *= k - curr + 1;
            ans %= MOD;
        } else {
            curr--;
        }
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