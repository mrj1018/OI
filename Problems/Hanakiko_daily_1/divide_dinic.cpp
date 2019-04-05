#include <cstdio>
#include <cctype>
#define MAXN 500005
#define MAXM 500005
#define INF 19260817
struct Edge{
    int u,v,f;
    Edge(void){}
    Edge(int tu,int tv,int tf):u(tu),v(tv),f(tf){}
    Edge(const Edge& te):u(te.u),v(te.v),f(te.f){}
};
using namespace std;
int n,s=1,t=2,edges=1;
int ans=0;
int fst[MAXN],nxt[MAXN],cur[MAXN];
int match[MAXN],last[MAXN];
Edge g[MAXM];
int depth[MAXN],visited[MAXN],q[MAXN];
int bfs(void);
int dfs(int x,int flow);
void addedge(int u,int v,int f);
int uread(void);
int main(void){
    int students,classes;
    students=uread(),classes=uread();
    int studenta,studentb,classa,classb;
    studenta=3,studentb=2+students;
    classa=studentb+1,classb=studentb+classes;
    n=classb;
    for (int i=classa;i<=classb;i++){
        int fi;
        fi=uread();
        last[i-studentb]=fi;
        addedge(i,t,fi);
        addedge(t,i,0);
    }
    for (int i=studenta;i<=studentb;i++){
        int cnt;
        addedge(s,i,1);
        addedge(i,s,0);
        cnt=uread();
        while (cnt--){
            int ti;
            ti=uread();
            ti+=studentb;
            addedge(i,ti,1);
            addedge(ti,i,0);
        }
    }
    while (bfs()){
        dfs(s,INF);
    }
    printf("%d\n",ans);
    for (int ei=2;ei<=edges;ei++){
        int tu=g[ei].u,tv=g[ei].v;
        if (tu>=studenta && tu<=studentb && tv>=classa && tv<=classb && (!g[ei].f)){
            match[tu-2]=tv-studentb;
            last[tv-studentb]--;
        }
    }
    int head=0,tail=0;
    for (int i=1;i<=classes;i++)
        if (last[i])
            q[tail++]=i;
    
    for (int i=1;i<=students;i++){
        if (match[i]){
            printf("%d ",match[i]);
            continue;
        }
        printf("%d ",q[head]);
        last[q[head]]--;
        if (!last[q[head]])
            head++;
    }
    putchar('\n');
    return 0;
}

int bfs(void){
    for (int i=1;i<=n;i++)
        visited[i]=0,depth[i]=INF,cur[i]=fst[i];
    depth[s]=0;
    int head=0,tail=0;
    q[tail++]=s;
    visited[s]=1;
    while (head!=tail){
        int nowv=q[head++];
        int nowdis=depth[nowv];
        visited[nowv]=0;
        for (int ei=fst[nowv];ei;ei=nxt[ei]){
            int tv=g[ei].v,tf=g[ei].f;
            if (tf && depth[tv]>nowdis+1){
                depth[tv]=nowdis+1;
                if (!visited[tv]){
                    visited[tv]=1;
                    q[tail++]=tv;
                }
            }
        }
    }
    return depth[t]!=INF;
}

int dfs(int x,int flow){
    int used=0;
    if (x==t){
        ans+=flow;
        return flow;
    }
    for (int ei=cur[x];ei;ei=nxt[ei]){
        cur[x]=ei;
        int tv=g[ei].v,tf=g[ei].f;
        if ((!tf) || depth[tv]!=depth[x]+1)
            continue;
        (tf>flow)?(tf=flow):(0);
        int tans;
        if ((tans=dfs(tv,tf))){
            used+=tans;
            flow-=tans;
            g[ei].f-=tans;
            g[ei^1].f+=tans;
            if (!flow)
                break;
        }
    }
    return used;
}

void addedge(int u,int v,int f){
    edges++;
    g[edges]=Edge(u,v,f);
    nxt[edges]=fst[u];
    fst[u]=edges;
}

int uread(void){
    int ans=0;
    int symbol=0;
    char ch;
    ch=getchar();
    while (!isdigit(ch)){
        if (ch=='-')
            symbol=1;
        ch=getchar();
    }
    while (isdigit(ch)){
        ans=(ans*10)+(ch-'0');
        ch=getchar();
    }
    return (symbol)?(-ans):(ans);
}