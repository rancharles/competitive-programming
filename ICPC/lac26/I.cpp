/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-15
 * Contest: 
 * Problem: I
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

    int ones = 0;
    vi cnt(n, 0);
    rep(i, 0, n) {
        int x; cin >> x;
        --x;
        cnt[x]++;
    }

    rep(i, 0, n) {
        ones += cnt[i] % 2;
    }

    if (ones < 2) {
        cout << "E\n";
        return;
    }

    if (ones % 2 == 0) {
        cout << "F\n";
    } else {
        cout << "S\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; ++t){
        // cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}