#include <cstdio>
#include <algorithm>
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
ll jf[MAXLG][MAXN][3][3];
int par[MAXLG][MAXN];
char data_type[MAXCHAR];

void dfs(int x,int pa);
int getlca(int x,int y);
void calcpar(void);
void calcjf(void);

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
    calcpar();
    calcjf();
    
    
    while (m--){
        int a,x,b,y,lca;
        ll ans=INF;
        scanf("%d%d%d%d",&a,&x,&b,&y);
        
        lca=getlca(a,b);
        if (lca==a){
            swap(a,b);
            swap(x,y);
        }
        if (lca==b){
            ans=0;
            int i=0,delta_d=depth[a]-depth[b];

            ll v0,v1;
            (x)?(v0=INF,v1=f[a][1]):(v0=f[a][0],v1=INF);

            while (delta_d){
                if (delta_d&1){
                    ll v00,v10;
                    v00=min(v0+jf[i][a][0][0],v1+jf[i][a][0][1]);
                    v10=min(v0+jf[i][a][1][0],v1+jf[i][a][1][1]);
                    v0=v00;
                    v1=v10;
                    a=par[i][a];
                }
                delta_d>>=1;
                i++;
            }

            (y)?(v0=INF):(v1=INF);
            i=0,delta_d=depth[b];
            while (delta_d){
                if (delta_d&1){
                    ll v00,v10;
                    v00=min(v0+jf[i][b][0][0],v1+jf[i][b][0][1]);
                    v10=min(v0+jf[i][b][1][0],v1+jf[i][b][1][1]);
                    v0=v00;
                    v1=v10;
                    b=par[i][b];
                }
                delta_d>>=1;
                i++;
            }

            ans=min(v0,v1);
            if (ans>=INF){
                printf("-1\n");
                continue;
            }
            printf("%lld\n",ans);
            continue;
        }

        ll v0x,v1x,v0y,v1y;
        (x)?(v0x=INF,v1x=f[a][1]):(v0x=f[a][0],v1x=INF);
        int i=0,delta_d=depth[a]-depth[lca]-1;
        while (delta_d){
            if (delta_d&1){
                ll v00,v10;
                v00=min(v0x+jf[i][a][0][0],v1x+jf[i][a][0][1]);
                v10=min(v0x+jf[i][a][1][0],v1x+jf[i][a][1][1]);
                v0x=v00;
                v1x=v10;
                a=par[i][a];
            }
            delta_d>>=1;
            i++;
        }

        (y)?(v0y=INF,v1y=f[b][1]):(v0y=f[b][0],v1y=INF);
        i=0,delta_d=depth[b]-depth[lca]-1;
        while (delta_d){
            if (delta_d&1){
                ll v00,v10;
                v00=min(v0y+jf[i][b][0][0],v1y+jf[i][b][0][1]);
                v10=min(v0y+jf[i][b][1][0],v1y+jf[i][b][1][1]);
                v0y=v00;
                v1y=v10;
                b=par[i][b];
            }
            delta_d>>=1;
            i++;
        }

        ll v0,v1;
        v0=f[lca][0]-f[a][1]-f[b][1]+v1x+v1y;
        v1=f[lca][1]-min(f[a][0],f[a][1])-min(f[b][0],f[b][1])+min(v1x,v0x)+min(v1y,v0y);

        i=0,delta_d=depth[lca];
        while (delta_d){
            if (delta_d&1){
                ll v00,v10;
                v00=min(v0+jf[i][lca][0][0],v1+jf[i][lca][0][1]);
                v10=min(v0+jf[i][lca][1][0],v1+jf[i][lca][1][1]);
                v0=v00;
                v1=v10;
                lca=par[i][lca];
            }
            delta_d>>=1;
            i++;
        }
        ans=min(v0,v1);
        if (ans>=INF){
            printf("-1\n");
            continue;
        }
        printf("%lld\n",ans);
    }
    return 0;
}

void calcpar(void){
    for (int lg=1;lg<MAXLG;lg++)
        for (int i=1;i<=n;i++)
            par[lg][i]=par[lg-1][par[lg-1][i]];
}

void calcjf(void){
    //jf[0]
    for (int i=2;i<=n;i++){
        jf[0][i][0][0]=INF;
        jf[0][i][0][1]=f[par[0][i]][0]-f[i][1];
        ll tf=(f[i][0]<f[i][1])?(f[i][0]):(f[i][1]);
        jf[0][i][1][0]=jf[0][i][1][1]=f[par[0][i]][1]-tf;
    }
    //jf[lg]
    for (int lg=1;lg<MAXLG;lg++){
        for (int i=1;i<=n;i++){
            ll t0,t1;
            int tpar=par[lg-1][i];
            //0,0
            t0=jf[lg-1][i][0][0]+jf[lg-1][tpar][0][0];
            t1=jf[lg-1][i][1][0]+jf[lg-1][tpar][0][1];
            jf[lg][i][0][0]=(t0<t1)?(t0):(t1);
            //1,0
            t0=jf[lg-1][i][0][0]+jf[lg-1][tpar][1][0];
            t1=jf[lg-1][i][1][0]+jf[lg-1][tpar][1][1];
            jf[lg][i][1][0]=(t0<t1)?(t0):(t1);
            //0,1
            t0=jf[lg-1][i][0][1]+jf[lg-1][tpar][0][0];
            t1=jf[lg-1][i][1][1]+jf[lg-1][tpar][0][1];
            jf[lg][i][0][1]=(t0<t1)?(t0):(t1);
            //1,1
            t0=jf[lg-1][i][0][1]+jf[lg-1][tpar][1][0];
            t1=jf[lg-1][i][1][1]+jf[lg-1][tpar][1][1];
            jf[lg][i][1][1]=(t0<t1)?(t0):(t1);
        }
    }
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
    for (int lg=MAXLG-1;~lg;lg--)
        if (par[lg][x]!=par[lg][y])
            x=par[lg][x],y=par[lg][y];
    return par[0][x];
}
