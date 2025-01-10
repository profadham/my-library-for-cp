vector<ll> fail(string s) //o(2n)->o(n)
{
    const int n = s.size();
    vector<ll> F(n);
    F[0] = 0;
    for (ll i = 1, l = 0; i < n; i++)
    {
        while (l > 0 && s[i] != s[l])
            l = F[l - 1];
        if (s[i] == s[l])l++;
        F[i] = l;
    }
    return F;
}

vector<vector<ll>> aut;
void atometa(string s)
{
    ll n = s.size();
    vector<ll> pi = fail(s);
    aut.assign(n, vector<ll>(26));
    for (ll i = 0; i < n; i++)
    {
        for (ll c = 0; c < 26; c++)
        {
            if (i > 0 && 'a' + c != s[i])
                aut[i][c] = aut[pi[i - 1]][c];
            else aut[i][c] = i + ('a' + c == s[i]);

        }
    }
}