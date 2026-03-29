/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-28
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

const int MAX_N = 4e5 + 1;
const ll MOD = 1e9 + 7;

void solve(){
    int x, y; cin >> x >> y;

    int sum = x - y;
    if (sum < 0) {
        sum = -sum;
    }

    if (sum == 0) {
        cout << 1 << "\n";
    } else {
        int rt = sqrt(sum);
        int divs = 0;
        rep(i, 1, rt + 1) {
            if (sum % i == 0) {
                divs++;
            } else {
                continue;
            }

            int rev = sum/i;
            if (rev != i) {
                divs++;
            }
        }

        cout << divs << "\n";
    }

    rep(i, 0, x) {
        cout << 1 << " ";
    }

    rep(i, 0, y) {
        cout << -1 << " ";
    }

    cout << '\n';
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