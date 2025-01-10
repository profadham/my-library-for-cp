#include <bits/stdc++.h>
using namespace std;
#define ll long long
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
const int N = 2 * 1e5 + 5, M = 1e7 + 1;
const ll inf = 1e18;

struct Sqrt {
    ll n, len;
    vector<ll> a,b;
    Sqrt(vector<ll>& a) {
        this->a = a;
        len = (ll)sqrt(a.size() + .0) + 1;
        //every block is from i*len -> (i+1)*len-1
        b.assign(len, 0);
        n = a.size();
        for (ll i = 0; i < n; i++) {
            b[i / len] += a[i];
        }
    }
    void update(ll i, ll v) {
        b[i / len] -= a[i];
        a[i] = v;
        b[i / len] += a[i];
    }
    ll query(ll l, ll r) {
        ll sum = 0;
        ll c_l = l / len, c_r = r / len;
        if (c_l == c_r) {
            for (ll i = l; i <= r; i++) sum += a[i];
        }
        else {
            for (ll i = l, end = (c_l + 1) * len - 1; i <= end; i++) sum += a[i];
            for (ll i = c_l + 1; i <= c_r - 1; i++) sum += b[i];
            for (ll i = c_r * len; i <= r; i++) sum += a[i];
        }
        return sum;
    }
};