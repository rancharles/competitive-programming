/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-07-01
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
    int n; cin >> n;

    vl arr(n);
    rep(i, 0, n) cin >> arr[i];

    sort(all(arr));

    auto op = [&](ll x) -> ll {
        if (x % 2 == 0) {
            return x/2;
        }

        return x + 1;
    };

    map<int, int> cand;
    map<int, int> hit;

    int curr = 0;
    cand[arr[0]] = curr;
    hit[arr[0]]++;
    while (!cand.contains(op(arr[0]))) {
        curr++;
        arr[0] = op(arr[0]);
        hit[arr[0]]++;
        cand[arr[0]] = curr;
    }

    rep(i, 1, n) {
        int curr = 0;
        set<int> cyc;
        cyc.insert(arr[i]);
        if (cand.contains(arr[i])) {
            cand[arr[i]] += curr;
            hit[arr[i]]++;
        }

        while (!cyc.contains(op(arr[i]))) {
            curr++;
            arr[i] = op(arr[i]);
            cyc.insert(arr[i]);
            if (cand.contains(arr[i])) {
                cand[arr[i]] += curr;
                hit[arr[i]]++;
            }
        }
    }

    int ans = INT_MAX;
    for (auto [k, v] : cand) {
        if (hit[k] != n) continue;
        ans = min(ans, v);
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