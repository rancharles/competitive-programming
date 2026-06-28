/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-06-28
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
    int n, k; cin >> n >> k;

    vi arr(n);

    rep(i, 0, n) cin >> arr[i];
    sort(all(arr));

    vector<bool> c(n, false), win(n, false);
    rep(i, 0, n) {
        if (i == 0 || arr[i] != arr[i - 1]) {
            c[i] = true;
        }
    }

    int w = 0;
    deque<int> q;
    for (int i = n - 1; i >= 0; i--) {
        while (!q.empty() && q.front() > arr[i] + k) {
            q.pop_front();
            w--;
        }

        if (w == 0) {
            win[i] = true;
        }

        while (!q.empty() && q.back() == arr[i]) {
            q.pop_back();
            w--;
        }

        if (win[i]) {
            q.push_back(arr[i]);
            w++;
        }

        if (c[i]) {
            if (!win[i]) {
                cout << "YES" << endl;
                return;
            }
        }
    }

    cout << "NO" << endl;
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