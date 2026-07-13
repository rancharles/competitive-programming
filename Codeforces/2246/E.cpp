/**
 * Solution by Charles Ran (polarity.sh)
 * Date: 2026-07-12
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
string zero, one;

mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());

ll rand(ll l, ll r) {
    return l + rd() % (r - l + 1);
}

int ti(string s) {
    int ans = 0;
    rep(i, 0, sz(s)) {
        if (s[i] == '1') {
            ans += 1 << (sz(s) - i - 1);
        }
    }
    return ans;
}

string ts(int x) {
    string a = "";
    while (x != 0) {
        if (x % 2 == 0) {
            a += "0";
        } else {
            a += "1";
        }

        x /= 2;
    }
    reverse(all(a));

    string b;
    rep(i, 0, 30 - sz(a)) {
        b += "0";
    }
    b += a;
    return b;
}

void solve(){
    string s;
    rep(i, 0, 1) {
        s += "1";
    }
    rep(i, 0, 29) {
        s += "0";
    }
    cout << ti(s) << endl;
    int z; cin >> z;
    string o = ts(z);
    int c = -1;
    rep(i, 0, 30) {
        if (o[i] != s[i]) {
            c = i;
            break;
        }
    }

    if (c != -1) {
        char act = o[c];
        cout << 0 << " " << ti(one) << endl;
        cin >> z;
        string r = ts(z);
        if (o[c] == r[c]) {
            cout << 0 << endl;
        } else {
            cout << 1 << endl;
        }
        return;
    }

    string a = "0", b = "1";
    rep(i, 0, 29) {
        int x = rand(0, 1);
        a += ('0' + x);
        x = rand(0, 1);
        b += ('0' + x);
    }
    cout << ti(a) << " " << ti(b) << endl;
    cin >> z;
    string r = ts(z);
    bool a1 = true, b1 = true;
    rep(i, 1, 30) {
        if (r[i] != a[i]) {
            a1 = false;
        }
        if (r[i] != b[i]) {
            b1 = false;
        }
    }
    if (a1) {
        cout << 0 << endl;
        return;
    }
    if (b1) {
        cout << 1 << endl;
        return;
    }

    if (r[0] == '1') {
        cout << 0 << endl;
    } else {
        cout << 1 << endl;
    }
    // bool a11 = true, a12 = false, a21 = true, a22 = false;
    // rep(i, 0, 15) {
    //     char x = '0' + (a[i] != '1');
    //     if (r[i] != x) {
    //         a11 = false;
    //     }
    //     x = '0' + (b[i] != '1');
    //     if (r[i] != x) {
    //         a22 = true;
    //     }
    // }
    // rep(i, 15, 30) {
    //     char x = a[i];
    //     if (r[i] != x) {
    //         a21 = false;
    //     }
    //     x = b[i];
    //     if (r[i] != x) {
    //         a12 = true;
    //     }
    // }
    // if (a11 && a12) {
    //     cout << 0 << endl;
    //     return;
    // }
    // if (a21 && a22) {
    //     cout << 0 << endl;
    //     return;
    // }
    
    // cout << 1 << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    rep(i, 0, 30) {
        zero += "0";
        one += "1";
    }

    int tc;
    cin >> tc;
    for (int t = 1; t <= tc; ++t){
        // cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}