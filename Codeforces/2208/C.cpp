/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-14
 * Contest: 
 * Problem: C
**/

#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using ld = long double;
using pii = pair<int, int>;
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

const int MAX_N = 1e5 + 1;
const ll MOD = 1e9 + 7;

void solve(){
    int n; cin >> n;

    vector<ld> c(n), p(n);
    rep(i, 0, n) {
        cin >> c[i];
        cin >> p[i];
    }

    vector<ld> dp(n);
    dp[n - 1] = c[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        dp[i] = max(dp[i + 1], c[i] + (1 - p[i]/100) * dp[i + 1]);
    }

    cout << fixed << setprecision(10) << dp[0] << endl;
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