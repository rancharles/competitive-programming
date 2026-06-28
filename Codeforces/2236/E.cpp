/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-06-28
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
    vi arr(n);
    rep(i, 0, n) {
        cin >> arr[i];
        --arr[i];
    }

    vector<vi> len(n + 1);

    rep(i, 0, n) {
        int mn = arr[i], mx = arr[i];
        vector<bool> has(n, false);
        has[arr[i]] = true;

        len[1].pb(mn);

        rep(j, i + 1, n) {
            if (has[arr[j]]) {
                break;
            }

            has[arr[j]] = true;
            mn = min(mn, arr[j]);
            mx = max(mx, arr[j]);

            if (mx - mn == j - i) {
                len[j - i + 1].pb(mn);
            }
        }
    }

    for (int i = n; i >= 1; i--) {
        vector<bool> has(n, false);
        for (int x : len[i]) {
            has[x] = true;
            if (x - i >= 0 && has[x - i]) {
                cout << i << endl;
                return;
            }

            if (x + i < n && has[x + i]) {
                cout << i << endl;
                return;
            }
        }
    }

    cout << 0 << endl;
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