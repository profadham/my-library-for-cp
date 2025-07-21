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
