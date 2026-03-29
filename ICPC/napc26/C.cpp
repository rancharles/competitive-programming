/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-20
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
// #define int long long

const int MAX_N = 1e5 + 1;
const ll MOD = 998244353;

void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    int k = n * m;
    vector<vector<pair<int, int>>> b(k);
    rep(i, 0, n) {
        rep(j, 0, m) {
            cin >> a[i][j];
            if (a[i][j] < k) {
                b[a[i][j]].push_back({j, i});
            }
        }
    }
    // return;
    rep(i, 0, k) {
        if (b[i].empty()) {
            cout << i;
            return;
        }
        if (a[0][0] == i || a[n - 1][m - 1] == i) {
            continue;
        }
        sort(all(b[i]));
        vector<pair<int, int>> cur;
        int tot = 0;
        vector<vector<pair<int, int>>> c;
        if (b[i][0].first != 0) {
            c.push_back({{n, tot}});
            tot++;

            // if (i == 4) {
            //     for (auto [x, y]: c.back()) {cout << x << ' ' << y << '\n';}cout << '\n';
            //     }
        }
        cur.push_back({b[i][0].second, tot});
        tot++;
        rep(j, 1, b[i].size()) {
            if (b[i][j].first == b[i][j - 1].first) {
                cur.push_back({b[i][j].second, tot});
                tot++;
            } else if (b[i][j].first == b[i][j - 1].first + 1) {
                cur.push_back({n, tot});
                c.push_back(cur);

                // if (i == 4) {
                // for (auto [x, y]: c.back()) {cout << x << ' ' << y << '\n';}cout << '\n';
                // }

                tot++;
                cur = {};

                cur.push_back({b[i][j].second, tot});
                tot++;
            } else {
                cur.push_back({n, tot});
                c.push_back(cur);
                tot++;
                cur = {};
                // if (i == 4) {
                // for (auto [x, y]: c.back()) {cout << x << ' ' << y << '\n';}cout << '\n';
                // }
                c.push_back({{n, tot}});
                tot++;

                // if (i == 4) {
                // for (auto [x, y]: c.back()) {cout << x << ' ' << y << '\n';}cout << '\n';
                // }

                cur.push_back({b[i][j].second, tot});
                tot++;
            }
        }
        if (b[i].back().first != m - 1) {
            cur.push_back({n, tot});
            c.push_back(cur);
            

            // if (i == 4) {
            //     for (auto [x, y]: c.back()) {cout << x << ' ' << y << '\n';}cout << '\n';
            //     }
            tot++;
            c.push_back({{n, tot}});
            // if (i == 4) {
            //     for (auto [x, y]: c.back()) {cout << x << ' ' << y << '\n';}cout << '\n';
            //     }
            tot++;
        } else {
            cur.push_back({n, tot});
            c.push_back(cur);

            // if (i == 4) {
            //     for (auto [x, y]: c.back()) {cout << x << ' ' << y << '\n';}cout << '\n';
            //     }

            tot++;
        }
        vector<vector<int>> g(tot);
        c[0].insert((c[0].begin()), {-1, -1});
        rep(j, 1, c.size()) {
            c[j].insert(c[j].begin(), {-1, -1});
            int l = 0;
            rep(d, 1, c[j].size()) {
                l = max(0, l - 10);
                while (l + 1 < c[j - 1].size() && c[j - 1][l].first <= c[j][d].first) {
                    int pl = max(c[j - 1][l].first + 1, c[j][d - 1].first + 1), pr = min(c[j - 1][l + 1].first - 1, c[j][d].first - 1);
                    if (pl <= pr) {
                        g[c[j - 1][l + 1].second].push_back(c[j][d].second);
                        // cout << 
                        // if (i == 4) {
                            cout << c[j - 1][l + 1].second << ' ' << c[j][d].second << '\n';
                        // }
                    }
                    l++;
                }
            }
        }
        vector<bool> vis(tot);
        queue<int> q;
        q.push(0);
        while (q.size()) {
            int t = q.front();
            q.pop();
            if (vis[t]) {
                continue;
            }
            vis[t] = 1;
            for (int v: g[t]) {
                if (vis[v]) {
                    continue;
                }
                q.push(v);
            }
        }
        if (vis.back()) {
            cout << i;
            return;
        }
        // break;
    }
    cout << k;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc;
    cin >> tc;
    for (int t = 1; t <= tc; ++t){
        // cout << "Case #" << t << ": ";
        solve();
        cout << '\n';
    }
    return 0;
}