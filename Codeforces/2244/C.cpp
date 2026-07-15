/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-07-14
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
    int n, x, y; cin >> n >> x >> y;
    int d = __gcd(x, y);
    
    vi arr(n);
    vector<vi> s(d);
    rep(i, 0, n) cin >> arr[i];
    rep(i, 0, n) {
        s[i % d].pb(arr[i]);
    }
    rep(i, 0, d) {
        sort(all(s[i]));
    }
    vi brr(n);
    rep(i, 0, n) {
        brr[i] = s[i % d][i/d];
        if (i != 0 && brr[i - 1] > brr[i]) {
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