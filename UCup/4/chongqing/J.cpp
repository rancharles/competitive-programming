/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-29
 * Contest: 
 * Problem: J
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
 * DATASTRUCTURE: Lazy Segment Tree
 * PURPOSE: Segment Tree with lazy updates
 * TIME: O(log n) to update and query
*/
template <class Info, class Tag> class LazySegtree {
  private:
	const int n;
	vector<Info> tree;
	vector<Tag> lazy;

	/** builds the segtree values in O(N) time */
	void build(int v, int l, int r, const vector<Info> &a) {
		if (l == r) {
			tree[v] = a[l];
		} else {
			int m = (l + r) / 2;
			build(2 * v, l, m, a);
			build(2 * v + 1, m + 1, r, a);
			tree[v] = tree[2 * v] + tree[2 * v + 1];
		}
	}

	/** applies update x to lazy[v] and tree[v] */
	void apply(int v, int l, int r, const Tag &x) {
		tree[v].apply(x, l, r);
		lazy[v].apply(x);
	}

	/** pushes lazy updates down to the children of v */
	void push_down(int v, int l, int r) {
		int m = (l + r) / 2;
		apply(2 * v, l, m, lazy[v]);
		apply(2 * v + 1, m + 1, r, lazy[v]);
		lazy[v] = Tag();
	}

	void range_update(int v, int l, int r, int ql, int qr, const Tag &x) {
		if (qr < l || ql > r) { return; }
		if (ql <= l && r <= qr) {
			apply(v, l, r, x);
		} else {
			push_down(v, l, r);
			int m = (l + r) / 2;
			range_update(2 * v, l, m, ql, qr, x);
			range_update(2 * v + 1, m + 1, r, ql, qr, x);
			tree[v] = tree[2 * v] + tree[2 * v + 1];
		}
	}

	Info range_query(int v, int l, int r, int ql, int qr) {
		if (qr < l || ql > r) { return Info(); }
		if (l >= ql && r <= qr) { return tree[v]; }
		push_down(v, l, r);
		int m = (l + r) / 2;
		return range_query(2 * v, l, m, ql, qr) +
		       range_query(2 * v + 1, m + 1, r, ql, qr);
	}

  public:
	LazySegtree() {}

	LazySegtree(int n) : n(n) {
		tree.assign(4 << __lg(n), Info());
		lazy.assign(4 << __lg(n), Tag());
	}

	LazySegtree(const vector<Info> &a) : n(a.size()) {
		tree.assign(4 << __lg(n), Info());
		lazy.assign(4 << __lg(n), Tag());
		build(1, 0, n - 1, a);
	}

	/** updates [ql, qr] with the arbitrary update chosen */
	void range_update(int ql, int qr, const Tag &x) {
        if (qr < ql) return;
		range_update(1, 0, n - 1, ql, qr, x);
	}

	/** @return result of range query on [ql, qr] */
	Info range_query(int ql, int qr) {
        return range_query(1, 0, n - 1, ql, qr); 
    }
};

enum QueryType { ADD, SET, NONE };

struct Tag {
	QueryType type = NONE;
	ll val = 0;
    ll xrval = 0;
	void apply(const Tag &t) {
		if (t.type == ADD) {
			val += t.val;
			if (type != SET) { type = ADD; }
		} else if (t.type == SET) {
			type = SET;
			val = t.val;
            xrval = t.xrval;
		}
	}
};

struct Info {
	ll mn = 1e9;
    int count = 0;
    ll xr = 0;
	void apply(const Tag &t, int l, int r) {
		if (t.type == SET) {
			mn = t.val;
            count = r - l + 1;
            xr = (r - l + 1) % 2 == 0 ? 0 : t.xrval;
		} else if (t.type == ADD) {
            mn += t.val;
		}
	}
};

/** @return result of joining nodes a and b together */
Info operator+(const Info &a, const Info &b) {
    if (a.mn < b.mn) {
        return a;
    }

    if (b.mn < a.mn) {
        return b;
    }

    return {
        a.mn, a.count + b.count, a.xr ^ b.xr
    };
}

ll getPre(ll n) {
    ll k = n - 1;
    ll big = 0;
    while (k > 0) {
        int t = 63 - __builtin_clzll(k);
        if ((k & 1) == 0) {
            big ^= 1ll << t;
        }
        k ^= 1ll << t;
    }

    ll odd = (n)/2;
    if (odd % 2 == 1) {
        big |= 1;
    } else {
        big = (big/2) * 2;
    }

    return big;
}

