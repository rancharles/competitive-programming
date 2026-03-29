/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-03-28
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
    int n, k; cin >> n >> k;

    vi arr(n);
    rep(i, 0, n) {
        cin >> arr[i];
        if (arr[i] != -1) arr[i]--;
    }

    vi brr(n);
    rep(i, 0, n) {
        cin >> brr[i];
        if (brr[i] != -1) brr[i]--;
    }

    vi cnt(n, 0);

    rep(i, 0, k) {
        int vala = arr[i];
        for (int j = i; j < n; j += k) {
            if (arr[j] != vala) {
                vala = -1;
                break;
            }
        }

        if (vala == -1) {
            for (int j = i; j < n; j += k) {
                if (brr[j] != -1 && arr[j] != brr[j]) {
                    cout << "NO" << endl;
                    return;
                } 
            }
            continue;
        }
        cnt[vala]++;
        int valb = brr[i];
        for (int j = i; j < n; j += k) {
            if (brr[j] == -1) continue;
            if (brr[j] != valb) {
                if (valb == -1) {
                    valb = brr[j];
                } else {
                    cout << "NO" << endl;
                    return;
                }
            }
        }

        if (valb == -1) continue;
        cnt[valb]--;
    }

    rep(i, 0, n) {
        if (cnt[i] < 0) {
            cout << "NO" << endl;
            return;
        }
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