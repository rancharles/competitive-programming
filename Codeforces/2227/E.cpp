/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-04-30
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
    int n; cin >> n;
    vi arr(n);
    vi cnt(n + 1, 0);
    rep(i, 0, n) {
        cin >> arr[i];
        cnt[arr[i]]++;
    }

    vi tot(n + 1, 0);
    rep(i, 1, n + 1) {
        tot[i] = tot[i - 1] + cnt[i];
    }

    vi suf(n + 1, 0);
    int mn = n;
    for (int i = n - 1; i >= 0; i--) {
        int h = arr[i];
        if (h < mn) {
            rep(j, h + 1, mn + 1) {
                suf[j] = i + 1;
            }
            mn = h;
        }
    }

    int add = 0;
    rep(i, 0, n) {
        int h = arr[i];
        add = max(add, i - suf[h]);
    }

    ll ans = 0;
    rep(i, 1, n + 1) {
        ans += - tot[i - 1] + suf[i];
    }

    ans += add;
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