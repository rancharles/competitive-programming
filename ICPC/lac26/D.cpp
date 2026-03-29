/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-15
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
    int n, x; cin >> n >> x;

    int k; cin >> k;

    ll ans = 0;

    vl arr(n);
    rep(i, 0, n) {
        cin >> arr[i];
    }

    multiset<ll> cand;
    rep(i, n - k, n) {
        cand.insert(arr[i]);
    }

    for (int i = n - 1; i >= 0; i--) {
        int pos = i - k;
        if (pos >= 0) {
            cand.insert(arr[pos]);
        }

        if ((i + 1) % (x + 1) == 0) {
            auto j = prev(cand.end());
            ans += *j;
            cand.erase(j);
        } else {
            auto j = cand.begin();
            cand.erase(j);
        }
    }

    cout << ans/2 << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; ++t){
        // cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}