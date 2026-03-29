/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-14
 * Contest: 
 * Problem: D2
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

/** 
 * ALGORITHM: Topological Sort
 * PURPOSE: Sorts a DAG's vertices such that each directed edge points forward
 * CONSTRAINT: Graph must be a DAG
 * TIME: O(V)
*/
vector<int> toposort(int n, vector<vector<int>> &adj){
    vector<int> degree(n, 0);
    queue<int> q; // use pq for lexicographical sorting
    for (int i = 0; i < n; i++){
        for (int j : adj[i]){
            degree[j]++;
        }
    }

    for (int i = 0; i < n; i++){
        if (degree[i] == 0){
            q.push(i);
        }
    }

    vector<int> ans;

    while(!q.empty()){
        int i = q.front();
        ans.pb(i);
        q.pop();

        for (int j : adj[i]){
            if (degree[j] == 0){
                continue;
            }

            degree[j]--;
            if (degree[j] == 0){
                q.push(j);
            }
        }
    }

    return ans;
}

void solve(){
    int n; cin >> n;

    bool diag = false;
    vector<vector<bool>> has(n, vector<bool>(n, false));
    vector<vi> adj(n);
    rep(i, 0, n) {
        rep(j, 0, n) {
            char x; cin >> x;
            has[i][j] = x == '1';
            if (i == j && x != '1') {
                diag = true;
            }

            if (x == '1' && i != j) {
                adj[i].pb(j);
            }
        }
    }

    if (diag) {
        cout << "No" << endl;
        return;
    }

    vi ord = toposort(n, adj);

    if (sz(ord) != n) {
        cout << "No" << endl;
        return;
    }

    vector<vi> radj(n);
    vector<vi> aadj(n);
    vector<pii> ans;
    vector<bool> visited(n, false);
    function<void(int, vi&)> dfs;
    dfs = [&](int node, vi& reach) {
        reach.pb(node);
        visited[node] = true;
        for (int x : radj[node]) {
            if (visited[x]) continue;
            dfs(x, reach);
        }
    };

    bool cycle = false;
    function<void(int, int)> dfscycle;
    dfscycle = [&](int node, int par) {
        visited[node] = true;
        for (int x : aadj[node]) {
            if (x == par) continue;
            if (visited[x]) {
                cycle = true;
                continue;
            }
            dfscycle(x, node);
        }
    };

    for (int i = n - 1; i >= 0; i--) {
        int node = ord[i];
        vi sadj;
        rep(j, i + 1, n) {
            int jnode = ord[j];
            if (has[node][jnode]) {
                sadj.pb(jnode);
            }
        }

        vi reachable = {node};
        visited = vector<bool>(n, false);

        for (int x : sadj) {
            if (visited[x]) continue;
            radj[node].pb(x);
            aadj[node].pb(x);
            aadj[x].pb(node);
            ans.pb({node, x});
            dfs(x, reachable);
        }

        for (int x : reachable) {
            if (!has[node][x]) {
                cout << "No" << endl;
                return;
            }
        }

        visited = vector<bool>(n, false);
        dfscycle(node, -1);
        if (cycle) {
            cout << "No" << endl;
            return;
        }
    }

    if (sz(ans) != n - 1) {
        cout << "No" << endl;
        return;
    }

    cout << "Yes" << endl;
    for (pii e : ans) {
        cout << 1 + e.first << " " << 1 + e.second << "\n";
    }
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