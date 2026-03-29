/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-14
 * Contest: 
 * Problem: B
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
    int n, k, p, m; cin >> n >> k >> p >> m;
    --p;

    vi cost(n);
    rep(i, 0, n) cin >> cost[i];

    pii win = {cost[p], p};

    set<pii> small;
    queue<pii> remain;

    int ans = 0;

    rep(i, 0, k) {
        small.insert({cost[i], i});
    }

    rep(i, k, n) {
        remain.push({cost[i], i});
    }

    int curr = 0;
    while (curr <= m) {
        auto winFind = small.find(win);
        if (winFind != small.end()) {
            if (cost[p] + curr <= m) {
                curr += cost[p];
                ans++;
                small.erase(winFind);
                remain.push(win);
                small.insert(remain.front());
                remain.pop();
                continue;
            }
            break;
        }

        auto bestFind = small.begin();
        if (bestFind->first + curr <= m) {
            curr += bestFind->first;
            remain.push(*bestFind);
            small.erase(bestFind);
            small.insert(remain.front());
            remain.pop();

            continue;
        }

        break;
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