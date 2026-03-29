/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-21
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
const ll MOD = 1e9 + 7;

vector<int> z_function(vi& s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

void solve(){
    int n, q; cin >> n >> q;

    string s; cin >> s;
    vi arr(n);
    rep(i, 0, n) {
        arr[i] = s[i] - 'a';
    }

    rep(qq, 0, q) {
        int l, r; cin >> l >> r;
        --l;
        vi curr;
        rep(i, l, r) {
            curr.pb(arr[i]);
        }

        int m = r - l;

        vi z = z_function(curr);
        // vi dp(m + 1, -1);
        // dp[m] = 0;
        vi need(m + 1, m - 1);
        int lst = m;
        ll ans = 0;
        for (int i = m - 1; i >= 0; i--) {
            if (i == 0) {
                z[i] = m;
            }

            if (i + z[i] >= lst) {
                int j = i;
                while (j < i + z[i]) {
                    if (j + 1 != m && z[j + 1] != 0) {
                        j = need[j + 1];
                    } else {
                        if (j == i + z[i] - 1) break;
                        j++;
                    }
                }
                need[i] = min(j, m - 1);
                // dp[i] = 1 + dp[lst];
                // need[i] = max(i + z[i] - 1, need[lst]);
                ans += need[i] - i + 1;
            } else {
                // dp[i] = dp[lst];
                ans += z[i];
                need[i] = i + z[i] - 1;
            }

            if (z[i] != 0) {
                lst = i;
            }
        }

        cout << ans << "\n";
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