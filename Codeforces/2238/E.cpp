/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-06-29
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

void solve(){
    int n; cin >> n;
    string s; cin >> s;

    vi arr(n, 0);
    rep(i, 0, n) {
        if (s[i] == 'F') {
            arr[i] = 1;
        } else if (s[i] == 'T') {
            arr[i] = -1;
        }
    }

    auto mxsum = [&](vi& arr) {
        vi pre(n + 1, 0);
        rep(i, 0, n) {
            pre[i + 1] = arr[i] + pre[i];
        }

        int ans = 0;
        int mn = 0;
        rep(i, 1, n + 1) {
            ans = max(ans, pre[i] - mn);
            mn = min(mn, pre[i]);
        }

        return ans;
    };

    int mx = INT_MIN;
    rep(sbsum, 0, n + 1) {
        vi brr = arr;
        rep(i, 0, n) {
            if (arr[i] == 0) {
                brr[i] = -1;
            }
        }

        // mxsum <= sbsum case
        if (mxsum(brr) > sbsum) continue;

        int sum = 0;
        rep(i, 0, n) {
            if (arr[i] == 0) {
                brr[i] = 1;

                if (mxsum(brr) > sbsum) {
                    brr[i] = -1;
                }
            }

            sum += brr[i];
        }

        mx = max(mx, sum - 2 * sbsum);
    }

    cout << (mx + n)/2 << endl;
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