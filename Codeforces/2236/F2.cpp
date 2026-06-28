/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-06-28
 * Contest: 
 * Problem: F1
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

const int MAX_N = 1e6 + 1;
const ll MOD = 1e9 + 7;

/**
 * PRECOMPUTE: Prime Linear Sieve
 * PURPOSE: Classifies numbers up to MAX_N as primes or not
 * TIME: O(n)
 */
vector<ll> prime;
vector<bool> is_composite(MAX_N + 1, false);
vector<ll> min_div(MAX_N + 1, 1);
void prime_sieve (ll n) {
	for (ll i = 2; i < n; ++i) {
		if (!is_composite[i]) {
			prime.pb(i);
            min_div[i] = i;
		}
		for (ll j = 0; j < prime.size() && i * prime[j] < n; ++j) {
			is_composite[i * prime[j]] = true;
            min_div[i * prime[j]] = prime[j];
			if (i % prime[j] == 0) {
				break;
			}
		}
	}
}

vector<vi> parr(MAX_N);
vector<bool> iscrit(MAX_N, false);

void solve(){
    int n, x; cin >> n >> x;

    map<int, int> critp;

    while (x != 1) {
        int p = min_div[x];
        iscrit[p] = true;
        
        while (x % p == 0) {
            x /= p;
            critp[p]++;
        }
    }

    ll ans = 1;
    map<int, int> pm;

    rep(i, 0, n) {
        int a; cin >> a;
        while (a != 1) {
            int p = min_div[a];
            int c = 0;
            while (a % p == 0) {
                a /= p;
                c++;
            }

            if (iscrit[p]) {
                parr[p].pb(c);
            }
            else {
                pm[p] += c;
            }
        }
    }

    for (auto [p, c] : pm) {
        ans *= c + 1;
        ans %= MOD;
    }

    bool zero = false;
    for (auto [p, c] : critp) {
        int m = sz(parr[p]);
        if (m == 0) {
            zero = true;
            parr[p] = {};
            iscrit[p] = false;
            continue;
        }

        int a = *max_element(all(parr[p]));
        vector<vl> dp(a + 1, vl(c + a + 1, 0)), ndp(a + 1, vl(c + a + 1, 0));
        rep(cap, 0, a + 1) {
            dp[cap][0] = 1;
        }

        rep(i, 1, m + 1) {
            rep(cap, 0, a + 1) {
                int cp = min(cap, parr[p][i - 1]);
                vl pre(c + a + 2, 0);
                rep(k, 1, c + a + 2) {
                    pre[k] = dp[cap][k - 1] + pre[k - 1];
                    pre[k] %= MOD;
                }

                rep(sum, 0, c + a + 1) {
                    ndp[cap][sum] = (pre[sum + 1] + MOD - pre[max(0, sum - cp)]) % MOD;
                }
            }
            
            dp = ndp;
        }

        ll mult = 0;
        rep(mx, 1, a + 1) {
            mult += (dp[mx][c + mx] + MOD - dp[mx - 1][c + mx]) % MOD;
            mult %= MOD;
        }

        ans *= mult;
        ans %= MOD;

        parr[p] = {};
        iscrit[p] = false;
    }

    if (zero) {
        cout << 0 << endl;
        return;
    }

    cout << ans << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    prime_sieve(MAX_N);

    int tc;
    cin >> tc;
    for (int t = 1; t <= tc; ++t){
        // cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}