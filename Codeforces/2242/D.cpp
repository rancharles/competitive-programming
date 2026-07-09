/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-07-08
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

void solve(){
    string a, b; cin >> a >> b;
    int n = sz(a), m = sz(b);
    vi arr(n), brr(m);
    rep(i, 0, n) {
        arr[i] = a[i] - '0';
    }
    rep(i, 0, m) {
        brr[i] = b[i] - '0';
    }
    vi sa(n + 1, 0), sb(m + 1, 0);
    using T = array<int, 10>;
    vector<T> la(n + 1), lb(m + 1);
    rep(i, 0, 10) {
        la[0][i] = -1;
        lb[0][i] = -1;
    }
    la[0][0] = 0;
    lb[0][0] = 0;
    rep(i, 0, n) {
        sa[i + 1] = (sa[i] + arr[i]) % 10;
        la[i + 1] = la[i];
        la[i + 1][sa[i + 1]] = i + 1;
    }
    rep(i, 0, m) {
        sb[i + 1] = (sb[i] + brr[i]) % 10;
        lb[i + 1] = lb[i];
        lb[i + 1][sb[i + 1]] = i + 1;
    }
    vector<vi> dp(n + 1, vi(m + 1, INT_MIN));
    rep(i, 0, n + 1) {
        if (sa[i] == 0) {
            dp[i][0] = 0;
        }
    }
    rep(i, 0, m + 1) {
        if (sb[i] == 0) {
            dp[0][i] = 0;
        }
    }

    rep(i, 1, n + 1) {
        int at = sa[i];
        rep(j, 1, m + 1) {
            int bt = sb[j];
            rep(k, 0, 10) {
                int an = (at + 10 - k) % 10;
                int bn = (bt + 10 - k) % 10;
                int ii = la[i - 1][an];
                int jj = lb[j - 1][bn];
                if (ii == -1 || jj == -1) {
                    continue;
                }
                dp[i][j] = max(dp[i][j], 1 + dp[ii][jj]);
            }
        }
    }

    int ans = dp[n][m];
    if (ans < 0) {
        ans = -1;
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