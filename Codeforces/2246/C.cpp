/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-07-12
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

    vl zero(n + 1, 0), one(n + 1, 0);
    zero[n] = 1;

    map<ll, ll> z, o;
    for (int i = n - 1; i >= 0; i--) {
        ll a = arr[i];
        zero[i] = zero[i + 1];
        zero[i] += z[a];
        zero[i] %= MOD;

        z[a] += zero[i + 1];
        z[a] %= MOD;

        one[i] = one[i + 1];
        one[i] += o[a];
        one[i] += z[a + 1];
        one[i] %= MOD;

        o[a] += one[i + 1];
        o[a] %= MOD;
    }

    ll ans = zero[0];
    rep(i, 0, n) {
        if (arr[i] != -1) continue;
        ans += one[i + 1];
        ans %= MOD;
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