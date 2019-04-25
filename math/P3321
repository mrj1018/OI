#include <cstdio>
#include <cctype>
#define N 32768
#define LGN 15
#define HALF_N 16384
#define MAXN 32775
#define MAXIOLG 25
#define G 3ll
#define GINV 334845270
#define MOD 1004535809ll
#define MMOD 1004535808ll
#define FILENAME(x)\
freopen(x".in","r",stdin);\
freopen(x".out","w",stdout);
using namespace std;

typedef long long ll;
typedef ll io_t;
io_t shin[MAXIOLG];
io_t seto(void);
void ayano(io_t x,char spliter='\n');

ll a[MAXN],b[MAXN],t[MAXN];
int rev[MAXN];

ll kasumi(ll a,ll b);

namespace NTT{
    void init(void){
        rev[0]=0;
        rev[1]=HALF_N;
        for (int i=2;i<N;i++)
            rev[i]=(i&1)?((rev[i>>1]>>1)^HALF_N):(rev[i>>1]>>1);
    }
    
    void ntt(ll *a,int is_inv=0){
        for (int i=0;i<N;i++)
            t[i]=a[rev[i]];
        for (int cur=1;cur<N;cur<<=1){
            int nxt=cur<<1;
            int blks=N/nxt;
            for (int blk=0;blk<blks;blk++){
                int offset=nxt*blk;
                for (int cpi=0;cpi<cur;cpi++){
                    int cpx=offset+cpi;
                    int cpy=cpx+cur;
                    
                }
            }
        }
    }
}

int main(void){
    ll pw,m,x,s;
    pw=seto(),m=seto(),x=seto(),s=seto();
    //Find g
    //Get ord
    //NTT Kasumi
    NTT::init();
    
    //Output answer
    return 0;
}

ll kasumi(ll a,ll b){
    ll ans=1;
    while (b){
        (b&1)?(ans=ans*a%MOD):(0);
        a=a*a%MOD;
        b>>=1;
    }
    return ans;
}

io_t seto(void){
    char ch=getchar();
    io_t ans=0;
    int symbol=0;
    while (!isdigit(ch)){
        if (ch=='-')
            symbol=1;
        ch=getchar();
    }
    while (isdigit(ch)){
        ans=(ans*10)+(ch-'0');
        ch=getchar();
    }
    return (symbol)?(-ans):(ans);
}

void ayano(io_t x,char spliter){
    if (!x){
        putchar('0');
        putchar(spliter);
        return;
    }
    if (x<0){
        putchar('-');
        x=-x;
    }
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
