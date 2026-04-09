/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-04-08
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
const int D = 20;

void solve(){
    int x, y; cin >> x >> y;

    if (x > y) {
        cout << 1 << " " << 1 << endl;
        return;
    }

    set<pair<ll, int>> s;
    rep(c, 0, x) {
        int one = 0;
        vi zero;
        rep(b, 0, D) {
            int bt = 1 << b;
            if (c & bt) {
                one++;
            } else {
                zero.pb(b);
            }
        }

        reverse(all(zero));

        int diff = y - 1 - c;
        diff /= 2;
        ll mult = 1LL << one;
        ll num = 1;
        int cnt = sz(zero);
        for (int b : zero) {
            int bt = 1 << b;
            cnt--;
            if (bt > diff) continue;
            diff -= bt;
            num += 1LL << cnt;
        }
        s.insert({mult * num, c});
    }

    int c = s.begin()->first;
    // cout << c << endl;
    int w = s.begin()->second;
    // cout << w << endl;
    cout << 1 << " " << x - w << endl;
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