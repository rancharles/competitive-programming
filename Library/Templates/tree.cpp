/**
 * Template by 1egend (polarity.sh)
 * Template: tree
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

/** 
 * ALGORITHM: Euler Tour
 * PURPOSE: Flattens a tree so that each range contains any subtree range
 * CONSTRAINT: Graph must be a tree
 * TIME: O(V)
*/
vector<pii> eulerTour(int n, vector<vector<int>> &adj){
    vector<pii> ans(n);
    int i = -1;
    function<void(int, int)> tour;
    tour = [&](int node, int parent){
        ans[node].first = ++i;
        for (int x : adj[node]){
            if (x != parent){
                tour(x, node);
            }
        }
        ans[node].second = i;
    };

    // root at 0
    tour(0, 0);

    return ans;
}

/**
 * ALGORITHM: Lowest Common Ancestor
 * PURPOSE: Lowest common ancestor node of two nodes, also supports depth and distance of nodes
 * TIME: O(n log n) preprocessing, O(1) lca query
 * REQUIRE: Sparse Table (or another RMQ structure)
 */
class LCA {
    private: 
        /** IN SEGTREE REMEMBER TO SET UNIT = pii{INT_MAX, INT_MAX} */
        SparseTable<pii> st;
        vi first;
        vi tour;
        vi d;

    public:
        LCA(int n, vector<vector<int>> &adj) : first(n), tour(2 * n - 1), d(n) {
            int i = -1;
            function<void(int, int, int)> dfs;
            dfs = [&](int node, int parent, int depth){
                tour[++i] = node;
                first[node] = i;
                d[node] = depth;
                for (int x : adj[node]){
                    if (x != parent){
                        dfs(x, node, depth + 1);
                        tour[++i] = node;
                    }
                }
            };

            // root at 0
            dfs(0, 0, 0);

            vector<pii> table(2 * n - 1);

            rep(i, 0, 2 * n - 1){
                table[i] = {d[tour[i]], tour[i]};
            }

            st.build(table);

            /**
             * rep(i, 0, 2 * n - 1){
                st.set(i, {d[tour[i]], tour[i]});
                }
             */
        }

        int depth(int node){
            return d[node];
        }

        int lca(int a, int b){
            pii range = minmax(first[a], first[b]);
            /** IN SPARSE TABLE REMEMBER TO USE INCLUSIVE BOUND range.second, Segtree use exclusive bound range.second + 1 */
            return st.query(range.first, range.second).second;
        }

        int dist(int a, int b){
            return d[a] + d[b] - 2 * d[lca(a, b)];
        }
};

/**
 * Binary jumping
int lg = log2(n) + 1;
vector<vi> jp(n + 1, vi(lg, n));
vector<vector<pii>> jmp(n + 1, vector<pii>(lg, {n, 0}));

rep(j, 1, lg){
    rep(i, 0, n){
        int k = jp[i][j - 1];
        jp[i][j] = jp[k][j - 1];
    }
}

rep(j, 1, lg){
    rep(i, 0, n){
        pii a = jmp[i][j - 1];
        pii b = jmp[a.first][j - 1];
        jmp[i][j] = {b.first, a.second + b.second};
    }
}
 */

/** A data structure that can answer point update & range max queries. */
template <class T> class MaxSegmentTree {
  private:
	// const T DEFAULT = std::numeric_limits<T>().max();
	const T DEFAULT = 0;

	int len;
	vector<T> segtree;

  public:
	MaxSegmentTree(int len) : len(len), segtree(len * 2, DEFAULT) {}

	void set(int ind, T val) {
		ind += len;
		segtree[ind] = val;
		for (; ind > 1; ind /= 2) {
			segtree[ind / 2] = std::max(segtree[ind], segtree[ind ^ 1]);
		}
	}

	T range_max(int start, int end) {
		T max = DEFAULT;
		for (start += len, end += len; start < end; start /= 2, end /= 2) {
			if (start % 2 == 1) { max = std::max(max, segtree[start++]); }
			if (end % 2 == 1) { max = std::max(max, segtree[--end]); }
		}
		return max;
	}
};

