#include <cstdio>
#define MAXN 100005
#define MAXM 200005
#define MAXCHAR 15
#define INF 100000000005ll
#define ROOT 1
using namespace std;
typedef long long ll;
int n;
int is_changed[MAXN]={0};
ll p[MAXN];
int fst[MAXN],nxt[MAXM];
int g[MAXM];
ll f0[MAXN][3];
ll ft[MAXN][3];
int par[MAXN];
char data_type[MAXCHAR];

void push_up(int x,int tar);
void dfs(int x,int pa);
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
        
        int tpar,lca=ROOT;
        tpar=a;
        while (tpar){
            is_changed[tpar]=1;
            tpar=par[tpar];
        }
        tpar=b;
        while (tpar){
            if (is_changed[tpar]){
                lca=tpar;
                break;
            }
            is_changed[tpar]=1;
            tpar=par[tpar];
        }
        
        push_up(a,lca);
        push_up(b,0);
        
        tpar=a;
        while (tpar){
            is_changed[tpar]=0;
            tpar=par[tpar];
        }
        tpar=b;
        while (is_changed[tpar]){
            is_changed[tpar]=0;
            tpar=par[tpar];
        }
        
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

void push_up(int x,int tar){
    
}

void dfs(int x,int pa){
    ll chose=p[x];
    ll n_chose=0;
    par[x]=pa;
    
    for (int ei=fst[x];ei;ei=nxt[ei]){
        int v=g[ei];
        if (v==pa)
            continue;
        dfs(v,x);
        n_chose+=f0[v][1];
        chose+=(f0[v][0]<f0[v][1])?(f0[v][0]):(f0[v][1]);
    }
    
    f0[x][0]=n_chose;
    f0[x][1]=chose;
}
