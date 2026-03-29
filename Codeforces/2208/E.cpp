/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-14
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
    int n; cin >> n;

    vi arr(n);
    rep(i, 0, n) {
        cin >> arr[i];
    }

    vector<vl> dp(n, vl(n + 1, 0));

    rep(i, 0, n + 1) {
        if (arr[n - 1] == -1) {
            dp[n - 1][i] = i;
        } else {
            if (arr[n - 1] < i) {
                dp[n - 1][i] = 1;
            }
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        rep(j, 0, n + 1) {
            if (arr[i] != -1) {
                if (arr[i] < j) {
                    
                }
                continue;
            }
        }
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