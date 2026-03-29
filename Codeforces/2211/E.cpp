/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-28
 * Contest: 
 * Problem: E
**/

#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ll = long long;
using lll = __int128;
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

    using T = pair<ll, ll>;
    vector<T> dp(n);

    for (int i = n - 1; i >= 0; i--) {
        ll a; cin >> a;
        int k; cin >> k;
        vi children(k);
        rep(j, 0, k) {
            cin >> children[j];
            --children[j];
        }

        int ans = 0;
        lll good = 1;

        rep(j, 0, k) {
            int x = children[j];
            auto [v, as] = dp[x];
            lll g = __gcd(v, a);
            good = good/__gcd(good, g) * g;
        }

        if (good == 1) {
            ans = 1;
            good = a;
        }

        rep(j, 0, k) {
            int x = children[j];
            auto [v, as] = dp[x];
            ans += as;
        }

        dp[i] = {good, ans};
        cout << ans << endl;
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