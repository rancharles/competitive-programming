/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-04-30
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

const int MAX_N = 1e5 + 1;
const ll MOD = 1e9 + 7;

void solve(){
    int n; cin >> n;

    vi arr(2 * n); 
    vector<pii> pos(n, {-1, -1});
    rep(i, 0, 2 * n) {
        int x; cin >> x;
        arr[i] = x;
        if (pos[x].first == -1) {
            pos[x].first = i;
        } else {
            pos[x].second = i;
        }
    }

    int lo = 1, hi = n;
    while (lo < hi) {
        int mid = (lo + hi + 1)/2;
        bool good = true;
        if (mid != 1) {
            int a = -1, b = -1;
            rep(i, 0, mid) {
                int v = pos[i].first + pos[i].second;
                if (a == -1) {
                    a = v;
                } else if (a != v) {
                    if (b == -1) {
                        b = v;
                    } else if (b != v){
                        good = false;
                        break;
                    }
                }
            }

            // cout << mid << " " << a << " " << b << endl;

            if (good) {
                good = false;
                if (a != -1){
                    int l = a/2, r = a/2;
                    if (a % 2 == 1) {
                        r++;
                    }

                    int cnt = 0;
                    while (cnt < mid && l >= 0 && r < 2 * n) {
                        if (arr[l] != arr[r]) {
                            break;
                        }

                        if (arr[l] < mid) {
                            cnt++;
                        }

                        l--;
                        r++;
                    }

                    if (cnt == mid) good = true;
                }
                if (b != -1){
                    int l = b/2, r = b/2;
                    if (b % 2 == 1) {
                        r++;
                    }

                    int cnt = 0;
                    while (cnt < mid && l >= 0 && r < 2 * n) {
                        if (arr[l] != arr[r]) {
                            break;
                        }

                        if (arr[l] < mid) {
                            cnt++;
                        }

                        l--;
                        r++;
                    }

                    if (cnt == mid) good = true;
                }
            }
        }

        if (good) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    cout << lo << endl;
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