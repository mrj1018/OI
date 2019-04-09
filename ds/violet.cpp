#include <cstdio>
#include <algorithm>
#include <cmath>
#include <map>
#define MAXB 205
#define MAXN 40005
using namespace std;

int a[MAXN],bel[MAXN];
int inv[MAXN];
int f[MAXB][MAXB];
int tcnt[MAXN],visited[MAXN];
int cnt[MAXB][MAXN];
map<int,int> mp;
int main(void){
    int n,m,s=0;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++){
        int t;
        scanf("%d",&t);
        if (mp.count(t))
            a[i]=mp[t];
        else {
            s++;
            inv[s]=t;
            mp[t]=s;
            a[i]=s;
        }
    }
    int blen,bls;
    blen=sqrt(n);
    bls=(n-1)/blen+1; //Ceil
    for (int i=1;i<=n;i++){
        bel[i]=(i-1)/blen+1;
        cnt[bel[i]][a[i]]++;
    }
    for (int i=2;i<=bls;i++)
        for (int j=1;j<=s;j++)
            cnt[i][j]+=cnt[i-1][j];
    //Calc f
    for (int i=1;i<=bls;i++){
        for (int t=1;t<=s;t++)
            tcnt[t]=0;
        int mxi=0,mxcnt=0;
        for (int j=i;j<=bls;j++){
            int ub=j*blen;
            for (int k=(j-1)*blen+1;k<=ub;k++){
                tcnt[a[k]]++;
                if (tcnt[a[k]]<mxcnt)
                    continue;
                if (inv[a[k]]<inv[mxi] || tcnt[a[k]]>mxcnt)
                    mxi=a[k],mxcnt=tcnt[a[k]];
            }
            f[i][j]=mxi;
        }
    }
    int x=0;
    while (m--){
        int l,r,t;
        scanf("%d%d",&l,&r);
        l=(l+x-1)%n+1,r=(r+x-1)%n+1;
        (l>r)?(t=l,l=r,r=t):(0);
        for (int i=1;i<=s;i++)
            tcnt[i]=visited[i]=0;
        if (bel[l]==bel[r]){
            int mxi=0,mxcnt=0;
            for (int i=l;i<=r;i++){
                tcnt[a[i]]++;
                if (tcnt[a[i]]<mxcnt)
                    continue;
                if (inv[a[i]]<inv[mxi] || tcnt[a[i]]>mxcnt)
                    mxi=a[i],mxcnt=tcnt[a[i]];
            }
            printf("%d\n",x=inv[mxi]);
            continue;
        }

        if (bel[l]+1<bel[r]){
            int opb=bel[l]+1,edb=bel[r]-1;
            int mxi=f[opb][edb];
            visited[mxi]=1;
            tcnt[mxi]+=(cnt[edb][mxi]-cnt[bel[l]][mxi]);
            int mxcnt=tcnt[mxi];
            int ub=bel[l]*blen;
            for (int i=l;i<=ub;i++){
                tcnt[a[i]]++;
                (!visited[a[i]])?(visited[a[i]]=1,tcnt[a[i]]+=(cnt[edb][a[i]]-cnt[bel[l]][a[i]])):(0);
                if (tcnt[a[i]]<mxcnt)
                    continue;
                if (inv[a[i]]<inv[mxi] || tcnt[a[i]]>mxcnt)
                    mxi=a[i],mxcnt=tcnt[a[i]];
            }
            
            int lb=(bel[r]-1)*blen+1;
            for (int i=lb;i<=r;i++){
                tcnt[a[i]]++;
                (!visited[a[i]])?(visited[a[i]]=1,tcnt[a[i]]+=(cnt[edb][a[i]]-cnt[bel[l]][a[i]])):(0);
                if (tcnt[a[i]]<mxcnt)
                    continue;
                if (inv[a[i]]<inv[mxi] || tcnt[a[i]]>mxcnt)
                    mxi=a[i],mxcnt=tcnt[a[i]];
            }
            printf("%d\n",x=inv[mxi]);
            continue;
        }

        int mxi=0,mxcnt=0;
        int ub=bel[l]*blen;
        for (int i=l;i<=ub;i++){
            tcnt[a[i]]++;
            if (tcnt[a[i]]<mxcnt)
                continue;
            if (inv[a[i]]<inv[mxi] || tcnt[a[i]]>mxcnt)
                mxi=a[i],mxcnt=tcnt[a[i]];
        }
        
        int lb=(bel[r]-1)*blen+1;
        for (int i=lb;i<=r;i++){
            tcnt[a[i]]++;
            if (tcnt[a[i]]<mxcnt)
                continue;
            if (inv[a[i]]<inv[mxi] || tcnt[a[i]]>mxcnt)
                mxi=a[i],mxcnt=tcnt[a[i]];
        }
        printf("%d\n",x=inv[mxi]);
    }
    return 0;
}
