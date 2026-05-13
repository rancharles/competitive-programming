/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-05-10
 * Contest: Codeforces 2226
 * Problem: D
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
    vi arr(n);
    rep(i, 0, n) cin >> arr[i];

    vi odd, even;
    rep(i, 0, n) {
        if (arr[i] % 2) {
            odd.pb(arr[i]);
        } else {
            even.pb(arr[i]);
        }
    }

    if (sz(odd) == 0 || sz(even) == 0) {
        rep(i, 1, n) {
            if (arr[i] < arr[i - 1]) {
                cout << "NO" << endl;
                return;
            }
        }

        cout << "YES" << endl;
        return;
    }

    int mxo = *max_element(all(odd));
    int mno = *min_element(all(odd));

    int mxe = *max_element(all(even));
    int mne = *min_element(all(even));

    int mnOdd = MAX_N;
    int mnEven = MAX_N + 1;

    for (int i = n - 1; i >= 0; i--) {
        int a = arr[i];

        if (a % 2) {
            if (a > mnOdd && mxe < a && mne > mnOdd) {
                cout << "NO" << endl;
                return;
            }
            mnOdd = min(mnOdd, a);
        } else {
            if (a > mnEven && mxo < a && mno > mnEven) {
                cout << "NO" << endl;
                return;
            }
            mnEven = min(mnEven, a);
        }
    }

    cout << "YES" << endl;
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