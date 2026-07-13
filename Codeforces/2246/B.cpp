/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-07-12
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
    if (n == 1) {
        cout << 1 << endl;
        return;
    }

    if (n == 2) {
        cout << -1 << endl;
        return;
    }

    vl arr = {1, 2, 3};
    ll sum = 6;
    rep(i, 0, n - 3) {
        arr.pb(sum);
        sum *= 2;
    }

    rep(i, 0, n) {
        cout << arr[i] << " ";
    }

    cout << endl;
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