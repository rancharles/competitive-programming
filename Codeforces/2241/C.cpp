/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-06-30
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
    string s; cin >> s;
    
    int mn0 = 1000, mx0 = -1;
    int mn1 = 1000, mx1 = -1;
    bool has0 = false, has1 = false;
    rep(i, 0, n) {
        if (s[i] == '0') {
            has0 = true;
            mn0 = min(mn0, i);
            mx0 = max(mx0, i);
        } else {
            has1 = true;
            mn1 = min(mn1, i);
            mx1 = max(mx1, i);
        }
    }

    if (!has0 || !has1) {
        cout << 1 << endl;
        return;
    }

    if (mx0 < mn1 || mx1 < mn0) {
        cout << 2 << endl;
        return;
    }

    cout << 1 << endl;
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