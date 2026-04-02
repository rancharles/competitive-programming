/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-04-01
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
const ll INF = 1e18;

/** 
 * ALGORITHM: Dijkstra's Algorithm
 * PURPOSE: Finds shortest path in nonnegative weighted simple graph from node x to all nodes
 * TIME: O(V + E)
*/
vector<ll> dijkstra(int n, vector<vector<pair<int, ll>>> &adj, int x){
    vector<ll> d(n, INF);
    d[x] = 0;

    using T = pair<ll, int>;
    priority_queue<T, vector<T>, greater<T>> pq;

    pq.push({0, x});

    while(!pq.empty()){
        auto [dist, k] = pq.top();
        pq.pop();

        if (dist != d[k]) { continue; }

        for (pair<int, ll> &node: adj[k]){
            if (dist + node.second < d[node.first]){
                d[node.first] = dist + node.second;
                pq.push({d[node.first], node.first});
            }
        }
    }

    return d;
}

void solve(){
    int n, m; cin >> n >> m;

    vector<vector<pair<int, ll>>> adj(n);
    rep(i, 0, m) {
        int a, b; cin >> a >> b;
        --a; --b;
        if (a > b) {
            swap(a, b);
        }
        ll w; cin >> w;
        adj[a].pb({b, w});
    }

    vl d = dijkstra(n, adj, 0);
    rep(i, 1, n) {
        if (d[i] == INF) {
            cout << -1 << "\n";
        } else {
            cout << d[i] << "\n";
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}