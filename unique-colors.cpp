// dfs and set/map swap technique example
// https://www.hackerrank.com/challenges/unique-colors/problem
#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define st first
#define nd second
using ll = long long;
const int N = 1e5 + 5;

unordered_map < int , ll > M[N];
vector < int > V[N], Y[N];
ll size[N], down[N], up[N], A[N], T[N], n;

void f(int x){
    size[x] = down[x] = 1;
    for(auto y: V[x])
        if(!size[y]){
            f(y);
            size[x] += size[y];
            T[y] = M[y][ A[x] ];
            down[x] += up[y] = down[y] + size[y] - M[y][ A[x] ];
            if(M[y].size() > M[x].size())
                M[x].swap(M[y]);
            for(auto t: M[y])
                M[x][t.st] += t.nd;
        }

    M[x][ A[x] ] = size[x];
}

void g(int x, int p){
    up[x] *= -1;
    up[x] += Y[ A[x] ].size() > 0 ? Y[ A[x] ].back() : n - M[1][ A[x] ];
    up[x] += up[p] + down[p];
    for(auto y: V[x])
        if(y != p){
            Y[ A[x] ].pb(size[y] - T[y]);
            g(y, x);
            Y[ A[x] ].pop_back();
        }
}

int main(){
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> A[i];
    for(int i = 1; i < n; i++){
        int x, y;
        cin >> x >> y;
        V[x].pb(y); V[y].pb(x);
    }

    f(1);
    g(1, 0);

    for(int i = 1; i <= n; i++)
        cout << down[i] + up[i] << "\n";

    return 0;
}
