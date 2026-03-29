/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-15
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
    int n, l; cin >> n >> l;

    vector<pii> a(n), b(n);
    vector<pii> pos(n);
    rep(i, 0, n) {
        int x; cin >> x;
        a[i] = {x, i};
        pos[i].first = x;
    }
    rep(i, 0, n) {
        int x; cin >> x;
        b[i] = {x, i};
        pos[i].second = x;
    }

    sort(all(a));
    sort(all(b));

    int ia, ib;
    rep(i, 0, n) {
        if (a[i].second == 0) {
            ia = i;
        }

        if (b[i].second == 0) {
            ib = i;
        }
    }

    rep(j, 0, n) {
        if (a[(ia + j) % n].second != b[(ib + j) % n].second) {
            cout << "*\n";
            return;
        }
    }

    if (pos[0].first > pos[0].second) {
        rep(i, 0, n) {
            swap(pos[i].first, pos[i].second);
        }
    }

    int ans = INT_MAX;

    auto counter = [&](int x, int y) {
        if (y < x) {
            return l - x + y;
        }

        return y - x;
    };

    auto clock = [&](int x, int y) {
        if (y <= x) {
            return x - y;
        }

        return l - y + x;
    };

    {
        auto [ss, ee] = pos[0];
        int cand = ee - ss;
        auto inRange = [&](int x) -> bool {
            return x > ss && x < ee;
        };

        rep(i, 1, n) {
            auto [s, e] = pos[i];
            int curr = 0;
            if (inRange(s)) {
                curr += counter(s, ee);
                curr += counter(ee, e);
            } else {
                curr = abs(counter(ee, s) - counter(ee, e));
            }

            cand = max(cand, curr);
        }

        ans = min(ans, cand);
    }

    {
        auto [ss, ee] = pos[0];
        int cand = l - ee + ss;
        auto inRange = [&](int x) -> bool {
            return x < ss || x > ee;
        };

        rep(i, 1, n) {
            auto [s, e] = pos[i];
            int curr = 0;
            if (inRange(s)) {
                curr += clock(s, ee);
                curr += clock(ee, e);
            } else {
                curr = abs(clock(ee, s) - clock(ee, e));
            }

            cand = max(cand, curr);
        }

        ans = min(ans, cand);
    }

    cout << ans << endl;
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