/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-25
 * Contest: 
 * Problem: A
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
    string s; cin >> s;
    int n = sz(s);
    vi arr(n);
    rep(i, 0, n) {
        arr[i] = s[i] - 'a';
    }

    string t; cin >> t;
    vi cnt(26, 0);
    rep(i, 0, sz(t)) {
        int x = t[i] - 'a';
        cnt[x]++;
    }

    rep(i, 0, n) {
        int x = arr[i];
        if (cnt[x] == 0) {
            cout << "Impossible\n";
            return;
        }

        cnt[x]--;
    }

    string ans;
    rep(i, 0, n) {
        int x = arr[i];
        rep(j, 0, 26) {
            if (j >= x) break;
            rep(k, 0, cnt[j]) {
                ans += (char)('a' + j);
            }
            cnt[j] = 0;
        }

        ans += (char)('a' + x);
    }

    rep(j, 0, 26) {
        rep(k, 0, cnt[j]) {
            ans += (char)('a' + j);
        }
    }

    cout << ans << '\n';
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