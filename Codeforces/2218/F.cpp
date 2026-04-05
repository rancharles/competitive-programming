/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-04-04
 * Contest: 
 * Problem: F
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
    int x, y; cin >> x >> y;

    if (y < x) {
        cout << "NO" << "\n";
        return;
    }

    vector<pii> ans;
    int d = y - x;
    int s = 1;
    if (d % 2 == 1) {
        if (x != 0) ans.pb({1, 2});
        s = 2;
        d--;
    }

    rep(i, 0, x) {
        ans.pb({s + 2 * i, s + 2 * i + 1});
        if (i != x - 1) ans.pb({s + 2 * i + 1, s + 2 * i + 2});
    }

    int lst = s + 2 * x - 1;
    if (lst == 0) {
        if (d % 2 == 0) {
            cout << "NO" << "\n";
            return;
        } else {
            d--;
            lst = 1;
        }
    }
    rep(i, 0, d) {
        ans.pb({lst, x + y - i});
    }

    cout << "YES" << "\n";
    for (pii e : ans) {
        cout << e.first << " " << e.second << "\n";
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