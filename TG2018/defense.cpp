#include <cstdio>
#define MAXN 100005
#define MAXM 200005
#define MAXLG 19
#define MAXCHAR 15
#define INF 100000000005ll
#define ROOT 1
using namespace std;
typedef long long ll;
int n;
ll p[MAXN];
int fst[MAXN],nxt[MAXM];
int depth[MAXN];
int g[MAXM];
ll f[MAXN][3];
int par[MAXLG][MAXN];
char data_type[MAXCHAR];

void dfs(int x,int pa);
int getlca(int x,int y);
void calcpar(void);

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

    dfs(ROOT,0);
    
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
        p[a]=(x)?(-INF):(INF);
        p[b]=(y)?(-INF):(INF);
        dfs(ROOT,0);
        ll ans=INF+INF+INF;
        (f[ROOT][0]<ans)?(ans=f[ROOT][0]):(0);
        (f[ROOT][1]<ans)?(ans=f[ROOT][1]):(0);
        p[a]=ap;
        p[b]=bp;
        (x)?(ans+=(INF+ap)):(0);
        (y)?(ans+=(INF+bp)):(0);
        printf("%lld\n",ans);
    }
    return 0;
}

void calcpar(void){
    for (int lg=1;lg<MAXLG;lg++)
        for (int i=1;i<=n;i++)
            par[lg][i]=par[lg-1][par[lg-1][i]];
}

void dfs(int x,int pa){
    ll chose=p[x];
    ll n_chose=0;
    
    par[0][x]=pa;
    depth[x]=depth[pa]+1;
    for (int ei=fst[x];ei;ei=nxt[ei]){
        int v=g[ei];
        if (v==pa)
            continue;
        dfs(v,x);
        n_chose+=f[v][1];
        chose+=(f[v][0]<f[v][1])?(f[v][0]):(f[v][1]);
    }
    
    f[x][0]=n_chose;
    f[x][1]=chose;
}

int getlca(int x,int y){
    if (x==y)
        return x;
    if (depth[x]>depth[y]){
        //swap
        int t=x;
        x=y,y=t;
    }
    if (depth[y]>depth[x]){
        //y jump up
        int t=depth[y]-depth[x];
        int i=0;
        while (t){
            if (t&1)
                y=par[i][y];
            t>>=1;
            i++;
        }
    }
    if (x==y)
        return x;
    for (int lg=MAXLG-1;~lg;lg--){
        
    }
}
