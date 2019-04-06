#include <cstdio>
#include <algorithm>
const int MAXN=100005;
const int MAX4N=400005;
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
struct Node{
    int l,r,cl,cr,st,mn;
    Node(void):l(0),r(0),cl(0),cr(0),st(0),mn(0){}
    Node(int tl,int tr,int tcl,int tcr,int ts,int tm):l(tl),r(tr),cl(tcl),cr(tcr),st(ts),mn(tm){}
    Node(const Node& tn):l(tn.l),r(tn.r),cl(tn.cl),cr(tn.cr),st(tn.st),mn(tn.mn){}
    #define L(x) ((stree[(x)]).l)
    #define R(x) ((stree[(x)]).r)
    #define MID(x) ((L(x)+R(x))>>1)
    #define CL(x) ((stree[(x)]).cl)
    #define CR(x) ((stree[(x)]).cr)
    #define ST(x) ((stree[(x)]).st)
    #define MN(x) ((stree[(x)]).mn)
    #define LC(x) (((x)<<1))
    #define RC(x) (((x)<<1)^1)
};

int n;
Basket ele[MAXN],tarr[MAXN];
Num bs[MAXN];
Node stree[MAX4N];

void build_tree(int root,int bl,int br);
int find_c(int root,int x);
void update(int root,int l,int r,int x);
int query(int root,int l,int r);
void pushdown(int root);
bool cmp(const Basket& lhs,const Basket& rhs);

int main(void){
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        int ta,tb,tc;
        scanf("%d%d%d",&ta,&tb,&tc);
        ele[i].a=ta,ele[i].b=tb,ele[i].c=tc;
    }
    sort(ele+1,ele+n+1);
    n=unique(ele+1,ele+n+1)-ele-1;
    for (int i=1;i<=n;i++)
        bs[i].x=ele[i].b,bs[i].p=i;
    sort(bs+1,bs+n+1);
    for (int i=1;i<=n;i++)
        ele[bs[i].p].b=i;

    int ans=ele[n].a,mxc=0;
    int ROOT=1;
    build_tree(ROOT,1,n);
    for (int i=n-1;~i;i--){
        int mxa=(i)?(ele[i].a):(0);
        //[1,i],[i+1,n]
        //Add i+1
        int l,r;
        r=ele[i+1].b;              //Elements <r needs to update
        l=find_c(ROOT,ele[i+1].c); //Elements >=l needs to update
        (ele[i+1].c>mxc)?(mxc=ele[i+1].c):(0);
        //Set [l,r) to c
        if (l<r)
            update(ROOT,l,r-1,ele[i+1].c);
        int tans=query(ROOT,1,n);
        (mxa+mxc<tans)?(tans=mxa+mxc):(0);
        (tans+mxa<ans)?(ans=tans+mxa):(0);
    }
    printf("%d\n",ans);
    return 0;
}

//Segment tree

void build_tree(int root,int bl,int br){
    L(root)=bl,R(root)=br;
    CL(root)=CR(root)=0;
    ST(root)=0,MN(root)=bs[bl].x;
    if (bl<br){
        int mid=(bl+br)>>1;
        build_tree(LC(root),bl,mid);
        build_tree(RC(root),mid+1,br);
    }
}
int find_c(int root,int x){
    //Find the minimum place where c<x
    while (L(root)<R(root))
        pushdown(root),(CL(LC(root))<x)?(root=LC(root)):(root=RC(root));
    return (CL(root)<x)?(L(root)):(n+1);
}
void update(int root,int l,int r,int x){
    if (l<=L(root) && r>=R(root)){
        CL(root)=CR(root)=x;
        MN(root)=bs[L(root)].x+x;
        ST(root)=x;
        return;
    }
    if (l>R(root) || r<L(root))
        return;
    pushdown(root);
    (l<=MID(root))?(update(LC(root),l,r,x),0):(0);
    (r> MID(root))?(update(RC(root),l,r,x),0):(0);
    MN(root)=(MN(LC(root))<MN(RC(root)))?(MN(LC(root))):(MN(RC(root)));
    (CL(RC(root))<CL(root))?(CL(root)=CL(RC(root))):(0);
    (CR(LC(root))>CR(root))?(CR(root)=CR(LC(root))):(0);
}
int query(int root,int l,int r){
    if (l<=L(root) && r>=R(root))
        return MN(root);
    if (l>R(root) || r<L(root))
        return INF;
    pushdown(root);
    int ans=INF,tans;
    (l<=MID(root))?((tans=query(LC(root),l,r)<ans)?(ans=tans):(0)):(0);
    (r> MID(root))?((tans=query(RC(root),l,r)<ans)?(ans=tans):(0)):(0);
    return ans;
}
void pushdown(int root){
    if (!ST(root))
        return;
    if (L(root)==R(root)){
        ST(root)=0;
        return;
    }
    CL(LC(root))=CR(LC(root))=ST(root);
    CL(RC(root))=CR(RC(root))=ST(root);
    ST(LC(root))=ST(RC(root))=ST(root);
    MN(LC(root))=bs[L(LC(root))].x+ST(root);
    MN(RC(root))=bs[L(RC(root))].x+ST(root);
    ST(root)=0;
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