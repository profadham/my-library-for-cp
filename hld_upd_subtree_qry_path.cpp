#include <bits/stdc++.h>
#define ll int
using namespace std;
const ll mod = 998244353;



void solve(){
    ll n,q;
    cin >> n;
    vector<vector<ll>> g(n+1);
    vector<ll>a(n+1);
    for (ll i= 0,u,v; i+1<n; i++){
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    vector<ll> pos(n+1), heavy(n+1,-1), sz(n+1), depth(n+1), top(n+1), par(n+1,-1), out(n+1);
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
        out[u] = time-1;
    };
    dfs(1,0);
    hld(1,1);
//    vector<ll> flat(n);
    vector<ll> seg(n*4), lazy(n*4,0);
    auto push = [&](ll x, ll lx, ll rx){
        if (rx!=lx){
            lazy[2*x+1] += lazy[x];
            lazy[2*x+2] += lazy[x];
        }
        seg[x] += lazy[x];
        lazy[x] = 0;
    };
    function <void(ll,ll,ll,ll,ll,ll)> seg_upd = [&](ll x, ll lx, ll rx, ll lq, ll rq, ll val){
        push(x, lx, rx);
        if (lx >= lq && rx <= rq){
            lazy[x] += val;
            push(x,lx,rx);
            return;
        }
        if (lx > rq || rx < lq) return;
        ll md = (lx+rx)/2;
        seg_upd(x*2+1,lx,md,lq,rq,val);
        seg_upd(x*2+2,md+1,rx,lq,rq,val);
        seg[x] = max(seg[x*2+1],seg[x*2+2]);
    };
    function<ll(ll,ll,ll,ll,ll)> seg_qry = [&](ll x, ll lx, ll rx, ll lq, ll rq){
        push(x,lx,rx);
        if (lx >= lq && rx <= rq) return seg[x];
        if (lx > rq || rx < lq) return (ll)-1e9;
        ll md= (lx+rx)/2;
        return max(seg_qry(x*2+2,md+1,rx,lq,rq),seg_qry(x*2+1,lx,md,lq,rq));
    };

    auto qry = [&](ll u, ll v){
        ll ans = -1e9;
        while (top[u] != top[v]){
            if (depth[top[u]] < depth[top[v]]) swap(u,v);
            ans = max(ans,seg_qry(0,0,n-1,pos[top[u]],pos[u]));
            u = par[top[u]];
        }
        if (depth[v] < depth[u]) swap(u,v);
        ans = max(ans,seg_qry(0,0,n-1,pos[u],pos[v]));
        return ans;
    };
    auto upd = [&](ll u,ll v){
        seg_upd(0,0,n-1,pos[u],out[u],v);
    };
    cin >> q;
    while (q--){
        string ty;
        ll u,v;
        cin >> ty>>u >> v;
        if (ty=="add"){
            upd(u,v);
        }
        else{
            cout <<qry(u,v) << "\n";
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

