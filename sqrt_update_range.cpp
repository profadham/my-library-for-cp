#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ll long long
#define ordered_set tree<ll, null_type,less_equal<ll>, rb_tree_tag,tree_order_statistics_node_update>
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
const int N = 5*1e5 + 5, M = 1e7 + 1;
const ll inf = 1e9;

struct Sqrt {
    ll n, len;
    vector<ll> a,b;
    Sqrt(vector<ll>& a) {
        this->a = a;
        len = (ll)sqrt(a.size() + .0) + 1;
        //every block is from i*len -> (i+1)*len-1
        b.assign(len, 0);
        n = a.size();
    }
    void update(ll l, ll r, ll v) {
        ll c_l = l / len, c_r = r / len;
        if (c_l == c_r) {
            for (ll i = l; i <= r; i++) a[i] += v;
        }
        else {
            for (ll i = l, end = (c_l + 1) * len - 1; i <= end; i++) a[i] += v;
            for (ll i = c_l + 1; i <= c_r - 1; i++) b[i] += v;
            for (ll i = c_r * len; i <= r; i++) a[i] += v;
        }
    }
    ll query(ll i) {
        return a[i] + b[i / len];
    }
};

void solve() {
    ll n;
    ll q;
    cin >> n;
    cin >> q;
    vector<ll> a(n);
    for (auto& i : a) cin >> i;

    Sqrt sq = Sqrt(a);
    //answer queries;

    while (q--) {
        ll ty, l, r, v;
        cin >> ty;
        if (ty == 1) {
            cin >> l >> r >> v;
            l--; r--;
            sq.update(l, r, v);
        }
        else {
            cin >> l; l--;
            cout << sq.query(l) << "\n";
        }
    }
}
