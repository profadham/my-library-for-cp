#include <bits/stdc++.h>
#define ll int
using namespace std;
const ll mod = 998244353;

const int N = 2e5+5;  // maximum array size
int n;                  // actual array size
int t[2 * N];

void build() {
    // build internal nodes: each parent is max of its two children
    for (int i = n - 1; i > 0; --i)
        t[i] = max(t[i<<1], t[i<<1|1]);
}

void modify(int p, int value) {
    // set value at position p
    for (t[p += n] = value; p > 1; p >>= 1)
        t[p>>1] = max(t[p], t[p^1]);
}

int qry(int l, int r) {
    // maximum on interval [l, r)
    int res = INT_MIN;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = max(res, t[l++]);
        if (r & 1) res = max(res, t[--r]);
    }
    return res;
}
void solve(){
    ll q;
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
    for (ll i =1; i <= n;  i++) t[n+pos[i]] = a[i];
    build();
    auto query = [&](ll u, ll v){
        ll res = 0;
        while (top[u] != top[v]){
            if (depth[top[u]] < depth[top[v]]) swap(u,v);
            res = max(res,qry(pos[top[u]],pos[u]+1));
            u = par[top[u]];
        }
        if (depth[v] < depth[u]) swap(u,v);
        res = max(qry(pos[u],pos[v]+1),res);
        return res;
    };
    auto upd = [&](ll u,ll x){
        modify(pos[u],x);
    };
    while (q--){
        ll ty, s, x;
        cin >> ty >> s>>x;
        if (ty==1){
            upd(s,x);
        }
        else{
            cout << query(s,x) << " ";
        }
    }
    cout << "\n";
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

