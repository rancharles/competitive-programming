/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-07-08
 * Contest: 
 * Problem: E
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
    int l, r, n; cin >> l >> r >> n;

    int ll = log2(l);
    int lr = log2(r);
    int a, b;
    if (lr > ll + 1) {
        a = 1 << lr;
        b = 1 << (lr - 1);
    } else if (lr > ll) {
        a = 1 << lr;
        b = l;
    } else {
        int curr = 0;
        for (int i = ll; i >= 0; i--) {
            int bt = 1 << i;
            int ac = r & bt;
            int bc = l & bt;
            if (ac != bc) {
                a = curr + bt;
                b = curr + bt - 1;
                break;
            }

            curr += (bool)(ac) * bt;
        }
    }

    int la = log2(a);
    int lb = log2(b);

    rep(i, 0, n) {
        int pa = la - (i % (la + 1));
        int pb = lb - (i % (lb + 1));
        bool ac = a & (1 << pa);
        bool bc = b & (1 << pb);
        int x = ac & bc;

        char z = '0' + x;
        cout << z;
    }
    cout << '\n';
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