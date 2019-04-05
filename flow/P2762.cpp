//P2762.cpp 太空飞行计划问题 网络流24题 s-t割
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 1005
#define MAXM 10005
#define INF 19260817
#define IINF 1000000000
using namespace std;
struct Edge{
    int u,v,f,c;
    Edge(void){}
    Edge(int tu,int tv,int tf,int tc):u(tu),v(tv),f(tf),c(tc){}
    Edge(const Edge& te):u(te.u),v(te.v),f(te.f),c(te.c){}
};
int fst[MAXN],nxt[MAXM],cur[MAXN];
int dis[MAXN],q[MAXN],inq[MAXN];
int wei[MAXN];
Edge g[MAXM];
char tempc[MAXM];
int edges=1,s,t;
long long max_flow=0,min_cost=0;
bool spfa(void);
int dfs(int x,int flow);
void addedge(int u,int v,int f,int c);

int main(void){
    //ios::sync_with_stdio(0);
    //cin.tie(0);
    int m,n;
    int ans=0;
    cin >> m >> n;
    s=m+n+1,t=s+1;
    //Experiments:1...m
    //Instruments:m+1...m+n
    //s:m+n+1, t:m+n+2
    for (int i=1;i<=m;i++){
        int w;
        cin >> w;
        wei[i]=w;
        addedge(s,i,w,1);
        addedge(i,s,0,-1);
        memset(tempc,0,sizeof(tempc));
        cin.getline(tempc,MAXM);
        int ulen=0,tool;
        while (sscanf(tempc+ulen,"%d",&tool)==1){ 
            addedge(i,tool+m,INF,1);
            addedge(tool+m,i,0,-1);
            if (tool==0)
                ulen++;
            else {
                while (tool){
                    tool/=10;
                    ulen++;
                }
            }
            ulen++;
        }
    }
    for (int i=m+1;i<=m+n;i++){
        int cost;
        cin >> cost;
        wei[i]=cost;
        addedge(i,t,cost,1);
        addedge(t,i,0,-1);
    }
    while (spfa())
        dfs(s,IINF);
    for (int i=1;i<=m;i++){
        if (dis[i]<IINF){
           cout << i << ' ';
           ans+=wei[i];
        }
    }
    cout << endl;
    for (int i=m+1;i<=m+n;i++){
        if (dis[i]<IINF){
            cout << (i-m) << ' ';
            ans-=wei[i];
        }
    }
    cout << endl << ans << endl;
    return 0;
}

bool spfa(void){
    for (int i=1;i<=t;i++)
        cur[i]=fst[i],dis[i]=IINF,inq[i]=0;
    int head=0,tail=0;
    dis[s]=0,inq[s]=1;
    q[tail++]=s;
    while (head!=tail){
        int nowv=q[head++];
        inq[nowv]=0;
        if (head==MAXN)
           head=0;
        for (int ei=fst[nowv];ei;ei=nxt[ei]){
            if (!g[ei].f)
               continue;
            int tv=g[ei].v,tc=g[ei].c;
            if (dis[tv]>dis[nowv]+tc){
                dis[tv]=dis[nowv]+tc;
                if (!inq[tv]){
                    inq[tv]=1;
                    q[tail++]=tv;
                    if (tail==MAXN)
                       tail=0;
                }
            }
        }
    }
    return dis[t]<IINF;
}

int dfs(int x,int flow){
    if (x==t){
        max_flow+=flow;
        return 1;
    }
    int used=0;
    inq[x]=1;
    for (int ei=cur[x];ei;ei=nxt[ei]){
        cur[x]=ei;
        int tv=g[ei].v,tf=g[ei].f,tc=g[ei].c;
        if (!(dis[tv]==dis[x]+tc && (!inq[tv]) && tf))
            continue;
        (tf>flow)?(tf=flow):(0);
        int tflow;
        if ((tflow=dfs(tv,tf))){
            used+=tflow,flow-=tflow;
            g[ei].f-=tflow;
            g[ei^1].f+=tflow;
            min_cost+=(long long)tc*tflow;
            if (!flow)
               break;
        }
    }
    return used;
}

void addedge(int u,int v,int f,int c){
    edges++;
    g[edges]=Edge(u,v,f,c);
    nxt[edges]=fst[u];
    fst[u]=edges;
}
