/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-04-30
 * Contest: 
 * Problem: G
**/

#include <bits/stdc++.h>
using namespace std;

// Order statistic tree
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T>
using Tree =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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
    vl arr(n);
    rep(i, 0, n) {
        cin >> arr[i];
    }
    vl pre(n + 1, 0);
    rep(i, 0, n) {
        ll mult = -1;
        if (i % 2 == 0) mult = 1;
        pre[i + 1] = pre[i] + mult * arr[i];
    }

    Tree<pair<ll, int>> odd, even;
    ll ans = 0;
    for (int i = n; i >= 1; i--) {
        if (i % 2 == 0) {
            even.insert({pre[i], i});
            ans += even.order_of_key({pre[i - 1], -10});
        } else {
            odd.insert({pre[i], i});
            ans += sz(odd) - odd.order_of_key({pre[i - 1], n + 10});
        }
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