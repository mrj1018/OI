#include <cstdio>
#define MAXN 100005
#define MAXM 200005
#define MAXCHAR 15
#define INF 100000000005ll
#define ROOT 1
using namespace std;
typedef long long ll;
int n;
ll p[MAXN];
int fst[MAXN],nxt[MAXM];
int g[MAXM];
ll f[MAXN][3];
char data_type[MAXCHAR];
int main(void){
    int m;
    int edges=0;
    scanf("%d%d",&n,&m);
    scanf("%s",data_type);
    for (int i=1;i<=n;i++)
        scanf("%lld",p+i);
    for (int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        
        edges++;
        g[edges]=v;
        nxt[edges]=fst[u];
        fst[u]=edges;
        
        edges++;
        g[edges]=u;
        nxt[edges]=fst[v];
        fst[v]=edges;
    }
    
    while (m--){
        int a,x,b,y;
        scanf("%d%d%d%d",&a,&x,&b,&y);
        //Judge -1
        if ((!x) && (!y)){
            int ok=1;
            for (int ei=fst[a];ei;ei=nxt[ei]){
                if (g[ei]==b){
                    ok=0;
                    break;
                }
            }
            if (!ok){
                printf("-1\n");
                continue;
            }
        }
        int ap=p[a],bp=p[b];
        p[a]=x?(-INF):(INF);
        p[b]=y?(-INF):(INF);
        dfs(ROOT);
    }
    
    return 0;
}
