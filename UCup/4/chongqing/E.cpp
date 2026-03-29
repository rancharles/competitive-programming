/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-29
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

const int MAX_N = 1e5 + 1;
const ll MOD = 1e9 + 7;

void solve(){
    int n; cin >> n;

    using T = pair<ll, ll>;
    vector<T> arr(n);
    rep(i, 0, n) {
        cin >> arr[i].second;
    }
    rep(i, 0, n) {
        cin >> arr[i].first;
    }

    bool isZero = true;
    rep(i, 0, n) {
        if (arr[i].second <= arr[i].first) {
            isZero = false;
            break;
        }
    }

    if (isZero) {
        cout << 0 << "\n";
        return;
    }

    sort(all(arr));
    int lo = 1, hi = n;
    while (lo < hi) {
        ll mid = (lo + hi + 1)/2;
        bool good = false;
        ll sum = 0;
        multiset<ll> best;
        rep(i, n - mid + 1, n) {
            sum += arr[i].second;
            best.insert(arr[i].second);
        }
        for (int i = n - mid; i >= 0; i--) {
            ll budget = arr[i].first * mid;
            ll cost = arr[i].second;
            if (cost + sum <= budget) {
                good = true;
                break;
            }

            sum += cost;
            best.insert(cost);
            auto j = prev(best.end());
            sum -= *j;
            best.erase(j);
        }

        if (good) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    cout << lo << "\n";
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