/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-07-14
 * Contest: 
 * Problem: E
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
    int n, q; cin >> n >> q;

    string s; cin >> s;
    vi pre1(n + 1, 0), pre2(n + 1, 0);
    rep(i, 0, n) {
        pre1[i + 1] = pre1[i];
        pre2[i + 1] = pre2[i];
        if (i != 0 && s[i] == s[i - 1]) {
            pre2[i + 1]++;
        }
        if (i != n - 1 && s[i] == s[i + 1]) {
            pre1[i + 1]++;
        }
    }

    auto get = [&](int l, int r) {
        return pre2[r + 1] - pre1[l];
    };

    rep(i, 0, q) {
        int l, r, k; cin >> l >> r >> k;
        --l; --r;
        if ((get(l, r) + 1)/2 > k) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
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