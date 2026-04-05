/**
 * Template by 1egend (polarity.sh)
 * Template: graph
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
const ll INF = LLONG_MAX;

/** 
 * ALGORITHM: 0/1 BFS 
 * PURPOSE: Finds shortest path in 0/1 weighted simple graph front node x to all nodes
 * CONSTRAINT: x < n
 * TIME: O(V + E)
*/
vector<int> deque_bfs(int n, vector<vector<pair<int, int>>> &adj, int x){
    vector<int> d(n, INF);
    d[x] = 0;
    deque<int> q;
    q.push_front(x);
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (auto edge : adj[v]) {
            int u = edge.first;
            int w = edge.second;
            if (d[v] + w < d[u]) {
                d[u] = d[v] + w;
                if (w == 1)
                    q.push_back(u);
                else
                    q.push_front(u);
            }
        }
    }

    return d;
}

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

/** 
 * DS: Disjoint Set Union 
 * PURPOSE: Dynamically updates connectedness of graph by adding edges
 * TIME: amortized O(a(N)) to query
*/
class DSU {
    private: 
        vector<int> parents;
        vector<int> sizes;
    
    public:
        DSU(int size) : parents(size), sizes(size, 1){
            for (int i = 0; i < size; i++){
                parents[i] = i;
            }
        }

        int find(int x){
            return (parents[x] == x ? x : (parents[x] = find(parents[x])));
        }

        bool unite(int a, int b){
            int parentA = find(a);
            int parentB = find(b);
            if (parentA == parentB){
                return false;
            }

            if (sizes[parentA] > sizes[parentB]){
                swap(parentA, parentB);
            }

            sizes[parentB] += sizes[parentA];
            parents[parentA] = parentB;
            return true;
        }

        bool connected(int a, int b){
            return find(a) == find(b);
        }
};


/** 
 * ALGORITHM: Hierholzer's Algorithm
 * PURPOSE: Finds eulerian path/cycle, returns empty if not found. Modify s/ret to include .second for edge indices.
 * TIME: O(V + E)
 * SOURCE: KACTL
*/
vi hierholzer(vector<vector<pii>>& gr, int nedges, int src=0) {
	int n = sz(gr);
	vi D(n), its(n), eu(nedges), ret, s = {src};
	D[src]++; // to allow Euler paths, not just cycles
	while (!s.empty()) {
		int x = s.back(), y, e, &it = its[x], end = sz(gr[x]);
		if (it == end){ ret.push_back(x); s.pop_back(); continue; }
		tie(y, e) = gr[x][it++];
		if (!eu[e]) {
			D[x]--, D[y]++;
			eu[e] = 1; s.push_back(y);
		}}
	for (int x : D) if (x < 0 || sz(ret) != nedges+1) return {};
	return {ret.rbegin(), ret.rend()};
}
vector<pii> hierholzerEdge(vector<vector<pii>>& gr, int nedges, int src=0) {
	int n = sz(gr);
	vi D(n), its(n), eu(nedges); vector<pii> ret, s = {{src, -1}};
	D[src]++; // to allow Euler paths, not just cycles
	while (!s.empty()) {
		auto [x, pe] = s.back(); int y, e, &it = its[x], end = sz(gr[x]);
		if (it == end){ ret.push_back({x, pe}); s.pop_back(); continue; }
		tie(y, e) = gr[x][it++];
		if (!eu[e]) {
			D[x]--, D[y]++;
			eu[e] = 1; s.push_back({y, e});
		}}
	for (int x : D) if (x < 0 || sz(ret) != nedges+1) return {};
	return {ret.rbegin(), ret.rend()};
}

/** 
 * ALGORITHM: Bellman-Ford
 * PURPOSE: Finds SSSP with negative weights.
 * CONSTRAINT: V^2 max w < 2^63
 * TIME: O(VE)
 * SOURCE: KACTL
*/
const ll inf = LLONG_MAX;
struct Ed { int a, b, w; int s() { return a < b ? a : -a; } };
struct Node { ll dist = inf; int prev = -1; };

void bellmanFord(vector<Node>& nodes, vector<Ed>& eds, int s) {
	nodes[s].dist = 0;
	sort(all(eds), [](Ed a, Ed b) { return a.s() < b.s(); });

	int lim = sz(nodes) / 2 + 2; // /3+100 with shuffled vertices
	rep(i,0,lim) for (Ed ed : eds) {
		Node cur = nodes[ed.a], &dest = nodes[ed.b];
		if (abs(cur.dist) == inf) continue;
		ll d = cur.dist + ed.w;
		if (d < dest.dist) {
			dest.prev = ed.a;
			dest.dist = (i < lim-1 ? d : -inf);
		}
	}
	rep(i,0,lim) for (Ed e : eds) {
		if (nodes[e.a].dist == -inf)
			nodes[e.b].dist = -inf;
	}
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    return 0;
}