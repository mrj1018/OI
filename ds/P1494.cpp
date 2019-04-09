#include <cstdio>
#include <cmath>
#include <algorithm>
#define MAXN 50005
using namespace std;
typedef long long ll;
struct Query{
    int l,r,id;
    friend bool operator<(const Query& lhs,const Query& rhs);
};
int a[MAXN],bel[MAXN];
ll ans_a[MAXN],ans_b[MAXN];
int cnt[MAXN]={0};
Query qs[MAXN];
ll gcd(ll a,ll b);
int main(void){
    int n,m;
    scanf("%d%d",&n,&m);
    int blen;
    blen=sqrt(n);
    for (int i=1;i<=n;i++){
        scanf("%d",a+i);
        bel[i]=(i-1)/blen+1;
    }
    for (int i=1;i<=m;i++){
        int tl,tr;
        scanf("%d%d",&tl,&tr);
        qs[i].l=tl,qs[i].r=tr,qs[i].id=i;
    }
    sort(qs+1,qs+m+1);
    qs[0].l=1,qs[0].r=1;
    cnt[a[1]]=1;
    ll tsum=1;
    for (int i=1;i<=m;i++){
        int tl,tr,cl,cr,id; //Last l,r; Current l,r
        tl=qs[i-1].l,tr=qs[i-1].r;
        cl=qs[i].l,cr=qs[i].r;
        id=qs[i].id;
        while (tl<cl) //Remove tl
            tsum-=(ll)(cnt[a[tl]])*(cnt[a[tl]]),cnt[a[tl]]--,tsum+=(ll)(cnt[a[tl]])*(cnt[a[tl]]),tl++;
        while (tl>cl) //Add tl-1
            tl--,tsum-=(ll)(cnt[a[tl]])*(cnt[a[tl]]),cnt[a[tl]]++,tsum+=(ll)(cnt[a[tl]])*(cnt[a[tl]]);
        while (tr>cr) //Remove tr
            tsum-=(ll)(cnt[a[tr]])*(cnt[a[tr]]),cnt[a[tr]]--,tsum+=(ll)(cnt[a[tr]])*(cnt[a[tr]]),tr--;
        while (tr<cr) //Add tr+1
            tr++,tsum-=(ll)(cnt[a[tr]])*(cnt[a[tr]]),cnt[a[tr]]++,tsum+=(ll)(cnt[a[tr]])*(cnt[a[tr]]);
        ll ta,tb;
        ta=tsum-(cr-cl+1);
        tb=(ll)(cr-cl+1)*(cr-cl);
        if (!ta)
            ans_a[id]=0,ans_b[id]=1;
        else {
            ll g=gcd(ta,tb);
            ans_a[id]=ta/g,ans_b[id]=tb/g;
        }
    }
    for (int i=1;i<=m;i++)
        printf("%lld/%lld\n",ans_a[i],ans_b[i]);
    return 0;
}

ll gcd(ll a,ll b){
    ll t;
    while (b)
        t=a,a=b,b=t%b;
    return a;
}

bool operator<(const Query& lhs,const Query& rhs){
    return (bel[lhs.l]==bel[rhs.l])?((bel[lhs.l]&1)?(lhs.r<rhs.r):(lhs.r>rhs.r)):(bel[lhs.l]<bel[rhs.l]);
}
