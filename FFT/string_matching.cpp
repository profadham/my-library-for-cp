//بسم الله الرحمن الرحيم
#include <bits/stdc++.h>
#define ll long long

#define ordered_set tree<ll, null_type,less_equal<ll>, rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
#include <tr2/dynamic_bitset>
using dynamic_bitset = tr2::dynamic_bitset<>;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ld long double
#define fr first;
#define sc second;
#define pii pair<ll, ll>
#define all(x) x.begin(), x.end()
#define FIO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define is(V) (V < M and is_prime[V])
#define LF (x*2+1)
#define RT (x*2+2)
#define md ((lx+rx) >> 1)
#define vi vector<ll>
#define vv vector<vector<ll>>
#define vvii vector<vector<pii>>
#define vb vector<bool>
#define mem(x) memset(x, -1, sizeof x)
#define db dynamic_bitset
#define print(v) for (auto& i : v) cout << i << " ";
const int N = 4e5+5, M = 2e6 + 5;
const ll inf = 1e18;
const ll mod = 998244353;


const double PI = acos(-1);
struct base {
    double a, b;
    base(double a = 0, double b = 0) : a(a), b(b) {}
    const base operator + (const base &c) const
    { return base(a + c.a, b + c.b); }
    const base operator - (const base &c) const
    { return base(a - c.a, b - c.b); }
    const base operator * (const base &c) const
    { return base(a * c.a - b * c.b, a * c.b + b * c.a); }
};
void fft(vector<base> &p, bool inv = 0) {
    int n = p.size(), i = 0;
    for(int j = 1; j < n - 1; ++j) {
        for(int k = n >> 1; k > (i ^= k); k >>= 1);
        if(j < i) swap(p[i], p[j]);
    }
    for(int l = 1, m; (m = l << 1) <= n; l <<= 1) {
        double ang = 2 * PI / m;
        base wn = base(cos(ang), (inv ? 1. : -1.) * sin(ang)), w;
        for(int i = 0, j, k; i < n; i += m) {
            for(w = base(1, 0), j = i, k = i + l; j < k; ++j, w = w * wn) {
                base t = w * p[j + l];
                p[j + l] = p[j] - t;
                p[j] = p[j] + t;
            }
        }
    }
    if(inv) for(int i = 0; i < n; ++i) p[i].a /= n, p[i].b /= n;
}
vector<ll> multiply(vector<ll> &a, vector<ll> &b) {
    int n = a.size(), m = b.size(), t = n + m - 1, sz = 1;
    while(sz < t) sz <<= 1;
    vector<base> x(sz), y(sz), z(sz);
    for(int i = 0 ; i < sz; ++i) {
        x[i] = i < (int)a.size() ? base(a[i], 0) : base(0, 0);
        y[i] = i < (int)b.size() ? base(b[i], 0) : base(0, 0);
    }
    fft(x), fft(y);
    for(int i = 0; i < sz; ++i) z[i] = x[i] * y[i];
    fft(z, 1);
    vector<ll> ret(sz);
    for(int i = 0; i < sz; ++i) ret[i] = (ll) round(z[i].a);
    while((int)ret.size() > 1 && ret.back() == 0) ret.pop_back();
    return ret;
}

vector<ll> poly_pow(vector<ll> p, ll k){
    vector<ll> ans{1};
    while (k){
        if (k&1) ans = multiply(ans,p);
        p = multiply(p,p);
        k >>= 1;
    }
    return ans;
}

void string_match(string& s, string& patt) {
    int n = (int)s.length(), m = (int)patt.length();

    vector<ll> poly1(n), poly2(m);

    vector<int> ans_match(n);

    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < n; ++j) {
            poly1[j] = (s[j] - 'a') == i;
        }
        for (int j = 0; j < m; ++j) {
            poly2[j] = (patt[m-j-1] - 'a') == i;
        }
        vector<ll> ans = multiply(poly1, poly2);
        for (int j = 0; j < n; ++j) {
            ans_match[j] += ans[m-1+j];
        }
    }
    for (ll i= 0; i < n-m; i++) {
        //cout << i + sh << " " << ans_match.size() << "\n";
        cout << ans_match[i] << " ";
    }
}

void solve() {
    string s, p;
    cin >> s >> p;
    string_match(s,p);
}


int main() {
    ll t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
}
