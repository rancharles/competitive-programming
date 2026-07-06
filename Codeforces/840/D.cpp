/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-07-06
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
const int c = 5;

void solve(){
    int n, q; cin >> n >> q;

    vi arr(n);
    rep(i, 0, n) {
        cin >> arr[i];
        --arr[i];
    }
    vector<vi> pos(n);
    rep(i, 0, n) {
        int x = arr[i];
        pos[x].pb(i);
    }

    auto count = [&](int x, int l, int r) -> int {
        auto s = lower_bound(all(pos[x]), l);
        if (s == pos[x].end()) return 0;
        auto e = upper_bound(all(pos[x]), r);
        return e - s;
    };

    using T = array<int, 4>;
    vector<T> queries(q);
    rep(i, 0, q) {
        int l, r, k; cin >> l >> r >> k;
        --l; --r;
        queries[i] = {l, r, k, i};
    }

    vi ans(q, -1);
    vi cnt(n, 0);

    function<void(int, int, vector<T>)> dq;
    dq = [&](int l, int r, vector<T> queries) {
        int mid = (l + r)/2;
        if (l == r) {
            for (T q : queries) {
                ans[q[3]] = arr[l] + 1;
            }
            return;
        }

        vector<vi> cand(r - l + 1);
        vi aff;
        set<pair<int, int>> curr;
        rep(i, mid + 1, r + 1) {
            int need = (i - mid)/c + 1;
            int x = arr[i];
            if (cnt[x] > 0) {
                curr.erase({-cnt[x], x});
            }
            aff.pb(x);
            cnt[x]++;
            curr.insert({-cnt[x], x});

            for (auto [cc, y] : curr) {
                if (-cc < need) {
                    break;
                }

                cand[i - l].pb(y);
            }
        }

        for (int x : aff) {
            cnt[x] = 0;
        }
        aff = {};
        curr = {};
        for (int i = mid; i >= l; i--) {
            int need = (mid - i + 1)/c + 1;
            int x = arr[i];
            if (cnt[x] > 0) {
                curr.erase({-cnt[x], x});
            }
            cnt[x]++;
            curr.insert({-cnt[x], x});

            for (auto [cc, y] : curr) {
                if (-cc < need) {
                    break;
                }

                cand[i - l].pb(y);
            }
        }
        for (int x : aff) {
            cnt[x] = 0;
        }
        aff = {};

        vector<T> left, right;
        for (T qr : queries) {
            auto [ll, rr, k, i] = qr;
            if (rr <= mid) {
                left.pb(qr);
                continue;
            }

            if (ll > mid) {
                right.pb(qr);
                continue;
            }

            vi ca;
            for (int x : cand[ll - l]) {
                ca.pb(x);
            }
            for (int x : cand[rr - l]) {
                ca.pb(x);
            }
            int need = (rr - ll + 1)/k + 1;
            int mn = INT_MAX;
            for (int x : ca) {
                if (x >= mn) continue;
                int a = count(x, ll, rr);
                if (a < need) continue;
                mn = x;
            }
            if (mn != INT_MAX) {
                ans[i] = mn + 1;
            }
        }
        dq(l, mid, left);
        dq(mid + 1, r, right);
    };

    dq(0, n - 1, queries);
    
    for (int x : ans) {
        cout << x << '\n';
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    for (int t = 1; t <= tc; ++t){
        // cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}