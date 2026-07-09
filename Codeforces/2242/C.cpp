/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-07-08
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
    int n, k; cin >> n >> k;

    vi arr(n);
    rep(i, 0, n) {
        cin >> arr[i];
    }

    int tot = n;
    int ans = 0;
    set<array<int, 3>> s;
    set<array<int, 3>> c;
    int curr = 1;
    rep(i, 1, n) {
        if (arr[i] != arr[i - 1]) {
            s.insert({i - 1, arr[i - 1], curr});
            c.insert({curr, i - 1, arr[i - 1]});
            curr = 1;
        } else {
            curr++;
        }
    }

    s.insert({n - 1, arr.back(), curr});
    c.insert({curr, n - 1, arr.back()});

    auto rem = [&](int x, int y, int z) {
        c.erase({x, y, z});
        auto j = s.find({y, z, x});
        if (j != s.begin() && next(j) != s.end()) {
            auto i = prev(j);
            auto k = next(j);
            auto [ix, iy, iz] = *i;
            auto [kx, ky, kz] = *k;
            s.erase(j);
            if (iy == ky) {
                s.erase({ix, iy, iz});
                s.erase({kx, ky, kz});
                c.erase({iz, ix, iy});
                c.erase({kz, kx, ky});
                s.insert({ix, iy, iz + kz});
                c.insert({iz + kz, ix, iy});
            }
            return;
        }
        s.erase(j);
    };

    int re = 0;
    while (!s.empty()) {
        int a = (*c.begin())[0];
        if ((k - tot) % sz(s) == 0 && (k - tot)/sz(s) > -(a - re)) {
            ans++;
        }
        tot -= sz(s) * (a - re);
        re = a;
        while (!c.empty()) {
            auto j = c.begin();
            auto [x, y, z] = *j;
            if (x != a) {
                break;
            }

            rem(x, y, z);
        }
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