template <class T, bool VALS_IN_EDGES> class HLD {
  private:
	int N, R, tim = 0;  // n, root node, time
	vector<vector<int>> adj;
	vector<int> par, siz, depth, rt, pos;  // parent, size, depth, root, position arrays
	MaxSegmentTree<T> segtree;             // Modify as needed

	/** Compute the size of each subtree and set parent-child relationship
	 * Subtree of node v corresponds to segment [ pos[v], pos[v] + sz[v] ) */
	void dfs_sz(int v) {
		if (par[v] != -1) adj[v].erase(find(adj[v].begin(), adj[v].end(), par[v]));
		for (int &u : adj[v]) {
			par[u] = v, depth[u] = depth[v] + 1;
			dfs_sz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}

	/** Assign positions for nodes
	  * Path from v to the last vertex in ascending heavy path
	    corresponds to [ pos[rt[v]], pos[v] ] */
	void dfs_hld(int v) {
		pos[v] = tim++;
		for (int u : adj[v]) {
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfs_hld(u);
		}
	}

	/** process all heavy path and combine their results */
	template <class B> void process(int u, int v, B op) {
		for (; rt[u] != rt[v]; v = par[rt[v]]) {
			if (depth[rt[u]] > depth[rt[v]]) swap(u, v);
			op(pos[rt[v]], pos[v]);
		}
		if (depth[u] > depth[v]) swap(u, v);
		op(pos[u] + VALS_IN_EDGES, pos[v]);
	}

  public:
	HLD(vector<vector<int>> adj_, int _R)
	    : N(adj_.size()), R(_R), adj(adj_), par(N, -1), siz(N, 1), depth(N), rt(N),
	      pos(N), segtree(N)  // modify as needed
	{
		rt[R] = R;
		dfs_sz(R);
		dfs_hld(R);
	}

	T query_path(int u, int v) {
		T res = 0;  // default value, modify depending on problem
		process(u, v, [&](int l, int r) {
			res = max(res, segtree.range_max(l, r + 1));  // modify depending on problem
		});
		return res;
	}

	void modify_node(int u, T val) { segtree.set(pos[u], val); }
};

// int main() {
// 	ios_base::sync_with_stdio(false);
// 	cin.tie(0);

// 	int n, q;
// 	cin >> n >> q;
// 	vector<int> v(n);
// 	vector<vector<int>> adj(n);
// 	for (int i = 0; i < n; i++) { cin >> v[i]; }

// 	for (int i = 0; i < n - 1; i++) {
// 		int a, b;
// 		cin >> a >> b;
// 		--a, --b;
// 		adj[a].push_back(b);
// 		adj[b].push_back(a);
// 	}

// 	HLD<int, 0> H(adj, 0);

// 	for (int i = 0; i < n; i++) { H.modify_node(i, v[i]); }

// 	while (q--) {
// 		int type, s, a, b, x;
// 		cin >> type;
// 		if (type == 1) {
// 			cin >> s >> x;
// 			--s;
// 			H.modify_node(s, x);
// 		} else if (type == 2) {
// 			cin >> a >> b;
// 			--a, --b;
// 			cout << H.query_path(a, b) << " ";
// 		}
// 	}
// }

/**
 * DATASTRUCTURE: Rooted Link Cut Tree
 * PURPOSE: LCT but rooted, no-rerooting, good for storing per-component info through root keys
 * TIME: Amortized O(log n)
 * SOURCE: ChatGPT-written template, but stress-tested for correctness
 */
namespace rlct {
    struct SNode {
        SNode *ch[2], *p, *pp;

        int siz;    // aux subtree size
        int vsiz;   // virtual contribution size
        int subsz;  // total contribution of aux subtree + virtuals

        ll val;
        ll sum; // aux subtree sum
        ll vir; // virtual contribution sum
        ll sub; // total contribution of aux subtree + virtuals

        SNode(long long _val = 0)
            : ch{nullptr, nullptr}, p(nullptr), pp(nullptr),
              siz(1), vsiz(0), subsz(1),
              val(_val), sum(_val), vir(0), sub(_val) {}
    };

    int gs(SNode* x) { return x ? x->siz : 0; }
    int gsubsz(SNode* x) { return x ? x->subsz : 0; }
    ll gsum(SNode* x) { return x ? x->sum : 0; }
    ll gsub(SNode* x) { return x ? x->sub : 0; }

    void pull(SNode* x) {
        if (!x) return;
        x->siz = 1 + gs(x->ch[0]) + gs(x->ch[1]);
        x->sum = x->val + gsum(x->ch[0]) + gsum(x->ch[1]);

        // total contribution of the whole auxiliary subtree segment
        x->subsz = 1 + gsubsz(x->ch[0]) + gsubsz(x->ch[1]) + x->vsiz;
        x->sub   = x->val + gsub(x->ch[0]) + gsub(x->ch[1]) + x->vir;
    }

    bool is_aux_root(SNode* x) {
        return !x->p || (x->p->ch[0] != x && x->p->ch[1] != x);
    }

    bool side(SNode* x) {
        return x->p->ch[1] == x;
    }

    void attach(SNode* p, SNode* c, int d) {
        if (p) p->ch[d] = c;
        if (c) c->p = p;
    }

    void rotate(SNode* x) {
        SNode* p = x->p;
        SNode* g = p->p;
        int dx = side(x);

        if (!is_aux_root(p)) {
            attach(g, x, side(p));
        } else {
            x->p = nullptr;
        }

        attach(p, x->ch[dx ^ 1], dx);
        attach(x, p, dx ^ 1);

        x->pp = p->pp;
        p->pp = nullptr;

        pull(p);
        pull(x);
    }

    void splay(SNode* x) {
        while (!is_aux_root(x)) {
            SNode* p = x->p;
            if (!is_aux_root(p)) {
                if (side(x) == side(p)) rotate(p);
                else rotate(x);
            }
            rotate(x);
        }
        pull(x);
    }

    void detach_right(SNode* x) {
        if (x->ch[1]) {
            SNode* r = x->ch[1];
            r->pp = x;
            r->p = nullptr;

            x->vsiz += r->subsz;
            x->vir += r->sub;

            x->ch[1] = nullptr;
            pull(x);
        }
    }

    void attach_right_preferred(SNode* x, SNode* c) {
        if (c) {
            x->vsiz -= c->subsz;
            x->vir -= c->sub;
            attach(x, c, 1);
        } else {
            x->ch[1] = nullptr;
        }
        pull(x);
    }

    SNode* access(SNode* x) {
        splay(x);
        detach_right(x);

        SNode* last = x;
        while (x->pp) {
            SNode* w = x->pp;
            last = w;
            splay(w);
            detach_right(w);

            x->pp = nullptr;
            attach_right_preferred(w, x);

            splay(x);
        }
        return last;
    }

    SNode* make_node(long long val = 0) {
        return new SNode(val);
    }

    SNode* find_root(SNode* x) {
        access(x);
        while (x->ch[0]) x = x->ch[0];
        access(x);
        return x;
    }

    bool connected(SNode* u, SNode* v) {
        return find_root(u) == find_root(v);
    }

    void cut(SNode* x) {
        access(x);
        assert(x->ch[0] != nullptr);
        x->ch[0]->p = nullptr;
        x->ch[0] = nullptr;
        pull(x);
    }

    void link(SNode* child, SNode* par) {
        assert(!connected(par, child));
        access(child);
        assert(child->ch[0] == nullptr); // child must be represented-tree root
        access(par);
        attach(child, par, 0);
        pull(child);
    }

    SNode* lca(SNode* u, SNode* v) {
        if (!connected(u, v)) return nullptr;
        access(u);
        return access(v);
    }

    int dist_root(SNode* x) {
        access(x);
        return x->siz - 1;
    }

    int dist(SNode* u, SNode* v) {
        SNode* a = lca(u, v);
        if (!a) return -1;
        return dist_root(u) + dist_root(v) - 2 * dist_root(a);
    }

    void add_val(SNode* x, long long delta) {
        access(x);
        x->val += delta;
        pull(x);
    }

    void set_val(SNode* x, long long v) {
        access(x);
        x->val = v;
        pull(x);
    }

    // root -> x path sum
    long long path_sum_root(SNode* x) {
        access(x);
        return x->sum;
    }

    // u -> v path sum
    long long path_sum(SNode* u, SNode* v) {
        SNode* a = lca(u, v);
        if (!a) return 0;
        return path_sum_root(u) + path_sum_root(v) - 2 * path_sum_root(a) + a->val;
    }

    // represented subtree of x
    int subtree_size(SNode* x) {
        access(x);
        return 1 + x->vsiz;
    }

    long long subtree_sum(SNode* x) {
        access(x);
        return x->val + x->vir;
    }
} using namespace rlct;

/**
 * DATASTRUCTURE: Link Cut Tree
 * PURPOSE: Maintains properties of rooted forests
 * SOURCE: Benq
 * TIME: Amortized O(log n)
 */
typedef struct snode *sn;
struct snode {         //////// VARIABLES
	sn p, c[2];        // parent, children
	bool flip = 0;     // subtree flipped or not
	int sz;            // # nodes in current splay tree
	ll sub, vsub = 0;  // vsub stores sum of virtual children
	ll val;            // value in node
	snode(int _val) : val(_val) {
		p = c[0] = c[1] = NULL;
		calc();
	}
	friend int getSz(sn x) { return x ? x->sz : 0; }
	friend ll getSub(sn x) { return x ? x->sub : 0; }
	void prop() {  // lazy prop
		if (!flip) return;
		swap(c[0], c[1]);
		flip = 0;
		for (int i = 0; i < 2; i++)
			if (c[i]) c[i]->flip ^= 1;
	}
	void calc() {  // recalc vals
		for (int i = 0; i < 2; i++)
			if (c[i]) c[i]->prop();
		sz = 1 + getSz(c[0]) + getSz(c[1]);
		sub = val + getSub(c[0]) + getSub(c[1]) + vsub;
	}
	//////// SPLAY TREE OPERATIONS
	int dir() {
		if (!p) return -2;
		for (int i = 0; i < 2; i++)
			if (p->c[i] == this) return i;
		return -1;  // p is path-parent pointer
	}  // -> not in current splay tree
	// test if root of current splay tree
	bool isRoot() { return dir() < 0; }
	friend void setLink(sn x, sn y, int d) {
		if (y) y->p = x;
		if (d >= 0) x->c[d] = y;
	}
	void rot() {  // assume p and p->p propagated
		assert(!isRoot());
		int x = dir();
		sn pa = p;
		setLink(pa->p, this, pa->dir());
		setLink(pa, c[x ^ 1], x);
		setLink(this, pa, x ^ 1);
		pa->calc();
	}
	void splay() {
		while (!isRoot() && !p->isRoot()) {
			p->p->prop(), p->prop(), prop();
			dir() == p->dir() ? p->rot() : rot();
			rot();
		}
		if (!isRoot()) p->prop(), prop(), rot();
		prop();
		calc();
	}
	sn fbo(int b) {  // find by order
		prop();
		int z = getSz(c[0]);  // of splay tree
		if (b == z) {
			splay();
			return this;
		}
		return b < z ? c[0]->fbo(b) : c[1]->fbo(b - z - 1);
	}
	//////// BASE OPERATIONS
	void access() {  // bring this to top of tree, propagate
		for (sn v = this, pre = NULL; v; v = v->p) {
			v->splay();  // now switch virtual children
			if (pre) v->vsub -= pre->sub;
			if (v->c[1]) v->vsub += v->c[1]->sub;
			v->c[1] = pre;
			v->calc();
			pre = v;
		}
		splay();
		assert(!c[1]);  // right subtree is empty
	}
	void makeRoot() {
		access();
		flip ^= 1;
		access();
		assert(!c[0] && !c[1]);
	}
	//////// QUERIES
	friend sn lca(sn x, sn y) {
		if (x == y) return x;
		x->access(), y->access();
		if (!x->p) return NULL;
		x->splay();
		return x->p ?: x;  // y was below x in latter case
	}  // access at y did not affect x -> not connected
	friend bool connected(sn x, sn y) { return lca(x, y); }
	// # nodes above
	int distRoot() {
		access();
		return getSz(c[0]);
	}
	sn getRoot() {  // get root of LCT component
		access();
		sn a = this;
		while (a->c[0]) a = a->c[0], a->prop();
		a->access();
		return a;
	}
	sn getPar(int b) {  // get b-th parent on path to root
		access();
		b = getSz(c[0]) - b;
		assert(b >= 0);
		return fbo(b);
	}  // can also get min, max on path to root, etc
	//////// MODIFICATIONS
	void set(int v) {
		access();
		val = v;
		calc();
	}
	friend void link(sn x, sn y, bool force = 0) {
		assert(!connected(x, y));
		if (force) y->makeRoot();  // make x par of y
		else {
			y->access();
			assert(!y->c[0]);
		}
		x->access();
		setLink(y, x, 0);
		y->calc();
	}
	friend void cut(sn y) {  // cut y from its parent
		y->access();
		assert(y->c[0]);
		y->c[0]->p = NULL;
		y->c[0] = NULL;
		y->calc();
	}
	friend void cut(sn x, sn y) {  // if x, y adj in tree
		x->makeRoot();
		y->access();
		assert(y->c[0] == x && !x->c[0] && !x->c[1]);
		cut(y);
	}
};