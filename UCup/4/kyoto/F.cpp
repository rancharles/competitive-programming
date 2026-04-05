/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-04-04
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

const ll MAX_N = 1e16;
const ll MOD = 1e9 + 7;

ull modmul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}
ull pollard(ull n) {
	ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	auto f = [&](ull x) { return modmul(x, x, n) + i; };
	while (t++ % 40 || __gcd(prd, n) == 1) {
		if (x == y) x = ++i, y = f(x);
		if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return __gcd(prd, n);
}
bool isPrime(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n >> s;
	for (ull a : A) {   // ^ count trailing zeroes
		ull p = modpow(a%n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}
vector<ll> factor(ll n) {
	if (n == 1) return {};
	if (isPrime(n)) return {n};
	ll x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), all(r));
	return l;
}

void divisors(vector<pair<ll, ll>> &div, int i, ll curr, vl& divs) {
    if (i == sz(div)) {
        divs.pb(curr);
        return;
    }

    auto [p, e] = div[i];
    rep(j, 0, e + 1) {
        divisors(div, i + 1, curr, divs);
        curr *= p;
    }
}

vl factors(ll b) {
    vl db;
    ll rt = sqrt(b);
    rep(d, 1, rt + 1) {
        if (b % d != 0) continue;
        db.pb(d);
        ll dd = b/d;
        if (dd != d) {
            db.pb(dd);
        }
    }

    return db;
}

void solve(){
    ll a, b; cin >> a >> b;

    vl db = factors(b);

    map<ll, vl> adj;
    vl good;

    for (ll d : db) {
        ll k = a + b/d;

        vl dk = factors(k);

        for (ll a : dk) {
            ll b = k/a;
            if (__gcd(a, b) != 1) continue;
            if (d * a > MAX_N || d * b > MAX_N) continue;
            
            good.pb(d * a);
            good.pb(d * b);

            adj[d * a].pb(d * b);
            adj[d * b].pb(d * a);
        }
    }

    map<ll, bool> visited;

    vl comp;
    function<void(ll)> dfs;
    dfs = [&](ll node) {
        comp.pb(node);
        visited[node] = true;
        for (ll x : adj[node]) {
            if (visited[x]) continue;
            dfs(x);
        }
    };

    map<ll, ll> ans;
    for (ll x : good) {
        if (visited[x]) continue;
        comp = {};
        dfs(x);

        ll curr = 0;
        for (ll node : comp) {
            curr ^= node;
        }

        for (ll node : comp) {
            ans[node] = curr;
        }
    }

    int q; cin >> q;
    rep(qq, 0, q) {
        ll x; cin >> x;

        if (ans.contains(x)) {
            cout << ans[x] << "\n";
        } else {
            cout << x << "\n";
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}