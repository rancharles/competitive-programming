/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-04-08
 * Contest: 
 * Problem: C
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

void solve(){
    int n, m, a, b; cin >> n >> m >> a >> b;

    int d1 = __gcd(b, m);
    int d2 = __gcd(a, n);

    if (d1 != 1 || d2 != 1) {
        cout << "NO" << endl;
        return;
    }

    if (m % 2 == 0 && n % 2 == 0) {
        m /= 2;
        n /= 2;
    }

    if (__gcd(m, n) != 1) {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;
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