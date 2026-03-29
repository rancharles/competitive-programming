/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-21
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

void solve(){
    vector<pii> arr(3);
    rep(i, 0, 3) {
        int x; cin >> x;
        arr[i] = {x, i};
    }

    sort(all(arr));
    reverse(all(arr));
    vector<char> c = {'R', 'G', 'B'};
    string ans;
    while (arr[0].first < arr[1].first + arr[2].first) {
        arr[1].first--;
        arr[2].first--;
        ans += c[arr[2].second];
        ans += c[arr[1].second];
    }

    rep(i, 0, arr[1].first) {
        arr[0].first--;
        ans += c[arr[0].second];
        ans += c[arr[1].second];
    }

    rep(i, 0, arr[2].first) {
        arr[0].first--;
        ans += c[arr[0].second];
        ans += c[arr[2].second];
    }

    if (arr[0].first > 0) {
        ans += c[arr[0].second];
    }

    cout << ans << endl;
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