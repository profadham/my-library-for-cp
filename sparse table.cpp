
#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define ld double
#define fr first;
#define sc second;
#define FIO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
const ll N = 1e6 + 5, inf = 1e17, M = 25;
const int mod = 1e9 + 7;
#define pii pair<ll, ll>

template<typename T, class CMP = function<T(const T &, const T &)>>
class SparseTable {
public:
    int n;
    vector<vector<T>> sp;
    CMP func;

    SparseTable(const vector<T> &a, const CMP &f) : func(f) {
        n = a.size();
        int max_log = 32 - __builtin_clz(n);
        sp.resize(max_log);
        sp[0] = a;
        for (int j = 1; j < max_log; ++j) {
            sp[j].resize(n - (1 << j) + 1);
            for (int i = 0; i + (1 << j) <= n; ++i) {
                sp[j][i] = func(
                        sp[j - 1][i],
                        sp[j - 1][i + (1 << (j - 1))]
                );
            }
        }
    }

    T query(int l, int r) const {
        int lg = __lg(r - l + 1);
        return func(
                sp[lg][l],
                sp[lg][r - (1 << lg) + 1]
        );
    }
};

void solve()
{
    ll n;
    cin >> n;
    vector<int> v(n);
    for (auto& i : v) cin >> i;
    SparseTable<int, function<int(const int&, const int&)>> dp(v, [](int x, int y){return min(x, y);});
    ll q;
    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        l--; r--;
        cout << dp.query(l, r) << "\n";
    }
}

int main()
{
    FIO;
    ll t = 1;
    //cin>>t;
    for (ll i = 1; i <= t; i++)
    {
        solve();
    }
}