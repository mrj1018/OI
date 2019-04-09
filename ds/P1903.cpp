#include <cstdio>
#include <cmath>
#include <algorithm>
#define MAXN 50005
#define MAXC 1000005
using namespace std;
struct Query{
    int l,r,t,id;
    friend bool operator<(const Query& lhs,const Query& rhs);
};
int a[MAXN],b[MAXN],bel[MAXN];
int ans[MAXN];
int cnt[MAXC];
Query qs[MAXN];
int upd_x[MAXN],upd_col[MAXN],raw_col[MAXN];
int getop(void);
int main(void){
    int n,m,q=0,c=0;
    int blen;
    scanf("%d%d",&n,&m);
    blen=pow(n,0.66667);
    for (int i=1;i<=n;i++){
        scanf("%d",a+i);
        b[i]=a[i];
        bel[i]=(i-1)/blen+1;
    }
    while (m--){
        if (getop()){
            c++;
            scanf("%d%d",upd_x+c,upd_col+c);
            raw_col[c]=b[upd_x[c]];
            b[upd_x[c]]=upd_col[c];
        }
        else {
            int tl,tr;
            q++;
            scanf("%d%d",&tl,&tr);
            qs[q].id=q,qs[q].l=tl,qs[q].r=tr,qs[q].t=c;
        }
    }

    sort(qs+1,qs+1+q);
    int tl=1,tr=0,tt=0,tans=0;
    for (int i=1;i<=q;i++){
        int nl,nr,nt;
        nl=qs[i].l,nr=qs[i].r,nt=qs[i].t;
        while (tl<nl) //Remove tl
            cnt[a[tl]]--,(!cnt[a[tl]])?(tans--):(0),tl++;
        while (tl>nl) //Add tl-1
            tl--,(!cnt[a[tl]])?(tans++):(0),cnt[a[tl]]++;
        while (tr>nr) //Remove tr
            cnt[a[tr]]--,(!cnt[a[tr]])?(tans--):(0),tr--;
        while (tr<nr) //Add tr+1
            tr++,(!cnt[a[tr]])?(tans++):(0),cnt[a[tr]]++;
        while (tt<nt){ //Do tt+1
            tt++;
            if (upd_x[tt]>=nl && upd_x[tt]<=nr){
                cnt[a[upd_x[tt]]]--,(!cnt[a[upd_x[tt]]])?(tans--):(0);
                a[upd_x[tt]]=upd_col[tt];
                (!cnt[a[upd_x[tt]]])?(tans++):(0),cnt[a[upd_x[tt]]]++;
            }
            else
                a[upd_x[tt]]=upd_col[tt];
        }
        while (tt>nt){ //Undo tt
            if (upd_x[tt]>=nl && upd_x[tt]<=nr){
                cnt[a[upd_x[tt]]]--,(!cnt[a[upd_x[tt]]])?(tans--):(0);
                a[upd_x[tt]]=raw_col[tt];
                (!cnt[a[upd_x[tt]]])?(tans++):(0),cnt[a[upd_x[tt]]]++;
            }
            else
                a[upd_x[tt]]=raw_col[tt];
            tt--;
        }
        ans[qs[i].id]=tans;
    }

    for (int i=1;i<=q;i++)
        printf("%d\n",ans[i]);
    return 0;
}

int getop(void){
    char ch=getchar();
    while (ch!='Q' && ch!='R')
        ch=getchar();
    return ch=='R';
}

bool operator<(const Query& lhs,const Query& rhs){
    return (bel[lhs.l]==bel[rhs.l])?((bel[lhs.r]==bel[rhs.r])?(lhs.t<rhs.t):(bel[lhs.r]<bel[rhs.r])):(bel[lhs.l]<bel[rhs.l]);
}
