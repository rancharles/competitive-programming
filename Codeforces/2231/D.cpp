/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-07-01
 * Contest: 
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
const ll INF = 1e13;

void solve(){
    int n; cin >> n;

    string s; cin >> s;

    vl arr(n);
    rep(i, 0, n) cin >> arr[i];
    vl c(n);
    rep(i, 0, n) cin >> c[i];

    rep(i, 1, n) {
        if (c[i] < c[i - 1]) {
            cout << "No" << endl;
            return;
        }
    }

    ll known = 0;
    ll mx = LLONG_MIN;
    vi unknown;
    rep(i, 0, n) {
        if (s[i] == '1') {
            known += arr[i];
            if (known > c[i] && sz(unknown) == 0) {
                cout << "No" << endl;
                return;
            }
        } else {
            unknown.pb(i);
        }

        if (c[i] > mx) {
            mx = c[i];

            if (sz(unknown) > 1) {
                arr[unknown[0]] = -INF;
                arr[unknown.back()] = c[i] + INF - known;
            } else if (sz(unknown) != 0) {
                arr[unknown.back()] = c[i] - known;
            }

            known = c[i];
            unknown = {};
        }
    }

    if (sz(unknown) != 0) {
        arr[unknown[0]] = -INF;
    }

    ll psum = 0;
    ll maxp = LLONG_MIN;
    rep(i, 0, n) {
        psum += arr[i];
        maxp = max(maxp, psum);

        if (maxp != c[i]) {
            cout << "No" << endl;
            return;
        }
    }

    cout << "Yes" << endl;
    rep(i, 0, n) {
        cout << arr[i] << " ";
    }
    cout << endl;
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