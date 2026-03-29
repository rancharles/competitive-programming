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
    int n = 7, m = 7;
    vector<vi> grid(n, vi(m));
    rep(i, 0, n) {
        rep(j, 0, m) {
            char x; cin >> x;
            grid[i][j] = x == 'B';
        }
    }

    vector<pii> odd = {{1, 3}, {1, 5}, {2, 1}, {2, 3}, {2, 5}, {3, 2}, {3, 4}, {4, 1}, {4, 3}, {4, 5}, {5, 3}, {5, 5}};

    int a0 = 100, a1 = 100;
    rep(x, 0, (1 << 12)) {
        vector<vi> arr = grid;
        int cand = 0;
        rep(i, 0, 12) {
            if (x & (1 << i)) {
                pii pos = odd[i];
                arr[pos.first][pos.second] ^= 1;
                cand++;
            }
        }

        bool good = true;
        rep(i, 1, n - 1) {
            rep(j, 1, m - 1) {
                if ((i + j) % 2 == 0) continue;
                if (arr[i][j] && arr[i - 1][j - 1] && arr[i - 1][j + 1] && arr[i + 1][j - 1] && arr[i + 1][j + 1]) {
                    good = false;
                    break;
                }
            }
        }

        if (good) {
            a0 = min(a0, cand);
        }
    }

    vector<pii> even = {{1, 3}, {3, 1}, {5, 3}, {3, 5}, {2, 2}, {2, 4}, {3, 3}, {4, 2}, {4, 4}};

    rep(x, 0, (1 << 9)) {
        vector<vi> arr = grid;
        int cand = 0;
        rep(i, 0, 9) {
            if (x & (1 << i)) {
                pii pos = even[i];
                arr[pos.first][pos.second] ^= 1;
                cand++;
            }
        }

        bool good = true;
        rep(i, 1, n - 1) {
            rep(j, 1, m - 1) {
                if ((i + j) % 2 == 1) continue;
                if (arr[i][j] && arr[i - 1][j - 1] && arr[i - 1][j + 1] && arr[i + 1][j - 1] && arr[i + 1][j + 1]) {
                    good = false;
                    break;
                }
            }
        }

        if (good) {
            a1 = min(a1, cand);
        }
    }

    cout << a0 + a1 << endl;
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