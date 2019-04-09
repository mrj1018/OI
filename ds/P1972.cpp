// luogu-judger-enable-o2
//P1972
#include <cstdio>
#include <algorithm>
#define LOWBIT(x) ((x)&(-(x)))
#define MAXN 500005
#define MAXC 1000005
using namespace std;
struct Query{
    int l,r,id;
    friend bool operator<(const Query& lhs,const Query& rhs);
};
int n;
int pre[MAXN]={0};
int lst[MAXC]={0};
int tarr[MAXN];
int ans[MAXN];
Query qs[MAXN];
void add(int x,int v);
int query(int x);
int main(void){
    int m;
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        int tcol;
        scanf("%d",&tcol);
        pre[i]=lst[tcol],lst[tcol]=i;
    }
    scanf("%d",&m);
    for (int i=1;i<=m;i++)
        scanf("%d%d",&qs[i].l,&qs[i].r),qs[i].id=i;
    sort(qs+1,qs+1+m);
    int tr=0;
    for (int i=1;i<=m;i++){
        int cl=qs[i].l,cr=qs[i].r;
        while (tr<cr){
            //Add tr+1
            tr++;
            if (pre[tr])
                add(pre[tr],-1);
            add(tr,1);
        }
        ans[qs[i].id]=query(cr)-query(cl-1);
    }
    for (int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
    return 0;
}

void add(int x,int v){
    while (x<=n){
        tarr[x]+=v;
        x+=LOWBIT(x);
    }
}

int query(int x){
    int ans=0;
    while (x){
        ans+=tarr[x];
        x-=LOWBIT(x);
    }
    return ans;
}

bool operator<(const Query& lhs,const Query& rhs){
    return lhs.r<rhs.r;
}
