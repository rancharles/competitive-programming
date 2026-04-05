/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-04-04
 * Contest: 
 * Problem: A
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
const ll MOD = 998244353;

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

void solve(){
    int n, k; cin >> n >> k;

    vector<pii> prob(n);
    rep(i, 0, n) {
        int a, b; cin >> a >> b;
        prob[i] = {a, b};
    }

    ll curr = 1;
    rep(i, 0, k - 1) {
        auto [a, b] = prob[i];
        curr *= ((ll)(a) * mod_exp(b, MOD - 2, MOD)) % MOD;
        curr %= MOD;
    }

    ll fa = 0;

    vl ans(n, 0);

    rep(i, k - 1, n) {
        auto [a, b] = prob[i];
        curr *= ((ll)(a) * mod_exp(b, MOD - 2, MOD)) % MOD;
        curr %= MOD;
        
        ll no = 1;
        if (i != k - 1) {
            auto [ap, bp] = prob[i - k];
            curr *= ((ll)(bp) * mod_exp(ap, MOD - 2, MOD)) % MOD;
            curr %= MOD;    
            
            no = ((ll)(bp - ap) * mod_exp(bp, MOD - 2, MOD)) % MOD;
        }

        ll tot = curr * no % MOD;
        int j = i - k - 1;
        if (j >= 0) {
            tot *= (1 + MOD - ans[j]) % MOD;
            tot %= MOD;
        }

        fa += tot;
        fa %= MOD;
        ans[i] = fa;
    }

    cout << fa << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}