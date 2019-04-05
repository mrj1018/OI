#include <cstdio>
#include <algorithm>
#define MAXN 100005
#define INF 919260817
using namespace std;
int uset[MAXN];
int xi[MAXN],yi[MAXN];
int mxx[MAXN],mxy[MAXN];
int mnx[MAXN],mny[MAXN];
int ufind(int x);
int main(void){
    int n,m;
    int ans=INF;
    freopen("fenceplan.in","r",stdin);
    freopen("fenceplan.out","w",stdout);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++){
        scanf("%d%d",&xi[i],&yi[i]);
        mxx[i]=mnx[i]=xi[i];
        mxy[i]=mny[i]=yi[i];
        uset[i]=i;
    }
    while (m--){
        int u,v,pu,pv;
        scanf("%d%d",&u,&v);
        pu=ufind(u),pv=ufind(v);
        if (pu!=pv)
            uset[pv]=pu;
    }
    for (int i=1;i<=n;i++){
        int pi=ufind(i);
        mxx[pi]=max(mxx[pi],xi[i]);
        mnx[pi]=min(mnx[pi],xi[i]);
        mxy[pi]=max(mxy[pi],yi[i]);
        mny[pi]=min(mny[pi],yi[i]);
    }
    for (int i=1;i<=n;i++){
        int pi=ufind(i);
        int tlen=mxx[pi]-mnx[pi]+mxy[pi]-mny[pi];
        //printf("%d in %d, %d->%d, %d->%d, %d.\n",i,pi,mnx[pi],mxx[pi],mny[pi],mxy[pi],tlen);
        if (tlen<ans)
            ans=tlen;
    }
    printf("%d\n",ans<<1);
    return 0;
}

inline int ufind(int x){
    int t,par=x;
    while (uset[par]!=par)
        par=uset[par];
    while (x!=par)
        t=uset[x],uset[x]=par,x=t;
    return par;
}