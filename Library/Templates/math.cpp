/**
 * Template by 1egend (polarity.sh)
 * Template: math
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
const ll INF = LLONG_MAX;

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

/**
 * PRECOMPUTE: Phi Linear Sieve
 * PURPOSE: Computes phi(k) up to MAX_N
 * REQUIRE: Prime Linear Sieve
 * TIME: O(n)
 */
vector<ll> phi(MAX_N + 1);
void phi_sieve () {
	phi[1] = 1;
	for (ll i = 2; i < MAX_N + 1; ++i) {
		if (!is_composite[i]) {
			phi[i] = i - 1;
		}
		for (ll j = 0; j < prime.size() && i * prime[j] < MAX_N + 1; ++j) {
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			} else {
				phi[i * prime[j]] = phi[i] * phi[prime[j]];
			}
		}
	}
}

/**
 * PRECOMPUTE: Mobius Linear Sieve
 * PURPOSE: Computes mu(k) up to MAX_N
 * REQUIRE: Prime Linear Sieve
 * TIME: O(n)
 */
vector<ll> mu(MAX_N + 1);
void mobius_sieve () {
	mu[1] = 1;
	for (ll i = 2; i < MAX_N + 1; ++i) {
		if (!is_composite[i]) {
			mu[i] = -1;
		}
		for (ll j = 0; j < prime.size() && i * prime[j] < MAX_N + 1; ++j) {
			if (i % prime[j] == 0) {
				mu[i * prime[j]] = 0;
				break;
			} else {
				mu[i * prime[j]] = -mu[i];
			}
		}
	}
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

/** 
 * DATASTRUCTURE: Floor Interval Array
 * PURPOSE: Keys the ~ 2sqrt(n) values floor(n/i)
 * SPACE: O(sqrt n)
 * TIME: O(1) queries
*/
class FIArray {
    public:
        ll n;
        ll sqrtn;
		ll len;
        vector<ll> arr;
        vector<ll> keys;
    
        FIArray(ll num){
            n = num;
            sqrtn = sqrt(num);
            len = 2 * sqrtn;
            if (n/sqrtn == sqrtn){
                len--;
            }

            arr = vector<ll>(len);
            keys = vector<ll>(len);

            for (ll i = 1; i <= sqrtn; i++){
                keys[i - 1] = i;
            }

            for (ll i = 1; i <= sqrtn; i++){
                keys[len - i] = n/i;
            }
        }

        ll query(ll i){
            if (i <= sqrtn){
                return arr[i - 1];
            }

            return arr[len - n/i];
        }

        void set(ll i, ll x){
            if (i <= sqrtn){
                arr[i - 1] = x;
                return;
            }

            arr[len - n/i] = x;
        }
};

/** 
 * ALGORITHM: Dirichlet Hyperbola Method
 * PURPOSE: Computes prefix sum of (f (*) g)
 * CONSTRAINT: m * m <= LLONG_MAX to prevent overflow
 * TIME: O(sqrt(n)) for O(1) individual prefix sums
*/
template<ll m> class DirichletProduct {
	public:
		ll f(ll n){
			return 1;
		}

		ll g(ll n){
			return 1;
		}

		FIVector sumf(ll n){
			return n;
		}

		FIVector sumg(ll n){
			return n;
		}

		ll hyperbola(long double c){
			ll k = pow((long double)n, c);
			ll l = pow((long double)n, 1 - c);

			FIVector computef = sumf(n);
			FIVector computeg = sumg(n);

			// cout << k << " " << l << endl;

			ll ans = 0;

			for (ll i = 1; i <= k; i++){
				ll c = f(i);
				c *= computeg.query(n/i);
				// c *= sumg(n/i);
				c %= m;

				ans += c;
				ans %= m;
			}

			for (ll i = 1; i <= l; i++){
				ll c = g(i);
				c *= computef.query(n/i);
				// c *= sumf(n/i);
				c %= m;

				ans += c;
				ans %= m;
			}

			ans += m - ((computef.query(k) * computeg.query(l)) % m);
			// ans += m - ((sumf(k) * sumg(l)) % m);

			return ans % m;
		}
};

/** ALGORITHM: Fast Fourier Transform
 *  SOURCE: KACTL
*/
using C = complex<double>;
using vd = vector<double>;
void fft(vector<C>& a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}

/** 
 * ALGORITHM: FFT Convolution
 * PURPOSE: Computes coefficients of polynomial ab
 * TIME: O(n log n) where n = deg a + deg b
 * REQUIRE: Fast Fourier Transform
 * SOURCE: KACTL
*/
vd conv(const vd& a, const vd& b) {
	if (a.empty() || b.empty()) return {};
	vd res(sz(a) + sz(b) - 1);
	int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
	vector<C> in(n), out(n);
	copy(all(a), begin(in));
	rep(i,0,sz(b)) in[i].imag(b[i]);
	fft(in);
	for (C& x : in) x *= x;
	rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	rep(i,0,sz(res)) res[i] = imag(out[i]) / (4 * n);
	return res;
}

/** 
 * ALGORITHM: FFT Convolution with Modulus
 * PURPOSE: Computes coefficients of polynomial ab, modulo m
 * TIME: O(n log n) where n = deg a + deg b
 * REQUIRE: Fast Fourier Transform
 * SOURCE: KACTL
*/
template<int M> vl convMod(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	vl res(sz(a) + sz(b) - 1);
	int B=32-__builtin_clz(sz(res)), n=1<<B, cut=int(sqrt(M));
	vector<C> L(n), R(n), outs(n), outl(n);
	rep(i,0,sz(a)) L[i] = C((int)a[i] / cut, (int)a[i] % cut);
	rep(i,0,sz(b)) R[i] = C((int)b[i] / cut, (int)b[i] % cut);
	fft(L), fft(R);
	rep(i,0,n) {
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
	}
	fft(outl), fft(outs);
	rep(i,0,sz(res)) {
		ll av = ll(real(outl[i])+.5), cv = ll(imag(outs[i])+.5);
		ll bv = ll(imag(outl[i])+.5) + ll(real(outs[i])+.5);
		res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
	}
	return res;
}

/** 
 * ALGORITHM: Deterministic Miller-Rabin Primality Test
 * PURPOSE: Deterministic Primality Test
 * TIME: O (|A| log n)
 * SOURCE: KACTL
*/
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

/** 
 * DATASTRUCTURE: Matrix
 * PURPOSE: Common matrix template
 * TIME: O(nmp) for n x m times m x p matrix; supports binary exponentiation
 * SOURCE: USACO Guide
*/
template <typename T> void matmul(vector<vector<T>> &a, vector<vector<T>> b) {
	int n = a.size(), m = a[0].size(), p = b[0].size();
	assert(m == b.size());
	vector<vector<T>> c(n, vector<T>(p));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < p; j++) {
			for (int k = 0; k < m; k++) {
				c[i][j] = (c[i][j] + a[i][k] * b[k][j]);
			}
		}
	}

	a = c;
}

