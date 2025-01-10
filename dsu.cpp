struct dsu{
    vector<ll> par, sz;
    ll comps;
    dsu(ll n) : par(n+1), sz(n+1), comps(n)
    {
        for (ll i = 1; i <= n; i++) {par[i] = i; sz[i] = 1;}
    }
    ll find(ll u){
        if (u == par[u]) return u;
        return par[u] = find(par[u]);
    }
    bool merge(ll u, ll v){
        u = find(u);  v = find(v);
        if (u == v) return false;
        if (sz[u] > sz[v]) swap(u, v);
        sz[v] += sz[u];
        par[u] = v;
        comps--;
        return true;
    }
};