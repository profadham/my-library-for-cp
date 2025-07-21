//hld template:

#include <bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;
const ll mod = 998244353;

template <class T> struct fenwick {
    int n;
    vector<T> a, bit;

    fenwick() {}

    fenwick(int _n) : n(_n + 1), a(n + 1), bit(n + 1) {}

    void add(int i, T x) {
        a[i] += x;
        for (++i; i <= n; i += i & -i) bit[i] += x ;
    }

    void add(int l, int r, T x){
        add(l , x);
        add(r+1 , -x);
    }

    void set(int i, T val) {
        add(i, val - a[i]);
    }

    T query(int i) {
        T sum = 0;
        for (++i; i >= 1; i -= i & -i) sum += bit[i] ;
        return sum;
    }
};

void solve(){
    ll n, q;
    cin >> n >>q;
    vector<vector<ll>> g(n+1);
    vector<ll>a(n+1);
    for (ll i =1; i <= n; i++) cin >> a[i];
    for (ll i= 0,u,v; i+1<n; i++){
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    vector<ll> pos(n+1), heavy(n+1,-1), sz(n+1), depth(n+1), top(n+1), par(n+1,-1);
    ll time = 0;
    function <void(ll,ll)> dfs = [&](ll u, ll p){
        sz[u] = 1;
        ll mxsz = 0, hc = -1;
        for (auto& v : g[u]){
            if (v==p) continue;
            depth[v] = depth[u]+1;
            par[v] = u;
            dfs(v,u);
            sz[u] += sz[v];
            if (sz[v]>mxsz){
                mxsz = sz[v];
                hc = v;
            }
        }
        heavy[u] = hc;
    };
    function <void(ll,ll)> hld = [&](ll u, ll t){
        top[u] = t, pos[u] = time++;
        if (~heavy[u]) hld(heavy[u],t);
        for (auto& v : g[u]){
            if (v == par[u] || v == heavy[u]) continue;
            hld(v,v);
        }
    };
    dfs(1,0);
    hld(1,1);
    fenwick<ll> flat(n);
    for (ll i = 1; i <= n; i++)flat.set(pos[i],a[i]);
    auto query = [&](ll u, ll v){
        ll res = 0;
        while (top[u] != top[v]){
            if (depth[top[u]] < depth[top[v]]) swap(u,v);
            res += flat.query(pos[u]);
            if (pos[top[u]]) res -= flat.query(pos[top[u]]-1);
            u = par[top[u]];
        }
        if (depth[v] < depth[u]) swap(u,v);
        res += flat.query(pos[v]);
        if (pos[top[v]]) res -= flat.query(pos[top[v]]-1);
        return res;
    };
    auto upd = [&](ll u,ll x){
        flat.set(pos[u],x);
    };
    while (q--){
        ll ty, s, x;
        cin >> ty >> s;
        if (ty==1){
            cin >> x;
            upd(s,x);
        }
        else{
            cout << query(1,s) << "\n";
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    //cin >> t ;
    while (t--) {
        solve();
    }
}

