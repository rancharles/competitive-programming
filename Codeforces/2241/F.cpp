/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-06-30
 * Contest: 
 * Problem: F
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
    string x; cin >> x;

    int s = 0, e = n - 1;
    while (x[s] != '1' && s < n) {
        s++;
    }

    while (x[e] != '0' && e >= 0) {
        e--;
    }

    if (s > e) {
        cout << "Bob" << endl;
        return;
    }

    int curr = 0;
    rep(i, s, e + 1) {
        curr++;
        if (i == n - 1 || x[i] != x[i + 1]) {
            if (curr % 2 == 1) {
                cout << "Alice" << endl;
                return;
            }
            curr = 0;
        }
    }

    cout << "Bob" << endl;
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