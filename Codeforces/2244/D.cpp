/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-07-14
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

void solve(){
    int n, m; cin >> n >> m;

    vl arr(n);
    vl pre(n, 0);
    ll ans = 0;
    rep(i, 0, n) {
        cin >> arr[i];
        ans += arr[i];
        if (i != 0) pre[i] = pre[i - 1];
        pre[i] += arr[i];
    }
    vi brr(m);
    rep(i, 0, m) cin >> brr[i];
    sort(all(brr));
    reverse(all(brr));

    rep(i, 0, m) {
        int j = brr[i];
        --j;
        ll diff = pre[j];
        if (i != m - 1) {
            diff -= pre[brr[i + 1] - 1];
        }
        if (diff < 0) {
            ans -= diff * 2;
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