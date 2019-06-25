#include <cstdio>
#include <cctype>
#define MAXIOLG 25
#define FILENAME(x)\
freopen(x".in","r",stdin);\
freopen(x".out","w",stdout);
#define MAXN 100005
#define MAXM 200005
#define LOWBIT(x) ((x)&(-(x)))
using namespace std;

typedef int io_t;
typedef long long ll;
io_t shin[MAXIOLG];
io_t seto(void);
void ayano(io_t x,char spliter='\n');

int g[MAXM],fst[MAXN],nxt[MAXM],edges=0;
int par[MAXN],pch[MAXN],depth[MAXN],sz[MAXN];
int dfn[MAXN],dfnend[MAXN],top[MAXN],pcnt=0;

int w[MAXN];
int tarr[MAXN],tarri[MAXN];

void dfs1(int x,int pa);
void dfs2(int x,int pa,int tp);
void add_tree(int x,int v);
int query_tree(int x);
void add_path(int x,int y,int v);
int query_path(int x,int y);
void add_int(int x,int y,int v);
int query_int(int x,int y);
void addedge(int u,int v);
void add(int *a,int x,int v);
int query(int *a,int x);

int main(void){
    int n,m,r;
    n=seto(),m=seto(),r=seto();
    for (int i=1;i<=n;i++)
        w[i]=seto();
    for (int i=1;i<n;i++){
        int u=seto(),v=seto();
        addedge(u,v),addedge(v,u);
    }
    dfs1(r,0),dfs2(r,0,r);
    for (int i=1;i<=n;i++)
        add_int(dfn[i],dfn[i],w[i]);
    while (m--){
        int op,x,y,z;
        op=seto();
        switch (op){
            case 1:
                x=seto(),y=seto(),z=seto();
                add_path(x,y,z);
                break;
            case 2:
                x=seto(),y=seto();
                ayano(query_path(x,y));
                break;
            case 3:
                x=seto(),z=seto();
                add_tree(x,z);
                break;
            case 4:
                x=seto();
                ayano(query_tree(x));
                break;
        }
    }
    return 0;
}

void dfs1(int x,int pa){
    sz[x]=1,par[x]=pa,depth[x]=depth[pa]+1;
    int pchsz=0,pchi=0;
    for (int ei=fst[x];ei;ei=nxt[ei]){
        int v=g[ei];
        if (v==pa)
            continue;
        dfs1(v,x);
        sz[x]+=sz[v];
        (sz[v]>pchsz)?(pchsz=sz[v],pchi=v):(0);
    }
    pch[x]=pchi;
}

void dfs2(int x,int pa,int tp){
    pcnt++,dfn[x]=pcnt;
    top[x]=tp;
    if (!pch[x]){
        dfnend[x]=pcnt;
        return;
    }
    dfs2(pch[x],x,tp);
    for (int ei=fst[x];ei;ei=nxt[ei]){
        int v=g[ei];
        if (dfn[v])
            continue;
        dfs2(v,x,v);
    }
    dfnend[x]=pcnt;
}

void add_tree(int x,int v){
    add_int(dfn[x],dfnend[x],v);
}

int query_tree(int x){
    return query_int(dfn[x],dfnend[x]);
}

void add_path(int x,int y,int v){
    while (top[x]!=top[y])
        (depth[top[x]]>depth[top[y]])?
        (add_int(dfn[top[x]],dfn[x],v),x=par[top[x]]):
        (add_int(dfn[top[y]],dfn[y],v),y=par[top[y]]);
    (depth[x]<depth[y])?(add_int(dfn[x],dfn[y],v)):(add_int(dfn[y],dfn[x],v));
}

int query_path(int x,int y){
    int ans=0;
    while (top[x]!=top[y])
        (depth[top[x]]>depth[top[y]])?
        (ans+=query_int(dfn[top[x]],dfn[x]),x=par[top[x]]):
        (ans+=query_int(dfn[top[y]],dfn[y]),y=par[top[y]]);
    (depth[x]<depth[y])?(ans+=query_int(dfn[x],dfn[y])):(ans+=query_int(dfn[y],dfn[x]));
    return ans;
}

void add_int(int l,int r,int v){
    add(tarr,l,v);
    add(tarr,r+1,-v);
    add(tarri,l,(ll)(v)*l);
    add(tarri,r+1,(ll)(-v)*(r+1));
}

int query_int(int l,int r){
    int ans=query(tarr,r)*(ll)(r+1);
    ans=(ans-(query(tarr,l-1)*(ll)(l)));
    ans=(ans-query(tarri,r)+query(tarri,l-1));
    return ans;
}

void add(int *a,int x,int v){
    while (x<=pcnt){
        a[x]+=v;
        x+=LOWBIT(x);
    }
}

int query(int *a,int x){
    int ans=0;
    while (x){
        ans+=a[x];
        x-=LOWBIT(x);
    }
    return ans;
}

void addedge(int u,int v){
    edges++;
    g[edges]=v;
    nxt[edges]=fst[u],fst[u]=edges;
}

io_t seto(void){
    io_t ans=0;
    int symbol=0;
    char ch=getchar();
    while (!isdigit(ch))
        (ch=='-')?(symbol=1):(0),ch=getchar();
    while (isdigit(ch))
        (ans=ans*10+(ch-'0')),ch=getchar();
    return (symbol)?(-ans):(ans);
}

void ayano(io_t x,char spliter){
    if (!x){
        putchar('0'),putchar(spliter);
        return;
    }
    if (x<0)
        putchar('-'),x=-x;
    int len=0;
    while (x){
        io_t d=x/10;
        shin[len++]=x-d*10;
        x=d;
    }
    while (len){
        len--;
        putchar(shin[len]+'0');
    }
    putchar(spliter);
}