template <typename T> struct Matrix {
	vector<vector<T>> mat;
	Matrix() {}
	Matrix(vector<vector<T>> a) { mat = a; }
	Matrix(int n, int m) {
		mat.resize(n);
		for (int i = 0; i < n; i++) { mat[i].resize(m); }
	}

	int rows() const { return mat.size(); }
	int cols() const { return mat[0].size(); }

	// makes the identity matrix for a n by n matrix
	void makeiden() {
		for (int i = 0; i < rows(); i++) { mat[i][i] = 1; }
	}

	void print() const {
		for (int i = 0; i < rows(); i++) {
			for (int j = 0; j < cols(); j++) { cout << mat[i][j] << ' '; }
			cout << '\n';
		}
	}

	Matrix operator*=(const Matrix &b) {
		matmul(mat, b.mat);
		return *this;
	}

	Matrix operator*(const Matrix &b) { return Matrix(*this) *= b; }

    Matrix operator^=(ll p) {
        assert(p >= 0);


        Matrix a(rows(), cols()), b(*this);
        a.makeiden();

        while (p){
            if (p&1) a *= b;
            b *= b;
            p >>= 1;
        }

        mat = a.mat;

		return *this;
	}

	Matrix operator^(ll p) { return Matrix(*this) ^= p; }
};

