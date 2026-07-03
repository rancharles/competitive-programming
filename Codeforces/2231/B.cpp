/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-07-01
 * Contest: 
 * Problem: B
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

    vi arr(n);
    rep(i, 0, n) cin >> arr[i];

    vi pmx(n + 1, 0), smn(n + 1, INT_MAX);
    rep(i, 0, n) {
        pmx[i + 1] = max(pmx[i], arr[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
        smn[i] = min(smn[i + 1], arr[i]);
    }

    int inc = 0;
    vi need;
    rep(i, 0, n) {
        if (pmx[i] > arr[i]) {
            need.pb(i);
            inc = max(inc, pmx[i] - arr[i]);
        }
    }

    vector<bool> used(n, false);
    for (int i : need) {
        used[i] = true;
        arr[i] += inc;
    }

    if (sz(need) != 0) {
        rep(i, need.back() + 1, n) {
            arr[i] += inc;
        }
    }

    rep(i, 1, n) {
        if (arr[i] < arr[i - 1] && !used[i]) {
            arr[i] += inc;
        }

        if (arr[i] < arr[i - 1]) {
            cout << "NO" << endl;
            return;
        }
    }

    cout << "YES" << endl;
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