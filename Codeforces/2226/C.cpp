/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-04-29
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

    multiset<int> s;
    rep(i, 0, n) {
        int x; cin >> x;
        s.insert(x);
    }

    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = (lo + hi + 1)/2;
        multiset<int> ss = s;
        bool good = true;
        vector<bool> done(mid, false);
        rep(i, 0, mid) {
            auto j = ss.find(i);
            if (j != ss.end()) {
                ss.erase(j); 
                done[i] = true;
                continue;
            }
        }

        rep(i, 0, mid) {
            if (done[i]) continue;
            auto j = ss.lower_bound(2 * i + 1);
            if (j == ss.end()) {
                good = false;
                break;
            }

            ss.erase(j);
        }

        if (good) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    cout << lo << endl;
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