/** 
 * DATASTRUCTURE: Generic Matrix
 * PURPOSE: Generic matrix template over a semiring
 * TIME: O(nmp) for n x m times m x p matrix; supports binary exponentiation
 * CONSTRAINT: Needs a semiring T
 *   - static T zero();  // additive identity
 *   - static T one();   // multiplicative identity
 *   - T operator+(const T&, const T&);
 *   - T operator*(const T&, const T&);
 *   - ostream& operator<<(ostream& os, const ModInt& x); // for print
*/
#include <bits/stdc++.h>
using namespace std;

template<typename U>
struct SRNum {
    U v;
    SRNum(U x = U{}) : v(x) {}

    // identities for + and *
    static SRNum zero() { return SRNum(U{}); } // 0
    static SRNum one()  { return SRNum(U{1}); } // 1

    // compound ops
    SRNum& operator+=(const SRNum& o) { v += o.v; return *this; }
    SRNum& operator*=(const SRNum& o) { v *= o.v; return *this; }

    // binary ops (defined via compound)
    friend SRNum operator+(SRNum a, const SRNum& b) { a += b; return a; }
    friend SRNum operator*(SRNum a, const SRNum& b) { a *= b; return a; }

    // optional for field
    SRNum& operator-=(const SRNum& o) { v -= o.v; return *this; }
    SRNum& operator/=(const SRNum& o) { v /= o.v; return *this; }
    friend SRNum operator-(SRNum a, const SRNum& b) { a -= b; return a; }
    friend SRNum operator/(SRNum a, const SRNum& b) { a /= b; return a; }

    // optional
    friend bool operator==(const SRNum& a, const SRNum& b) { return a.v == b.v; }
    friend bool operator!=(const SRNum& a, const SRNum& b) { return !(a == b); }

    friend ostream& operator<<(ostream& os, const SRNum& x) { return os << x.v; }
};

// Shorthands
using SRLL = SRNum<long long>;
using SRD  = SRNum<double>;

template <typename T>
void matmul(vector<vector<T>> &a, const vector<vector<T>> &b) {
    int n = (int)a.size(), m = (int)a[0].size(), p = (int)b[0].size();
    assert(m == (int)b.size());
    vector<vector<T>> c(n, vector<T>(p, T::zero()));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < m; k++) {
            // Optional micro-opt: skip if a[i][k] == T::zero() (requires ==)
            for (int j = 0; j < p; j++) {
                c[i][j] = c[i][j] + (a[i][k] * b[k][j]);
            }
        }
    }
    a = move(c);
}

template <typename T>
struct Matrix {
    vector<vector<T>> mat;

    Matrix() {}
    Matrix(vector<vector<T>> a) : mat(move(a)) {}
    Matrix(int n, int m, const T &fill = T::zero()) : mat(n, vector<T>(m, fill)) {}

    int rows() const { return (int)mat.size(); }
    int cols() const { return (int)mat[0].size(); }

    void makeiden() {
        assert(rows() == cols());
        int n = rows();
        for (int i = 0; i < n; i++) fill(mat[i].begin(), mat[i].end(), T::zero());
        for (int i = 0; i < n; i++) mat[i][i] = T::one();
    }

    void print() const {
        for (int i = 0; i < rows(); i++) {
            for (int j = 0; j < cols(); j++) cout << mat[i][j] << ' ';
            cout << '\n';
        }
    }

    Matrix operator*=(const Matrix &b) {
        matmul(mat, b.mat);
        return *this;
    }
    Matrix operator*(const Matrix &b) const { return Matrix(*this) *= b; }