void solve(){
    ll n, m, q; cin >> n >> m >> q;

    vl arr(m + 1);
    rep(i, 0, m) {
        cin >> arr[i + 1];
    }

    ll big = getPre(n);

if (n > m) {
    map<ll, set<int>> stuff;
    vl pre(m + 1, 0);
    rep(i, 1, m + 1) {
        ll s = (n - i) % n;
        pre[i] = pre[i - 1] ^ s;
    }
    multiset<int> left, right;

    auto add = [&](ll v) {
        if (v == 0) return;

        if (sz(stuff[v]) > 1) {
            right.insert(*next(stuff[v].begin()));
            left.insert(*prev(prev(stuff[v].end())));
        }
    };

    auto remove = [&](ll v) {
        if (v == 0) return;

        if (sz(stuff[v]) > 1) {
            right.erase(right.find(*next(stuff[v].begin())));
            left.erase(left.find(*prev(prev(stuff[v].end()))));
        }
    };

    rep(i, 1, m + 1) {
        ll x = arr[i];
        remove(x);
        stuff[x].insert(i);
        add(x);
    }
    
    if (left.empty()) {
        cout << n << " " << big << "\n";
    } else {
        int l = *(prev(left.end()));
        int r = *(right.begin());
        --r;
        if (r < l) {
            cout << 0 << " " << 0 << "\n";
        } else {
            cout << r - l + 1 << " " << (pre[r] ^ pre[l - 1]) << "\n";
        }
    }

    rep(qq, 0, q) {
        int a; ll b; cin >> a >> b;
        ll curr = arr[a];
        if (b != curr) {
            remove(curr);
            remove(b);
            arr[a] = b;
            stuff[curr].erase(a);
            stuff[b].insert(a);
            add(curr);
            add(b);
        }

        if (left.empty()) {
            cout << n << " " << big << "\n";
        } else {
            int l = *(prev(left.end()));
            int r = *(right.begin());
            --r;
            if (r < l) {
                cout << 0 << " " << 0 << "\n";
            } else {
                cout << r - l + 1 << " " << (pre[r] ^ pre[l - 1]) << "\n";
            }
        }
    }
    return;
}

    vector<set<int>> stuff(n + 1);
    LazySegtree<Info, Tag> st(n + 1);

    rep(i, 0, n) {
        st.range_update(i, i, Tag{SET, 0, i});
    }

    // b >= a
    auto addBad = [&](int a, int b, int d) {
        a %= n; b %= n;

        int sa = (n + 1 - b) % n;
        int sb = (n - a) % n;

        if (sa <= sb) {
            st.range_update(0, sa - 1, Tag{ADD, d, 0});
            st.range_update(sb + 1, n - 1, Tag{ADD, d, 0});
        } else {
            st.range_update(sb + 1, sa - 1, Tag{ADD, d, 0});
        }
    };

    auto add = [&](int i, int v) {
        arr[i] = v;
        if (v == 0) return;
        auto it = stuff[v].insert(i).first;
        if (it != stuff[v].begin() && it != prev(stuff[v].end())) {
            int a = *prev(it);
            int b = *next(it);

            if (b - a < n) {
                addBad(a, b, -1);
            }
        }

        if (it != stuff[v].begin()) {
            int a = *prev(it);
            int b = *it;

            if (b - a < n) {
                addBad(a, b, 1);
            }
        }

        if (it != prev(stuff[v].end())) {
            int a = *it;
            int b = *next(it);

            if (b - a < n) {
                addBad(a, b, 1);
            }
        }
    };

    auto remove = [&](int i) {
        int v = arr[i];
        if (v == 0) return;
        auto it = stuff[v].find(i);
        if (it != stuff[v].begin() && it != prev(stuff[v].end())) {
            int a = *prev(it);
            int b = *next(it);

            if (b - a < n) {               
                addBad(a, b, 1);
            }
        }

        if (it != stuff[v].begin()) {
            int a = *prev(it);
            int b = *it;

            if (b - a < n) {
                addBad(a, b, -1);
            }
        }

        if (it != prev(stuff[v].end())) {
            int a = *it;
            int b = *next(it);

            if (b - a < n) {
                addBad(a, b, -1);
            }
        }

        stuff[v].erase(it);
    };

    rep(i, 1, m + 1) {
        int x = arr[i];
        add(i, x);
    }

    Info ans = st.range_query(0, n - 1);
    // rep(i, 0, n) {
    //     cout << st.range_query(i, i).mn << endl;
    // }
    if (ans.mn == 0) {
        cout << ans.count << " " << ans.xr << '\n';
    } else {
        cout << 0 << " " << 0 << '\n';
    }

    rep(qq, 0, q) {
        int a, b; cin >> a >> b;
        remove(a);
        add(a, b);

        Info ans = st.range_query(0, n - 1);
        // rep(i, 0, n) {
        //     cout << st.range_query(i, i).mn << endl;
        // }
        if (ans.mn == 0) {
            cout << ans.count << " " << ans.xr << '\n';
        } else {
            cout << 0 << " " << 0 << '\n';
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; ++t){
        // cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}