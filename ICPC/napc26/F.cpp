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
    int n; cin >> n;

    vector<vi> ans(n, vi(n));
    rep(i, 2, n) {
        rep(j, 0, i) {
            ans[i][j] = 2 * i + 1;
            ans[j][i] = 2 * i + 1;
        }
    }

    rep(i, 2, n) {
        ans[i][i] = 2 * i + 2; 
    }


    ans[0][0] = 1;
    ans[0][1] = 2;
    ans[1][0] = 3;
    ans[1][1] = 4;

    cout << "Yes\n";

    rep(i, 0, n) {
        rep(j, 0, n) {
            cout << ans[i][j] << " ";
        }

        cout << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}