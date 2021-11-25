// dynamic programming with precalculation optimization example
// https://oj.uz/problem/view/IOI17_wiring
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define st first
#define nd second
using ll = long long;
const ll inf = 1e18 + 1;
const int mod = 1e9 + 7;
const int N = 2e5 + 5;

pair < ll , int > T[N];
ll L[N], R[N], dp[N], p[N];
ll bld(ll l, ll r, ll x, ll y){
    ll sz = 1;
    ll p = 0;
    for(int i = r; i >= l; i--, sz++){
        p += T[i].st;
        L[sz] = min(dp[i], dp[i - 1]) - p + sz * x;
        R[sz] = min(dp[i], dp[i - 1]) - p + sz * y;
    }
    return sz - 1;
}

ll min_total_length(vector < int > a, vector < int > b){
    int n = a.size();
    int m = b.size();
    int t = 0;
    for(int i = 0, j = 0; i < n || j < m ;){
        if(j == m || (i < n && a[i] < b[j])) T[++t] = mp(a[i++], 1);
        else T[++t] = mp(b[j++], 2);
    }

    memset(L, 22, sizeof L);
    memset(R, 22, sizeof R);
    int l = 1;
    int r = 1;
    for(; T[r].nd == T[r + 1].nd; r++)
        dp[r] = inf;
    dp[r] = inf;
    for(int i = r + 1; i <= t; i = r + 1){
        int j = i;
        while(T[j].nd == T[j + 1].nd)
            j++;
        int x = T[i].st;
        int y = T[i - 1].st;
        ll psz = bld(l, r, x, y);

        ll mn = inf;
        ll sz = 1;
        for(int k = i; k <= j; k++, sz++){
            p[sz] = p[sz - 1] + T[k].st;
            mn = min(mn, R[sz]);
            dp[k] = mn + p[sz] - sz * y;
        }
        mn = inf;
        sz = j - i + 1;
        for(; psz > sz; psz--)
            mn = min(mn, L[psz]);
        for(int k = j; k >= i; k--, sz--){
            mn = min(mn, L[sz]);
            dp[k] = min(dp[k], mn + p[sz] - sz * x);
        }

        for(int k = 1; k <= r - l + 1; k++)
            L[k] = R[k] = inf;
        l = i;
        r = j;
    }

    return dp[t];
}