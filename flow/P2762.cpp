//P2762.cpp 太空飞行计划问题 网络流24题 s-t割
#include <iostream>
#include <algorithm>
#define MAXN 1005
#define MAXM 10005
#define INF 19260817
using namespace std;
struct Edge{
    int u,v,f,c;
    Edge(void){}
    Edge(int tu,int tv,int tf,int tc):u(tu),v(tv),f(tf),c(tc){}
    Edge(const Edge& te):u(te.u),v(te.v),f(te.f),c(te.c){}
};
int fst[MAXN],nxt[MAXM];
Edge g[MAXM];
int edges=1,s,t;
void addedge(int u,int v,int f,int c);

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int m,n;
    int ans=0;
    cin >> m >> n;
    s=m+n+1,t=s+1;
    //Experiments:1...m
    //Instruments:m+1...m+n
    //s:m+n+1, t:m+n+2
    for (int i=1;i<=m;i++){
        int w;
        ans+=w;
        addedge(s,i,INF,w);
        addedge(i,s,0,-w);
        
    }
    return 0;
}

void addedge(int u,int v,int f,int c){
    edges++;
    g[edges]=Edge(u,v,f,c);
    nxt[edges]=fst[u];
    fst[u]=edges;
}
