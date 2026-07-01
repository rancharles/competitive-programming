/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-06-30
 * Contest: 
 * Problem: G
**/

#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using sll = __int128;
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

const int MAX_N = 1e5 + 1;
const ll MOD = 1e9 + 7;

sll read() {
    sll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

void print(sll x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

/** 
 * DATASTRUCTURE: Segment Tree
 * PURPOSE: Range Updates and Queries
 * TIME: O(log n) to update and query
*/
template <class T> class SegmentTree {
  private:
	const T UNIT = 0;

    T combine(T a, T b){
        return __gcd(a, b);
    }

	vector<T> segtree;
	int len;

  public:
	SegmentTree(int len) : len(len), segtree(len * 2, UNIT) {}

	void set(int ind, T val) {
		ind += len;
		segtree[ind] = val;
		for (; ind > 1; ind /= 2) {
			segtree[ind / 2] = combine(segtree[ind], segtree[ind ^ 1]);
		}
	}

    // [start, end)
	T query(int start, int end) {
		T ans = UNIT;
		for (start += len, end += len; start < end; start /= 2, end /= 2) {
			if (start % 2 == 1) { ans = combine(ans, segtree[start++]); }
			if (end % 2 == 1) { ans = combine(ans, segtree[--end]); }
		}
		return ans;
	}
};

void solve(){
    int n; cin >> n;
    vl arr(n);
    rep(i, 0, n) {
        cin >> arr[i];
    }

    SegmentTree<ll> st(n);
    rep(i, 0, n) {
        st.set(i, arr[i]);
    }

    sll ans = 0;

    vi neq(n, n);
    for (int i = n - 2; i >= 0; i--) {
        if (arr[i] == arr[i + 1]) {
            neq[i] = neq[i + 1];
        } else {
            neq[i] = i + 1;
        }
    }

    rep(l, 0, n) {
        ll g = st.query(l + 1, n);
        if (g % arr[l] == 0) {
            continue;
        }

        int lo = l + 1, hi = n - 1;
        while (lo < hi) {
            int mid = (lo + hi)/2;
            ll g = st.query(l + 1, mid + 1);
            if (g % arr[l] == 0) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }

        int r = lo;
        ll md = arr[r] % arr[l];
        ll a = min(md, arr[l] - md);
        ans += a * (n - r);
    }

    print(ans);
    putchar('\n');
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