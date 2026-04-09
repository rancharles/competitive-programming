/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-04-08
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
    rep(i, 0, n) cin >> arr[i];

    vi d(n);
    rep(i, 0, n) cin >> d[i];

    vi ans;

    for (int i = n - 1; i >= 0; i--) {
        vi dom;
        rep(j, i + 1, n) {
            if (arr[j] > arr[i]) {
                dom.pb(j);
            }
        }

        if (d[i] > sz(dom)) {
            cout << -1 << endl;
            return;
        }

        vector<bool> big(n, false);
        for (int j : dom) {
            big[j] = true;
        }

        int need = sz(dom) - d[i];
        bool added = false;
        int cnt = 0;
        vi rans;
        rep(j, 0, sz(ans)) {
            if (!added && cnt == need) {
                rans.pb(i);
                added = true;
            }

            rans.pb(ans[j]);
            if (big[ans[j]]) {
                cnt++;
            }
        }
        
        if (!added && cnt == need) {
            rans.pb(i);
        }

        ans = rans;
    }

    vi fans(n);
    rep(i, 0, sz(ans)) {
        fans[ans[i]] = i + 1;
    }

    rep(i, 0, n) {
        cout << fans[i] << " ";
    }
    cout << endl;
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