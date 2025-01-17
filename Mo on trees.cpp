//problem solved: https://vjudge.net/problem/SPOJ-COT2


#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
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
const int N = 4e4 + 5, M = 1e7 + 1;
const ll inf = 1e18;
const ll mod = 998244353;
struct chash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t R = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + R);
    }
};

ll mul(ll a, ll b) {return (a*b)%mod;}
ll add(ll a,ll b) {return (a+b)%mod;}

ll n, m;
vector<ll> w;
vector<vector<ll>> g;
ll T;
vector<ll> tin, tout;
void dfs(ll u, ll p){
    //cout << u << "\n";
    tin[u]=T++;
    for (auto& v:g[u]){
        if (v==p)continue;
        dfs(v, u);
    }
    tout[u]=T++;
}


vector<vector<ll>> up;
vector<ll> depth;
ll L;
void dfs1(ll u)
{
    for (auto& v: g[u])
    {
        if (v == up[0][u]) continue;
        up[0][v] = u;
        depth[v] = depth[u]+1;
        dfs1(v);
    }
}

void pre()
{
    dfs1(1);
    for (ll msk = 1; msk < L; msk++)
    {
        for (ll u = 1; u <= n; u++)
        {
            if(~up[msk-1][u])
            {
                ll p = up[msk-1][u];
                up[msk][u] = up[msk-1][p];
                //dp[msk][u] = max(dp[msk-1][u], dp[msk-1][p]);
            }
        }
    }
}
ll lca(ll u, ll v)
{
    if (depth[u] < depth[v]) swap(u, v);
    ll k = depth[u]-depth[v];
    for (ll i = 0;k; ++i, k>>=1)
    {
        if(k&1) u= up[i][u];
    }
    if (u == v) return u;
    for (ll i = L-1;~i;i--)
    {
        if (up[i][u] != up[i][v])
        {
            u = up[i][u];
            v = up[i][v];
        }
    }
    return up[0][u];
}



ll len;
struct Query {
    int l, r, p, idx;
    bool operator<(Query other) const
    {
        return make_pair(l / len, r) <
               make_pair(other.l / len, other.r);
    }
};

void solve(){
    cin >> n >> m;
    w.assign(n+1, 0);
    tin.assign(n+1, 0);
    tout.assign(n+1, 0);
    g.assign(n+1, {});
    L = __lg(n)+1;
    up.assign(32, vector<ll>(n+1, -1));
    depth.assign(n+1, 0);
    len = (ll)sqrt(n+.0)+1;

    for (ll i = 1; i <= n; i++) cin >> w[i];

    //compress:
    ll id = 0;
    vector<ll> b = w;
    sort(all(b));
    auto it = unique(all(b));
    b.erase(it, b.end());
    map<ll, ll> mp;
    for (auto& i : b) mp[i]=id++;
    for (ll i = 0; i <= n; i++) w[i]=mp[w[i]];

    for (ll i = 0,u, v; i < n-1; i++){
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs(1, -1);
    pre();
    vector<ll> a(T);
    for (ll i = 1; i <= n; i++){
        a[tin[i]] = i;
        a[tout[i]] = i;
    }
   // for (auto& i : a) cout << i << " ";
   // cout << "\n";
    vector<Query> q(m);
    for (ll i=  0; i < m;i++){
        ll u,v;
        cin >> u >> v;
        if (tin[u]>tin[v]) swap(u, v);
        ll p =lca(u, v);
        //cout << p << "\n";
        if (p==u){
            q[i].l = tin[u],q[i].r=tin[v],q[i].p=-1;
        }
        else{
            //cout << p << "\n";
            q[i].l=tout[u],q[i].r=tin[v],q[i].p=p;
        }
        q[i].idx=i;
    }
    sort(all(q));
    ll res = 0;
    ll freq[N];
    ll node[N];
    memset(freq, 0, sizeof freq);
    memset(node, 0, sizeof node);
    auto add = [&](ll x){
        if (!freq[w[x]]++) res++;
    };
    auto remove = [&](ll x){
        if (!--freq[w[x]]) res--;
    };
    auto ins = [&](ll u){
        node[u]++;
        if (node[u]&1) add(u);
        else remove(u);
    };
    auto del = [&](ll u){
        node[u]--;
        if (node[u]&1) add(u);
        else remove(u);
    };
    ll curl = 0, curr = -1;
    vector<ll> ans(m);
    for (Query qq : q) {
        //cout << qq.l << " " << qq.r << "\n";
        while (curl > qq.l) {
            curl--;
            ins(a[curl]);
        }
        while (curr < qq.r) {
            curr++;
            ins(a[curr]);
        }
        while (curl < qq.l) {
            del(a[curl]);
            curl++;
        }
        while (curr > qq.r) {
            del(a[curr]);
            curr--;
        }
        //cout << ans << "\n";
        //cout << ":::::::::::\n";
        ll curans = res;
        //cout << curans << "\n";
        if (qq.p!=-1){
            if (!freq[w[qq.p]]) curans++;
           // cout << freq[w[qq.p]] << "-\n";
        }
        //cout << curans << "\n";
        ans[qq.idx] = curans;
    }
    for (auto& i : ans) cout << i << "\n";
}
int main()
{
    //freopen("filename.in", "r", stdin);
    //freopen("filename.out", "w", stdout);
    //FIO;

    ll tt = 1;
    //cin >> tt;
    for (ll i = 1; i <= tt; i++)
    {
        solve();
        //if(i < tt) cout << "\n";
    }
}