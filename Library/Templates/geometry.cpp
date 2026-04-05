/**
 * Template by 1egend (polarity.sh)
 * Template: geometry
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
 * DATASTRUCTURE: Point (2D)
 * PURPOSE: Represents a point on the euclidian plane
*/
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
    friend istream& operator>>(istream& in, P& p) {
        return in >> p.x >> p.y;
    }
	friend ostream& operator<<(ostream& os, P p) {
		return os << p.x << " " << p.y; }
};

/** 
 * ALGORITHM: Collinearity
 * PURPOSE: Checks if p lies on the line between p1 and p2.
 * If 0 it does. If 1 it is on the right (from p1 to p2), if -1 on the left.
 * CONSTRAINT: p1 != p2
 * REQUIRE: Point
*/
template<class T>
T collinear(Point<T> p1, Point<T> p2, Point<T> p) {
    p2 -= p1;
    p -= p1;

    T tmp = p2.x;
    p2.x = p2.y;
    p2.y = -tmp;

    ll a = p2.x * p.x;
    ll b = p2.y * p.y;

    if (a == -b) {
        return 0;
    }

    return a > -b ? 1 : -1;
}

/** 
 * ALGORITHM: Line Segment Intersection
 * PURPOSE: Check if segment p1, p2 intersects with p3, p4
 * CONSTRAINT: p1 != p2, p3 != p4
 * REQUIRE: Collinear
*/
bool segmentIntersect(Point<ll> p1, Point<ll> p2, Point<ll> p3, Point<ll> p4) {
    ll a = collinear(p1, p2, p3);
    ll b = collinear(p1, p2, p4);
    ll c = collinear(p3, p4, p1);
    ll d = collinear(p3, p4, p2);

    if (a == 0 && b == 0 && c == 0 && d == 0) {
        if (max(p1.x, p2.x) >= min(p3.x, p4.x) && max(p3.x, p4.x) >= min(p1.x, p2.x) && max(p1.y, p2.y) >= min(p3.y, p4.y) && max(p3.y, p4.y) >= min(p1.y, p2.y)) {
            return true;
        }
        else {
            return false;
        }
    }

    if (a * b <= 0 && c * d <= 0) {
        return true;
    }

    return false;
}

/** 
 * ALGORITHM: Polygon area
 * PURPOSE: Uses shoelace theorem to calculate TWICE the polygon area. Remove abs for signed area.
 * CONSTRAINT: Point locations <= 1e9 to avoid overflow
 * REQUIRE: Point
*/
ll polygonArea(const vector<Point<ll>> &points) {
    int n = sz(points);
    ll ans = 0;
    rep(i, 0, n) {
        int pv = (i + n - 1) % n;
        int nx = (i + 1) % n;
        ans += (points[nx].y - points[pv].y) * points[i].x;
    }

    return abs(ans);
}

/** 
 * ALGORITHM: Convex Hull
 * PURPOSE: Returns the convex hull of a set of points in counter-clockwise order. Points on the edges are not considered on the hull.
 * TIME: O(n log n)
 * REQUIRE: Point
*/
typedef Point<ll> P;
vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<P> h(sz(pts)+1); // 2 * sz(pts) + 1 if you want to keep edge points
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		for (P p : pts) {
            // < 0 if want to keep edge points
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    return 0;
}