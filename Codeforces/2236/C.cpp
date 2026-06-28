/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-06-28
 * Contest: 
 * Problem: C
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
    int a, b, x; cin >> a >> b >> x;

    int ans = INT_MAX;

    int ca = 0;
    while (true) {
        int bb = b;
        int cb = 0;
        while (true) {
            ans = min(ans, abs(bb - a) + ca + cb);
            if (bb == 0) break;
            bb /= x;
            cb++;
        }
        if (a == 0) break;
        a /= x;
        ca++;
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