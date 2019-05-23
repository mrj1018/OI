//Luogu P5381
#include <cstdio>
#include <cctype>
#include <algorithm>
#define MAXIOLG 25
#define FILENAME(x)\
freopen(x".in","r",stdin);\
freopen(x".out","w",stdout);
#define LOWBIT(x) ((x)&(-(x)))
#define MAXN 500005
using namespace std;

typedef ll io_t;
io_t shin[MAXIOLG];
io_t seto(void);
void ayano(io_t x,char spliter='\n');

typedef long long ll;

ll a[MAXN],b[MAXN];
double xvalue[MAXN];
ll valn[MAXN];
ll d2n[MAXN];
ll tarr_n[MAXN];
double tarr_r[MAXN];

ll query_n(int x);
void add_n(int pos,ll x);
int get_x(ll rank);
double query_r(int x);
void add_r(int pos,double x);

int main(void){
    int n;
    double ans=0;
    n=seto();
    ll cons=0; //a=0
    int values=0; //a!=0 count
    for (int i=1;i<=n;i++){
        a[i]=seto(),b[i]=seto();
        (a[i]<0)?(a[i]=-a[i],b[i]=-b[i]):(0);
        if (a[i]==0){
            (b[i]<0)?(b[i]=-b[i]):(0);
            valn[i]=-1;
            continue;
        }
        values++;
        d2n[values]=xvalue[i]=(double)(-b)/a;
    }
    sort(d2n+1,d2n+values+1);
    ll nowcnt=0; //Now abs count
    for (int i=1;i<=n;i++){
        if (!a[i]){
            cons+=b[i];
            ans+=b[i];
            printf("%.6f\n",ans);
            continue;
        }
        double td=xvalue[i];
        int pos=lower_bound(d2n+1,d2n+values+1,td)-d2n;
        valn[i]=pos;
        add_n(pos,a[i]);
        add_r(pos,td*a[i]);
        nowcnt+=a[i];
        //Find mid
        ll mid_rank=(nowcnt>>1)+1;
        ll mid_i=get_x(mid_rank);
        double mid_x=xvalue[mid_i];
        
    }
    return 0;
}

io_t seto(void){
    io_t ans=0;
    int symbol=0;
    char ch=getchar();
    while (!isdigit(ch))
        (ch=='-')?(symbol=1):(0),ch=getchar();
    while (isdigit(ch))
        (ans=ans*10+(ch-'0')),ch=getchar();
    return (symbol)?(-ans):(ans);
}

void ayano(io_t x,char spliter){
    if (!x){
        putchar('0'),putchar(spliter);
        return;
    }
    if (x<0)
        putchar('-'),x=-x;
    int len=0;
    while (x){
        io_t d=x/10;
        shin[len++]=x-d*10;
        x=d;
    }
    while (len){
        len--;
        putchar(shin[len]+'0');
    }
    putchar(spliter);
}
