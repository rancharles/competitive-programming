/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-28
 * Contest: 
 * Problem: D
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

const int MAX_N = 2e5 + 1;
const ll MOD = 1e9 + 7;

/** 
 * ALGORITHM: Modular Exponentiation 
 * PURPOSE: Computes x^n (mod m)
 * CONSTRAINT: m * m <= LLONG_MAX to prevent overflow
 * TIME: O(log n)
*/
ll mod_exp(ll x, ll n, ll m) {
	x %= m;

	ll res = 1;
	while (n > 0) {
		if (n % 2 == 1) { res = res * x % m; }
		x = x * x % m;
		n /= 2;
	}

	return res;
}
/** 
 * PRECOMPUTE: Factorials and Factorial Inverses
 * PURPOSE: Computes factorials and their inverses modulo m
 * REQUIRE: Modular Exponentiation
 * TIME: O(n + log m)
*/
vector<ll> fac(MAX_N + 1);
vector<ll> fac_inv(MAX_N + 1);
void factorial(ll p) {
	fac[0] = 1;
	for (int i = 1; i <= MAX_N; i++) { fac[i] = fac[i - 1] * i % p; }
}
void factorial_inverses(ll p) {
    fac_inv[0] = 1;
	fac_inv[MAX_N] = mod_exp(fac[MAX_N], p - 2, p);
	for (int i = MAX_N; i >= 1; i--) { fac_inv[i - 1] = fac_inv[i] * i % p; }
}
/** 
 * ALGORITHM: Binomial Coefficient
 * PURPOSE: Computes n choose r
 * CONSTRAINT: 0 <= n, r <= MAX_N
 * REQUIRE: Factorials and Factorial Inverses
 * TIME: O(1)
*/
ll choose(ll n, ll r, ll p) {
    if (r > n){
        return 0;
    }
	return fac[n] * fac_inv[r] % p * fac_inv[n - r] % p;
}

void solve(){
    int n; cin >> n;

    ll d = 29;
    vl b(n + 1, (1LL << 29) - 1);
    rep(i, 0, n) {
        cin >> b[i + 1];
    }

    vector<pair<ll, int>> c;
    for (int i = n; i >= 0; i--) {
        ll cand = b[i];
        for (auto [v, j] : c) {
            cand += MOD - (v * choose(j, i, MOD) % MOD);
            cand %= MOD;
        }

        if (cand != 0) {
            c.pb({cand, i});
        }
    }

    vi cnt(29, 0);
    for (auto [v, j] : c) {
        rep(i, 0, d) {
            ll bit = (1LL << i);
            if (v & bit) {
                cnt[i] = j;
            }
        }
    }

    vl ans(n, 0);
    rep(i, 0, 29) {
        rep(j, 0, cnt[i]) {
            ans[j] |= (1LL << i);
        }
    }

    // ll three = 0;
    // rep(i, 0, n) {
    //     rep(j, i + 1, n) {
    //         rep(k, j + 1, n) {
    //             three += ans[i] & ans[j] & ans[k];
    //             three %= MOD;
    //         }
    //     }
    // }

    // cout << three << endl;

    rep(i, 0, n) {
        cout << ans[i] << " ";
    }

    cout << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    factorial(MOD);
    factorial_inverses(MOD);
    int tc;
    cin >> tc;
    for (int t = 1; t <= tc; ++t){
        // cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}