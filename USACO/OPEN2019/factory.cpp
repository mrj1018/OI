#include <cstdio>
#define MAXN 505
using namespace std;
bool g[MAXN][MAXN];
int main(void){
    freopen("factory.in","r",stdin);
    freopen("factory.out","w",stdout);
    int n;
    scanf("%d",&n);
    for (int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        g[u][v]=1;
    }
    for (int i=1;i<=n;i++)
        g[i][i]=1;
    for (int k=1;k<=n;k++)
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++)
                g[i][j]|=(g[i][k]&g[k][j]);
    for (int i=1;i<=n;i++){
        bool ok=1;
        for (int j=1;j<=n;j++)
            ok&=g[j][i];
        if (ok){
            printf("%d\n",i);
            return 0;
        }
    }
    printf("-1\n");
    return 0;
}