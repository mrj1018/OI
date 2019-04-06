#include <cstdio>
#include <algorithm>
const int MAXN=100005;
const int INF=500000000;
using namespace std;
struct Basket{
    int a,b,c;
    Basket(void):a(0),b(0),c(0){}
    Basket(int ta,int tb,int tc):a(ta),b(tb),c(tc){}
    Basket(const Basket& tb):a(tb.a),b(tb.b),c(tb.c){}
    friend bool operator<(const Basket& lhs,const Basket& rhs);
    friend bool operator==(const Basket& lhs,const Basket& rhs);
};
struct Num{
    int x,p;
    Num(void):x(0),p(0){}
    Num(int tx,int tp):x(tx),p(tp){}
    Num(const Num& tn):x(tn.x),p(tn.p){}
    friend bool operator<(const Num& lhs,const Num& rhs);
};

Basket ele[MAXN],tarr[MAXN];
Num as[MAXN],bs[MAXN],cs[MAXN];
bool cmp(const Basket& lhs,const Basket& rhs);

int main(void){
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        int ta,tb,tc;
        scanf("%d%d%d",&ta,&tb,&tc);
        ele[i].a=ta,ele[i].b=tb,ele[i].c=tc;
    }
    sort(ele+1,ele+n+1);
    n=unique(ele+1,ele+n+1)-ele-1;
    int mxa=0,ans=ele[n].a;
    for (int i=1;i<n;i++){
        int tn=n-i;
        mxa=ele[i].a;
        //[1,i],[i+1,n]
        for (int j=i+1,tj=0;j<=n;j++,tj++)
            tarr[tj]=ele[j];
        sort(tarr,tarr+tn,cmp);
        int tans=tarr[tn-1].b,mxc=0;
        for (int j=tn-2;~j;j--){
            //[1,j],[j+1,tn)
            (tarr[j+1].c>mxc)?(mxc=tarr[j+1].c):(0);
            (tarr[j].b+mxc<tans)?(tans=tarr[j].b+mxc):(0);
        }
        (tans+mxa<ans)?(ans=tans+mxa):(0);
    }
    printf("%d\n",ans);
    return 0;
}

bool operator<(const Basket& lhs,const Basket& rhs){
    if (lhs.a<rhs.a)
        return 1;
    if (lhs.a>rhs.a)
        return 0;
    if (lhs.b<rhs.b)
        return 1;
    if (lhs.b>rhs.b)
        return 0;
    return (lhs.c<rhs.c);
}

bool operator==(const Basket& lhs,const Basket& rhs){
    return lhs.a==rhs.a && lhs.b==rhs.b && lhs.c==rhs.c;
}

bool operator<(const Num& lhs,const Num& rhs){
    return lhs.x<rhs.x;
}

bool cmp(const Basket& lhs,const Basket& rhs){
    if (lhs.b<rhs.b)
        return 1;
    if (lhs.b>rhs.b)
        return 0;
    return (lhs.c<rhs.c);
}