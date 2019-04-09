#include <cstdio>
#include <cmath>
#define MAXN 200005
#define MAX4N 800005
#define ROOT 1
using namespace std;
struct Node{
    int l,r;
    double sins,coss,addv;
    Node(void):l(0),r(0),sins(0.0),coss(0.0),addv(0.0){}
    Node(int tl,int tr,double ts,double tc,double ta):l(tl),r(tr),sins(ts),coss(tc),addv(ta){}
    Node(const Node& tn):l(tn.l),r(tn.r),sins(tn.sins),coss(tn.coss),addv(tn.addv){}
    #define L(x) ((stree[(x)]).l)
    #define R(x) ((stree[(x)]).r)
    #define SS(x) ((stree[(x)]).sins)
    #define CS(x) ((stree[(x)]).coss)
    #define ADD(x) ((stree[(x)]).addv)
    #define LC(x) (((x)<<1))
    #define RC(x) (((x)<<1)^1)
};
double a[MAXN];
Node stree[MAX4N];

//Segment Tree
void build_tree(int root,int l,int r);
void pushdown(int root);
void update(int root,int l,int r,double x);
double query(int root,int l,int r);

int main(void){
    int test_datas;
    scanf("%d",&test_datas);
    for (int test_datai=1;test_datai<=test_datas;test_datai++){
        printf("Case #%d:\n",test_datai);
        int n,m;
        scanf("%d%d",&n,&m);
        for (int i=1;i<=n;i++)
            scanf("%lf",a+i);
        build_tree(ROOT,1,n);
        while (m--){
            int op;
            scanf("%d",&op);
            if (op==1){
                //op==1
                int l,r;
                double v;
                scanf("%d%d%lf",&l,&r,&v);
                update(ROOT,l,r,v);
            }
            else {
                //op==2
                int l,r;
                scanf("%d%d",&l,&r);
                printf("%.3f\n",query(ROOT,l,r));
            }
        }
    }
    return 0;
}

void build_tree(int root,int l,int r){
    stree[root].l=l,stree[root].r=r;
    stree[root].addv=0.0;
    if (l==r){
        stree[root].sins=sin(a[l]);
        stree[root].coss=cos(a[l]);
        return;
    }
    int mid=((l+r)>>1);
    build_tree(LC(root),l,mid);
    build_tree(RC(root),mid+1,r);
    stree[root].sins=stree[LC(root)].sins+stree[RC(root)].sins;
    stree[root].coss=stree[LC(root)].coss+stree[RC(root)].coss;
}

void pushdown(int root){
    if (L(root)==R(root))
        ADD(root)=0.0;
    if (ADD(root)==0.0)
        return;
    double tsin,tcos,theta;
    theta=ADD(root);
    ADD(root)=0.0;
    tsin=sin(theta),tcos=cos(theta);
    //sin(x+y)=sin(x)cos(y)+cos(x)sin(y)
    //cos(x+y)=cos(x)cos(y)-sin(x)sin(y)
    double lcs,lcc,rcs,rcc;
    lcs=SS(LC(root)),lcc=CS(LC(root));
    SS(LC(root))=lcs*tcos+lcc*tsin;
    CS(LC(root))=lcc*tcos-lcs*tsin;
    rcs=SS(RC(root)),rcc=CS(RC(root));
    SS(RC(root))=rcs*tcos+rcc*tsin;
    CS(RC(root))=rcc*tcos-rcs*tsin;
    ADD(LC(root))+=theta;
    ADD(RC(root))+=theta;
}

void update(int root,int l,int r,double x){
    if (l<=L(root) && r>=R(root)){
        //sin(x+y)=sin(x)cos(y)+cos(x)sin(y)
        //cos(x+y)=cos(x)cos(y)-sin(x)sin(y)
        double tsin,tcos,s,c;
        tsin=sin(x),tcos=cos(x);
        s=SS(root),c=CS(root);
        SS(root)=s*tcos+c*tsin;
        CS(root)=c*tcos-s*tsin;
        ADD(root)=x;
        return;
    }
    if (l>R(root) || r<L(root))
        return;
    pushdown(root);
    int mid=(L(root)+R(root))>>1;
    (l<=mid)?((update(LC(root),l,r,x)),0):(0);
    (r> mid)?((update(RC(root),l,r,x)),0):(0);
    SS(root)=SS(LC(root))+SS(RC(root));
    CS(root)=CS(LC(root))+CS(RC(root));
}

double query(int root,int l,int r){
    if (l<=L(root) && r>=R(root))
        return CS(root);
    if (l>R(root) || r<L(root))
        return 0.0;
    pushdown(root);
    int mid=(L(root)+R(root))>>1;
    double ans=0.0;
    (l<=mid)?(ans+=query(LC(root),l,r)):(0);
    (r> mid)?(ans+=query(RC(root),l,r)):(0);
    return ans;
}
