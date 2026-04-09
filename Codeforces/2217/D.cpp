/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-04-08
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
    int n, k; cin >> n >> k;

    vi arr(n);
    rep(i, 0, n) {
        cin >> arr[i];
    }

    vector<bool> isP(n, false);
    vi p(k);
    rep(i, 0, k) {
        cin >> p[i];
        --p[i];
        isP[p[i]] = true;
    }

    int pp = p[0];

    int cand = 0;
    int has = 0;
    int curr = 0;
    int ans = 0;
    vi dp1(n), dp2(n);
    int mx1 = 0;
    rep(i, 0, n) {
        if ((i == 0 || arr[i] != arr[i - 1]) && arr[i] != arr[pp]) {
            mx1++;
            if (mx1 == 1 && cand > 0) {
                ans--;
                cand--;
                cout << "a" << i << endl;
            }
        }
        // dp1[i] = mx1;
        if (isP[i]) {
            int d = min(mx1, curr);
            curr -= d;
            mx1 -= d;
            if (mx1 > 0) {
                cand = 0;
                curr = mx1;
                ans += 2 * mx1;
                mx1 = 0;
                has++;
            } else if (has > 0) {
                cand++;
            }
        }
    }

    int d = min(mx1, curr);
    curr -= d;
    mx1 -= d;
    if (mx1 > 0) {
        ans += 2 * mx1;
    }

    // int mx2 = 0;
    // for (int i = n - 1; i >= 0; i--) {
    //     if ((i == n - 1 || arr[i] != arr[i + 1]) && arr[i] != arr[pp]) {
    //         mx2++;
    //     }
    //     dp2[i] = mx2;
    // }

    // int ans = INT_MAX;
    // rep(i, 0, k) {
    //     int q = p[i];

    //     ans = min(ans, max(dp1[q], dp2[q]));
    // }

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