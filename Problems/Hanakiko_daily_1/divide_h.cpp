#include <cstdio>
#include <cctype>
#define MAXN 1005
#define MAXM 50005
#define MAXB 1005
#define INF 19260817
using namespace std;
int ans=0,rnd=-1;
int fst[MAXN],nxt[MAXM],edges=0;
int q[MAXN];
int limit[MAXN],used[MAXN],visited[MAXN];
int chose[MAXN];
int only[MAXN];
int namelist[MAXN][MAXB];
int g[MAXM];
void addedge(int u,int v);
int dfs(int x);
int uread(void);
int main(void){
    int students,classes;
    students=uread(),classes=uread();
    for (int i=1;i<=classes;i++){
        int fi;
        fi=uread();
        limit[i]=fi;
    }
    for (int i=1;i<=students;i++){
        int cnt;
        cnt=uread();
        while (cnt--){
            int ti;
            ti=uread();
            addedge(i,ti);
        }
    }
    for (int i=1;i<=students;i++)
        (rnd=i,dfs(i))?(ans++):(0);
    printf("%d\n",ans);
    
    int head=0,tail=0;
    for (int i=1;i<=classes;i++)
        if (used[i]<limit[i])
            q[tail++]=i;
    
    for (int i=1;i<=students;i++){
        if (chose[i]){
            printf("%d ",chose[i]);
            continue;
        }
        printf("%d ",q[head]);
        used[q[head]]++;
        if (used[q[head]]==limit[q[head]])
            head++;
    }
    putchar('\n');
    return 0;
}

int dfs(int x){
    //Match for x
    for (int ei=fst[x];ei;ei=nxt[ei]){
        int tv=g[ei];
        if (tv==chose[x] || visited[tv]==rnd)
            continue;
        visited[tv]=rnd;
        if (used[tv]<limit[tv]){
            chose[x]=tv;
            namelist[tv][used[tv]]=x;
            used[tv]++;
            return 1;
        }
        for (int j=0;j<used[tv];j++){
            if ((!only[namelist[tv][j]]) && dfs(namelist[tv][j])){
                chose[x]=tv;
                namelist[tv][j]=x;
                return 1;
            }
        }
    }
    only[x]=1;
    return 0;
}

void addedge(int u,int v){
    edges++;
    g[edges]=v;
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