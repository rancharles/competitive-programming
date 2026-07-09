/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-07-08
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
    rep(i, 0, n) {
        cin >> arr[i];
        --arr[i];
    }
    using T = array<int, 3>;
    vector<T> cnt(n + 1, {0, 0, 0});
    rep(i, 0, n) {
        cnt[i + 1] = cnt[i];
        cnt[i + 1][arr[i]]++;
    }

    vi s(n + 1, INT_MIN);
    for (int i = n - 1; i >= 1; i--) {
        auto [a, b, c] = cnt[i];
        s[i] = max(s[i + 1], a + b - c);
    }

    rep(i, 1, n - 1) {
        auto [a, b, c] = cnt[i];
        int d = a + b - c;
        if (a >= b + c && s[i + 1] >= d) {
            cout << "YES" << endl;
            return;
        }
    }

    cout << "NO" << endl;
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