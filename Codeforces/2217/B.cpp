/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-04-08
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
    int n, k; cin >> n >> k;

    vi arr(n);
    rep(i, 0, n) {
        cin >> arr[i];
    }

    int p; cin >> p;
    --p;

    int mx1 = 0;
    rep(i, p + 1, n) {
        if (arr[i] != arr[i - 1] && arr[i] != arr[p]) {
            mx1++;
        }
    }

    int mx2 = 0;
    for (int i = p - 1; i >= 0; i--) {
        if (arr[i] != arr[i + 1] && arr[i] != arr[p]) {
            mx2++;
        }
    }

    cout << 2 * max(mx1, mx2) << endl;
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