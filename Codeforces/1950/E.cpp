/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-20
 * Contest: 
 * Problem: E
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

const int MAX_N = 2e5 + 1;
const ll MOD = 1e9 + 7;

void solve(){
    int n; cin >> n;

    string s; cin >> s;
    vi arr(n);
    rep(i, 0, n) {
        arr[i] = s[i] - 'a';
    }

    vi ans;

    int rt = sqrt(n);
    for (int x = 1; x <= rt; x++) {
        if (rt % x != 0) continue;
        int y = rt/x;

        int uniq = 0;
        vi other(x, -1);
        for (int k = 1; k < n; k += x) {
            rep(i, 0, x) {
                if (arr[k * x + i] != arr[i]) {
                    other[i] = arr[i];
                    uniq++;
                } 
            }
        }

        if (uniq < 2) {
            ans.pb(x);
        }

        for (int k = 1; k < n; k += y) {
            rep(i, 0, y) {

            }
        }

        if (uniq < 2) {
            ans.pb(y);
        }
    }

    cout << *min_element(all(ans)) << endl;
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