    Matrix operator^=(long long p) {
        assert(p >= 0);
        assert(rows() == cols());
        Matrix a(rows(), cols()); a.makeiden();
        Matrix b(*this);
        while (p) {
            if (p & 1) a *= b;
            b *= b;
            p >>= 1;
        }
        mat = move(a.mat);
        return *this;
    }
    Matrix operator^(long long p) const { return Matrix(*this) ^= p; }
};

/** 
 * DATASTRUCTURE: Fast Matrix
 * PURPOSE: Optimized matrix template
 * TIME: O(nmp) for n x m times m x p matrix; supports binary exponentiation
 * SOURCE: KACTL
*/
template<class T, int N> struct Matrix {
	typedef Matrix M;
	array<array<T, N>, N> d{};
	M operator*(const M& m) const {
		M a;
		rep(i,0,N) rep(j,0,N)
			rep(k,0,N) a.d[i][j] += d[i][k]*m.d[k][j];
		return a;
	}
	array<T, N> operator*(const array<T, N>& vec) const {
		array<T, N> ret{};
		rep(i,0,N) rep(j,0,N) ret[i] += d[i][j] * vec[j];
		return ret;
	}
	M operator^(ll p) const {
		assert(p >= 0);
		M a, b(*this);
		rep(i,0,N) a.d[i][i] = 1;
		while (p) {
			if (p&1) a = a*b;
			b = b*b;
			p >>= 1;
		}
		return a;
	}
};

/**
 * ALGORITHM: Gaussian Elimination with Prime Modulo
 * PURPOSE: Solves linear system for arbitrary solution. Returns rank or -1 if no solution.
 * TIME: O(n^3)
 * SOURCE: KACTL
*/
ll modpow(ll a, ll e) {
    ll r = 1;
    while (e > 0) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}
ll inv(ll a) {
    a %= MOD;
    if (a < 0) a += MOD;
    return modpow(a, MOD - 2);
}
int solveLinear(vector<vl>& A, vl& b, vl& x) {
    int n = sz(A), m = sz(x), rank = 0;
    if (n) assert(sz(A[0]) == m);

    vi col(m);
    iota(all(col), 0);

    rep(i, 0, n) {
        int br = -1, bc = -1;

        for (int r = i; r < n && br == -1; r++) {
            for (int c = i; c < m; c++) {
                ll v = A[r][c] % MOD;
                if (v < 0) v += MOD;
                if (v != 0) {
                    br = r;
                    bc = c;
                    break;
                }
            }
        }

        if (br == -1) {
            rep(j, i, n) {
                ll bj = b[j] % MOD;
                if (bj < 0) bj += MOD;
                if (bj != 0) return -1;
            }
            break;
        }

        swap(A[i], A[br]);
        swap(b[i], b[br]);
        swap(col[i], col[bc]);
        rep(j, 0, n) swap(A[j][i], A[j][bc]);

        ll invPivot = inv(A[i][i]);

        rep(j, i + 1, n) {
            ll fac = A[j][i] % MOD;
            if (fac < 0) fac += MOD;
            fac = fac * invPivot % MOD;

            b[j] = (b[j] - fac * b[i]) % MOD;
            if (b[j] < 0) b[j] += MOD;

            rep(k, i + 1, m) {
                A[j][k] = (A[j][k] - fac * A[i][k]) % MOD;
                if (A[j][k] < 0) A[j][k] += MOD;
            }

            A[j][i] = 0;
        }

        rank++;
        if (rank == m) break;
    }

    x.assign(m, 0);

    for (int i = rank - 1; i >= 0; i--) {
        ll rhs = b[i] % MOD;
        if (rhs < 0) rhs += MOD;

        rep(j, i + 1, rank) {
            rhs = (rhs - A[i][j] * b[j]) % MOD;
            if (rhs < 0) rhs += MOD;
        }

        b[i] = rhs * inv(A[i][i]) % MOD;
        x[col[i]] = b[i];
    }

    return rank;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    return 0;
}