/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-04-07
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

const int MAX_N = 3e2;
const ll MOD = 1e9 + 7;

void solve(){
    int p, s; cin >> p >> s;

    if (p == 4 * s) {
        cout << 1 << endl;
        cout << "0 0" << endl;
        return;
    }

    if (p == 3 * s) {
        cout << 2 << endl;
        cout << "0 0" << endl;
        cout << "0 1" << endl;
        return;
    }

    if (3 * p == 8 * s) {
        cout << 3 << endl;
        cout << "0 0" << endl;
        cout << "0 1" << endl;
        cout << "0 2" << endl;
        return;
    }

    if (2 * p == 5 * s) {
        cout << 4 << endl;
        cout << "0 0" << endl;
        cout << "0 1" << endl;
        cout << "0 2" << endl;
        cout << "0 3" << endl;
        return;
    }

    if (p > 2 * s) {
        rep(k, 1, MAX_N) {
            int r = k * p;
            if (r % s != 0) continue;
            int x = r/s;
            if (x > 2 * k + 2) break;
            int d = 2 * k + 2 - x;
            if (d % 2 == 1) continue;
            d /= 2;
            d++;
            cout << k << endl;
            rep(i, 0, d) {
                cout << "1 " << i << endl;
            }
            rep(i, 0, k - d) {
                cout << "0 " << i << endl;
            }
            return;
        }

        cout << -1 << endl;
        return;
    }

    int mult = 1000;

    p *= mult;
    s *= mult;

    int l = p/4;
    int d = s - 2 * l + 1;

    cout << s << endl;
    cout << "0 0" << endl;
    rep(i, 1, l) {
        cout << "0 " << i << endl;
        cout << i << " 0" << endl;
    }

    int cnt = 0;
    rep(i, 1, l) {
        rep(j, 1, l) {
            if (cnt == d) break;
            cnt++;
            cout << i << " " << j << endl;
        }
        if (cnt == d) break;
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