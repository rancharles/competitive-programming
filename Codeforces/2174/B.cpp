/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-25
 * Contest: 
 * Problem: B
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
    int n, k; cin >> n >> k;

    vi arr(n);
    rep(i, 0, n) cin >> arr[i];

    int large = 0;
    vector<pii> mx;
    rep(i, 1, n + 1) {
        if (i == n || arr[i] > arr[large]) {
            mx.pb({arr[large], i - large});
            large = i;
        }
    }

    int m = sz(mx);
    vector<vi> dp(m + 1, vi(k + 1, 0));
    vi suf(m + 1, 0);
    suf[m] = mx[m - 1].second;
    for (int i = m - 1; i >= 1; i--) {
        suf[i] = suf[i + 1] + mx[i - 1].second;
    }

    int lst = 0;
    vi rem(k + 1, 0);
    vi lrg(k + 1, 0);
    int curr = 0;
    rep(i, 1, m + 1) {
        auto [val, num] = mx[i - 1];
        rep(j, 1, lst + 1) {
            curr++;
            if (curr > k) break;
            rem[curr] = rem[curr - 1];
            lrg[curr] = lrg[curr - 1];
        }
        rep(j, lst + 1, val + 1) {
            curr++;
            if (curr > k) break;
            rem[curr] = rem[curr - 1] + suf[i];
            lrg[curr] = j;
        }
        lst = val;
        // rep(j, 0, num) {
        //     dp[i][j] = dp[i - 1][j];
        // }
        // rep(j, num, k + 1) {
        //     dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - num] + num * val);
        // }
    }

    int ans = 0;
    rep(i, 1, m + 1) {
        auto [val, num] = mx[i - 1];
        rep(j, 0, val + 1) {
            ans = max(ans, rem[k - j] + max(0, j - lrg[k - j]) * suf[i]);
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