#include <bits/stdc++.h>
 
using namespace std;
#define ll int
#define ld double
#define fr first;
#define sc second;
#define FIO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
const ll N = 2e6+5;
const int BASE = 26;
ll mod1;
ll mod2;
ll pw1[N], pw2[N];
 
ll		rnd(ll l, ll r)
{
    return (rand() % (r - l + 1)) + l;
}
bool	prime(ll n)
{
    if (n == 1 || n == 0) return false;
    if (n == 2) return true;
    for (ll i = 2; i * i <= n; i++)
    {
        if (!(n % i)) return false;
    }
    return true;
}
void	setMods()
{
    mod1 = rnd(2e8, 2e9);
    mod2 = rnd(2e8, 2e9);
    while (!prime(mod1))
        mod1--;
    while (!prime(mod2))
        mod2--;
}
ll		mul(ll a, ll b, ll m) { return a * 1ll * b % m; }
ll		add(ll a, ll b, ll m)
{
    return ((a + b) % m + m) % m;
}
ll		fp(ll b, ll p, ll m)
{
    ll res = 1;
    while (p)
    {
        if (p & 1) res = mul(res, b, m);
        p >>= 1; b = mul(b, b, m);
    }
    return res;
}
ll		inv(ll x, ll m)
{
    return fp(x, m - 2, m);
}
void	pre()
{
    pw1[0] = 1; pw2[0] = 1;
    for (ll i = 1; i < N; i++)
    {
        pw1[i] = 1ll * pw1[i - 1] * BASE % mod1;
        pw2[i] = 1ll * pw2[i - 1] * BASE % mod2;
    }
}
 
struct Hash
{
    ll h = 0, sz = 0;
    vector<ll> prefix, suffix;
    void			push_back(char c, ll m) //15 => 157
    {
        h = mul(h, BASE, m);
        h = add(h, c - 'a', m);
        sz++;
    }
    void			pop_back(char c, ll m) //157 => 15
    {
        h = add(h, -(c - 'a'), m);
        h = mul(h, inv(BASE, m), m);
        sz--;
    }
    void			pop_front(char c, ll m) //157 => 57
    {
        //ll val = mul(c - 'a', (m==mod1)?pw1[sz-1]:pw2[sz-2], m);
        ll val = mul(c - 'a', (m == mod1) ? pw1[sz - 1] : pw2[sz - 1], m);
        h = add(h, -val, m);
        sz--;
    }
    void			hash_prefix(const string& str)
    {
        ll h1 = 0, h2 = 0;
        prefix.clear();
        prefix.reserve(str.size());
        for (auto& i : str)
        {
            h1 = (1ll * h1 * BASE) % mod1;
            h1 = (h1 + i) % mod1;
            prefix.emplace_back(h1);
        }
    }
    void			hash_suffix(const string& str)
    {
        ll h1 = 0, h2 = 0;
        suffix.clear();
        suffix.reserve(str.size());
        for (ll i = str.size() - 1; i >= 0; i--)
        {
            h1 = (1ll * h1 * BASE) % mod1;
            h1 = (h1 + str[i]) % mod1;
            suffix.emplace_back(h1);
        }
    }
    ll	getPrefix(ll l, ll r)
    {
        auto ret = prefix[r];
        ll sz = r - l + 1;
        l--;
        if (l >= 0)
        {
            ret -= 1ll * prefix[l] * pw1[sz] % mod1;
            if (ret < 0) ret += mod1;
 
 
        }
        return ret;
    }
    ll	getSuffix(ll l, ll r)
    {
        auto ret = suffix[r];
        ll sz = r - l + 1;
        l--;
        if (l >= 0)
        {
            ret -= 1ll * suffix[l] * pw1[sz] % mod1;
            if (ret < 0) ret += mod1;
 
        }
        return ret;
    }
};
struct dhash{
    Hash h1, h2;
    void pb(char c){
        h1.push_back(c,mod1);
        h2.push_back(c,mod2);
    }
    void pop_front(char c){
        h1.pop_front(c,mod1);
        h2.pop_front(c,mod2);
    }
    void pop_back(char c){
        h1.pop_back(c,mod1);
        h2.pop_back(c,mod2);
    }
    bool cmp(dhash& H){
        return (h1.h==H.h1.h) && (h2.h==H.h2.h);
    }
};
 
void solve(){
	
}
 
int main()
{
    FIO;
    setMods();
    pre();
    //cout << mod1 << " " << mod2 << "\n";
    ll t = 1;
    //cin >> t;
    for (ll i = 1; i <= t; i++){
        solve();
        if (i < t) cout << "\n";
    }
}
