/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-06-29
 * Contest: 
 * Problem: A
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
    int n, c; cin >> n >> c;

    int ans = 0;

    vi a(n), b(n);
    rep(i, 0, n) cin >> a[i];
    rep(i, 0, n) cin >> b[i];

    bool good = true;
    rep(i, 0, n) {
        if (b[i] > a[i]) good = false;
    }

    if (good) {
        rep(i, 0, n) {
            ans += a[i] - b[i];
        }

        cout << ans << endl;
        return;
    }

    ans = c;

    sort(all(a));
    sort(all(b));
    rep(i, 0, n) {
        if (b[i] > a[i]) {
            cout << -1 << endl;
            return;
        }

        ans += a[i] - b[i];
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