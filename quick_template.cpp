#include <cstdio>
#include <cctype>
#define MAXIOLG 25
#define FILENAME(x) \
freopen(x".in","r",stdin); \
freopen(x".out","w",stdout);
#define MD(x) (((x)>=MOD)?((x)-=MOD):(0))
using namespace std;

typedef long long ll;
typedef long double ld;
typedef ll io_t;
io_t shin[MAXIOLG];
io_t seto(void);
void ayano(io_t x,char spliter='\n');

int main(void){
    
    return 0;
}

io_t seto(void){
    io_t x=0;
    int symbol=0;
    char ch=getchar();
    while (!isdigit(ch))
        (ch=='-')?(symbol=1):(0),
        ch=getchar();
    while (isdigit(ch))
        x=(x*10)+(ch-'0'),
        ch=getchar();
    return (symbol)?(-x):(x);
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
        shin[len++]=x-(d*10);
        x=d;
    }
    while (len--)
        putchar(shin[len]+'0');
    putchar(spliter);
}
