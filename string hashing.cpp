#include <bits/stdc++.h>

#define ll long long
#define ld double
#define fr first;
#define sc second;
#define FIO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
//const int N = 1 << 15, G = 4, TT = 226;
//const ll mod = 1e9 + 7;
using namespace std;
const ll inf = 1e12, N = 1e3 + 5, WW = 1000, K = 65, P = 200;
#define eps 1e-8
#define pi acos(-1)
#define rep1(n) for(ll i = 0; i < (ll)(n); i++)
const int BASE = 26;
ll mod1;
ll mod2;

ll rnd(ll l, ll r)
{
	return (rand() % (r - l + 1)) + l;
}
bool prime(ll n)
{
	if (n == 1 || n == 0) return false;
	if (n == 2) return true;
	for (ll i = 2; i * i <= n; i++)
	{
		if (!(n % i)) return false;
	}
	return true;
}

void setMods()
{
	mod1 = rnd(2e8, 2e9);
	mod2 = rnd(2e8, 2e9);
	while (!prime(mod1))
		mod1--;
	while (!prime(mod2))
		mod2--;
}

ll mul(ll a, ll b, ll m) { return a * 1ll * b % m; }
ll add(ll a, ll b, ll m)
{
	return ((a + b) % m + m) % m;
}
ll fp(ll b, ll p, ll m)
{
	ll res = 1;
	while (p)
	{
		if (p & 1) res = mul(res, b, m);
		p >>= 1; b = mul(b, b, m);
	}
	return res;
}
ll inv(ll x, ll m) { return fp(x, m - 2, m); }

struct Hash
{
	ll h = 0, sz = 0;
	vector<pair<ll, ll>> prefix, suffix;
	void			push_back(char c, ll m) //15 => 157
	{
		h = mul(h, BASE, m);
		h = add(h, c-'a', m);
		sz++;
	}
	void			pop_back(char c, ll m) //157 => 15
	{
		h = add(h, -(c-'a'), m);
		h = mul(h, inv(BASE, m), m);
		sz--;
	}
	void			pop_front(char c, ll m) //157 => 57
	{
		ll val = mul(c-'a', fp(BASE, sz - 1, m), m);
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
			h2 = (1ll * h2 * BASE) % mod2;
			h2 = (h2 + i) % mod2;
			prefix.emplace_back(h1, h2);
		}
	}
	void			hash_suffix(const string& str)
	{
		ll h1 = 0, h2 = 0;
		suffix.clear();
		suffix.reserve(str.size());
		for (ll i = str.size()-1; i >= 0; i--)
		{
			h1 = (1ll * h1 * BASE) % mod1;
			h1 = (h1 + str[i]) % mod1;
			h2 = (1ll * h2 * BASE) % mod2;
			h2 = (h2 + str[i]) % mod2;
			suffix.emplace_back(h1, h2);
		}
	}
	pair<ll, ll>	getPrefix(ll l, ll r)
	{
		auto ret = prefix[r];
		ll sz = r - l + 1;
		l--;
		if (l >= 0)
		{
			ret.first -= 1ll * prefix[l].first * fp(BASE, sz, mod1) % mod1;
			if (ret.first < 0) ret.first += mod1;

			ret.second -= 1ll * prefix[l].second * fp(BASE, sz, mod2) % mod2;
			if (ret.second < 0) ret.second += mod2;

		}
		return ret;
	}
	pair<ll, ll>	getSuffix(ll l, ll r)
	{
		auto ret = suffix[r];
		ll sz = r - l + 1;
		l--;
		if (l >= 0)
		{
			ret.first -= 1ll * suffix[l].first * fp(BASE, sz, mod1) % mod1;
			if (ret.first < 0) ret.first += mod1;

			ret.second -= 1ll * suffix[l].second * fp(BASE, sz, mod2) % mod2;
			if (ret.second < 0) ret.second += mod2;

		}
		return ret;
	}
};


void solve(){

}

int main()
{
	FIO;
	setMods();
	//cout << mod1 << " " << mod2 << "\n";
	ll t = 1;
	//cin >> t;
	while (t--)
	{
		solve();
	}
}