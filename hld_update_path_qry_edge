//problem link: https://vjudge.net/problem/SPOJ-GRASSPLA

#include <bits/stdc++.h>
#define ll int
using namespace std;
const ll mod = 998244353;



void solve(){
    ll n,q;
    cin >> n >>q;
    vector<vector<ll>> g(n+1);
    vector<ll>a(n+1);
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
//    vector<ll> flat(n);
    vector<ll> seg(n*4);
    auto push = [&](ll x, ll lx, ll rx){
        if (!seg[x]) return;
        if (rx!=lx){
            seg[2*x+1] += seg[x];
            seg[2*x+2] += seg[x];
            seg[x] = 0;
        }

    };
    function <void(ll,ll,ll,ll,ll,ll)> seg_upd = [&](ll x, ll lx, ll rx, ll lq, ll rq, ll val){
        push(x, lx, rx);
        if (lx >= lq && rx <= rq){
            seg[x] += val;
            push(x, lx, rx);
            return;
        }
        if (lx > rq || rx < lq) return;
        ll md = (lx+rx)/2;
        seg_upd(x*2+1,lx,md,lq,rq,val);
        seg_upd(x*2+2,md+1,rx,lq,rq,val);
    };
    function<ll(ll,ll,ll,ll)> seg_qry = [&](ll x, ll lx, ll rx, ll idx){
        push(x,lx,rx);
        if (lx==rx){
            return seg[x];
        }
        ll md= (lx+rx)/2;
        if (idx<=md) return seg_qry(x*2+1,lx,md,idx);
        else return seg_qry(x*2+2,md+1,rx,idx);
    };

    auto upd = [&](ll u, ll v){
        while (top[u] != top[v]){
            if (depth[top[u]] < depth[top[v]]) swap(u,v);
            seg_upd(0,0,n-1,pos[top[u]],pos[u],1);
            u = par[top[u]];
        }
        if (depth[v] < depth[u]) swap(u,v);
        seg_upd(0,0,n-1,pos[u],pos[v],1);
        seg_upd(0,0,n-1,pos[u],pos[u],-1);
//        seg_upd(0,0,n-1,pos[top[v]],pos[top[v]],-1);
    };
    auto qry = [&](ll u,ll v){
        if (depth[u]<depth[v]) swap(u,v);
        return seg_qry(0,0,n-1,pos[u]);
    };
    while (q--){
        char ty;
        ll u,v;
        cin >> ty>>u >> v;
        if (ty=='P'){
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

