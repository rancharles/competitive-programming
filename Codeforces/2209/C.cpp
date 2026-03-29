/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-21
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

    rep(i, 1, n) {
        cout << "? " << 2 * i + 1 << " " << 2 * i + 2 << endl;
        int a; cin >> a;
        if (a) {
            cout << "! " << 2 * i + 1 << endl;
            return;
        }
    }

    cout << "? " << 1 << " " << 3 << endl;
    int a; cin >> a;
    if (a) {
        cout << "! " << 1 << endl;
        return;
    }

    cout << "? " << 1 << " " << 4 << endl;
    cin >> a;
    if (a) {
        cout << "! " << 1 << endl;
        return;
    }

    cout << "! " << 2 << endl;
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