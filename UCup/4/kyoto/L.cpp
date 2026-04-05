/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-04-04
 * Contest: 
 * Problem: L
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
const ll MOD = 998244353;

void solve(){
    int n; cin >> n;
    string s; cin >> s;

    vector<set<int>> idx(4);
    rep(i, 0, n) {
        if (s[i] == 'K') {
            idx[0].insert(i + 1);
        } else if (s[i] == 'U') {
            idx[1].insert(i + 1);
        } else if (s[i] == 'P') {
            idx[2].insert(i + 1);
        } else if (s[i] == 'C'){
            idx[3].insert(i + 1);
        }
    }

    ll ans = 0;
    while (true) {
        ll curr = 1;
        int pos = n + 100;
        bool stop = false;
        for (int i = 3; i >= 0; i--) {
            if (idx[i].empty()) {
                stop = true;
                break;
            }

            auto j = idx[i].lower_bound(pos);
            if (j == idx[i].begin()) {
                stop = true;
                break;
            }

            j = prev(j);

            pos = *j;
            curr *= *j;
            curr %= MOD;
            idx[i].erase(j);
        }

        if (stop) break;

        ans += curr;
        ans %= MOD;
    }

    cout << ans << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}