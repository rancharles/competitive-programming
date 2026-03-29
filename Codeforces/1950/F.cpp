/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-20
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
    int a, b, c; cin >> a >> b >> c;
    if (a + 1 != c) {
        cout << -1 << endl;
        return;
    }

    multiset<int> depths;
    depths.insert(0);

    rep(i, 0, a) {
        auto j = depths.begin();
        depths.insert(*j + 1);
        depths.insert(*j + 1);
        depths.erase(j);
    }

    rep(i, 0, b) {
        auto j = depths.begin();
        depths.insert(*j + 1);
        depths.erase(j);
    }

    cout << *prev(depths.end()) << endl;
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