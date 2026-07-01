/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-06-30
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
    int n; cin >> n;
    vl arr(n), brr(n);
    rep(i, 0, n) cin >> arr[i];
    rep(i, 0, n) cin >> brr[i];

    for (int i = n - 1; i >= 0; i--) {
        if (arr[i] > brr[i]) {
            if (i == 0) {
                cout << "NO" << endl;
                return;
            }

            ll d = arr[i] - brr[i];
            arr[i] -= d;
            arr[i - 1] += d;
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