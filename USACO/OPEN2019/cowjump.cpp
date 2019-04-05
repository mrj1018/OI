#include <cstdio>
#include <cmath>
#include <algorithm>
#define MAXN 100005
using namespace std;
typedef long long ll;
struct Point{
    ll x,y;
    Point(void):x(0),y(0){}
    Point(ll tx,ll ty):x(tx),y(ty){}
    Point(const Point& tp):x(tp.x),y(tp.y){}
};
struct Segment{
    ll x1,y1,x2,y2,len;
    int ind;
    Segment(void):x1(0),y1(0),x2(0),y2(0),len(0),ind(0){}
    Segment(ll tx1,ll ty1,ll tx2,ll ty2,ll tl,int tind):x1(tx1),y1(ty1),x2(tx2),y2(ty2),len(tl),ind(tind){}
    Segment(const Segment& ts):x1(ts.x1),y1(ts.y1),x2(ts.x2),y2(ts.y2),len(ts.len),ind(ts.ind){}
    friend bool operator<(const Segment& lhs,const Segment& rhs);
};

Segment seg[MAXN];

bool isins(int i,int j);
bool on_seg(ll x1,ll y1,ll x2,ll y2,ll x3,ll y3);
ll sgn(ll x);
//ll llabs(ll x);
ll dot(ll x1,ll y1,ll x2,ll y2);
ll cross(ll x1,ll y1,ll x2,ll y2);
int main(void){
    int n;
    int ins1=0,ins2=0,cnt1=0,cnt2=0;
    freopen("cowjump.in","r",stdin);
    freopen("cowjump.out","w",stdout);
    scanf("%d",&n);

    for (int i=1;i<=n;i++){
        ll x1,y1,x2,y2,len;
        scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
        len=llabs(x1-x2)+llabs(y1-y2);
        seg[i]=Segment(x1,y1,x2,y2,len,i);
    }
    sort(seg+1,seg+n+1);
    int sqrn=sqrt(n);
    for (int i=1;i<=sqrn;i++){
        for (int j=i+1;j<=sqrn;j++){
            if (isins(i,j)){
                ins1=i,ins2=j;
                break;
            }
        }
        if (ins1)
            break;
    }
    if (!ins1){
        for (int i=1;i<=sqrn;i++){
            for (int j=sqrn+1;j<=n;j++){
                if (isins(i,j)){
                    ins1=i,ins2=j;
                    break;
                }
            }
            if (ins1)
                break;
        }
    }
    if (!ins1){
        for (int i=sqrn+1;i<=n;i++){
            for (int j=i+1;j<=n;j++){
                if (isins(i,j)){
                    ins1=i,ins2=j;
                    break;
                }
            }
            if (ins1)
                break;
        }
    }
    if (seg[ins1].ind<seg[ins2].ind)
        swap(ins1,ins2);
    for (int i=1;i<=n;i++){
        if (i!=ins1 && isins(i,ins1)){
            cnt1++;
            if (cnt1>1){
                printf("%d\n",seg[ins1].ind);
                return 0;
            }
        }
    }
    printf("%d\n",seg[ins2].ind);
    return 0;
}

bool isins(int i,int j){
    ll c1,c2,c3,c4;
    ll x1,x2,x3,x4,y1,y2,y3,y4;
    x1=seg[i].x1,x2=seg[i].x2;
    y1=seg[i].y1,y2=seg[i].y2;
    x3=seg[j].x1,x4=seg[j].x2;
    y3=seg[j].y1,y4=seg[j].y2;

    if (min(x1,x2)>max(x3,x4) || min(x3,x4)>max(x1,x2) ||
        min(y1,y2)>max(y3,y4) || min(y3,y4)>max(y1,y2))
        return 0;
    
    c1=sgn(cross(x2-x1,y2-y1,x3-x1,y3-y1));
    c2=sgn(cross(x2-x1,y2-y1,x4-x1,y4-y1));
    c3=sgn(cross(x4-x3,y4-y3,x1-x3,y1-y3));
    c4=sgn(cross(x4-x3,y4-y3,x2-x3,y2-y3));
    if (c1*c2<0 && c3*c4<0)
        return 1;
    if (on_seg(x1,y1,x3,y3,x4,y4) || on_seg(x2,y2,x3,y3,x4,y4) ||
        on_seg(x3,y3,x1,y1,x2,y2) || on_seg(x4,y4,x1,y1,x2,y2))
        return 1;
    return 0;
}

inline bool on_seg(ll x1,ll y1,ll x2,ll y2,ll x3,ll y3){
    return (cross(x2-x1,y2-y1,x3-x1,y3-y1)==0 && dot(x2-x1,y2-y1,x3-x1,y3-y1)<0);
}

inline ll sgn(ll x){
    return (x<0)?(-1):((x)?(1):(0));
}
/*inline ll llabs(ll x){
    return (x<0)?(-x):(x);
}*/
ll dot(ll x1,ll y1,ll x2,ll y2){
    return x1*y1+x2*y2;
}
ll cross(ll x1,ll y1,ll x2,ll y2){
    return x1*y2-x2*y1;
}

bool operator<(const Segment& lhs,const Segment& rhs){
    return lhs.len>rhs.len;
}