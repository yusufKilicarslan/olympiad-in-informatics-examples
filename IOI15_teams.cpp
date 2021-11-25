// persistent segment tree example
// https://oj.uz/problem/view/IOI15_teams
#include<bits/stdc++.h>
#include "teams.h"
using namespace std;
#define mp make_pair
#define st first
#define nd second
#define N 500005
#define tm (tl+tr >> 1)

int s[N * 20], L[N * 20], R[N * 20], root[N], nw, n;

int update(int v, int tl, int tr, int i){
    if(tl > i || tr < i) return v;
    int w = ++nw;
    if(tl < tr){
        L[w] = update(L[v], tl, tm, i);
        R[w] = update(R[v], tm+1, tr, i);
    }
    s[w] = s[v] + 1;
    return w;
}

int query(int a, int b, int tl, int tr, int l, int r){
    if(tl > r || tr < l) return 0;
    if(tl >= l && tr <= r) return s[a] - s[b];
    return query(L[a], L[b], tl, tm, l, r) + query(R[a], R[b], tm+1, tr, l, r);
}

int binary_search(int a, int b, int tl, int tr, int k){
    if(tl == tr) return tl;
    if(s[ L[a] ] - s[ L[b] ] < k)
        return binary_search(R[a], R[b], tm+1, tr, k - (s[ L[a] ] - s[ L[b] ]));
    return binary_search(L[a], L[b], tl, tm, k);
}

int can(int m, int *K){
    stack < pair < int , pair< int, int > > > S;
    S.push(mp(0, mp(N, 0)));
    sort(K, K + m);
    for(int i = 0; i < m; i++){
        int last, req, x;
        last = req = x = K[i];
        int ex = 0;
        for(;;){
            int z = S.top().nd.st;
            if(z < last){
                S.pop();
                continue;
            }
            if(z == last){
                ex += S.top().nd.nd;
                S.pop();
                continue;
            }

            int y = S.top().st;
            int t = S.top().nd.st;
            int l = binary_search(root[x], root[y], 1, n, req + ex + query(root[x], root[y], 1, n, 1, last - 1));
            if(l >= t){
                req -= query(root[x], root[y], 1, n, last, t-1) - ex;
                last = t;
                ex = S.top().nd.nd;
                S.pop();
                continue;
            }
            else{
                req -= query(root[x], root[y], 1, n, last, l) - ex;
                if(req > 0)
                    return 0;
                ex = req + query(root[x], root[y], 1, n, l, l);
                S.push(mp(x, mp(l, ex)));
                break;
            }
        }
    }

    return 1;
}

vector < int > V[N];
void init(int ss, int *a, int *b){
    n = ss;
    for(int i = 0; i < n; i++)
        V[ a[i] ].push_back(b[i]);
    
    int p = 0;
    for(int i = 1; i <= n; i++){
        for(auto t: V[i])
            p = update(p, 1, n, t);
        root[i] = p;
    }
}
