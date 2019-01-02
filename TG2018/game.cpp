#include <cstdio>
#include <cctype>
#include <algorithm>
#define MAXIOLG 25
#define MAXN 1005
#define MAXMET 100005
#define MOD 1000000007
using namespace std;

typedef long long ll;
int iotemp[MAXIOLG];
typedef int io_t;
io_t uread(void);
void uwrite(io_t x,char spliter='\n');

int kasumi(int a,int b);

int main(void){
    int n,m;
    n=uread(),m=uread();
    if (n==1){
        uwrite(kasumi(2,m));
        return 0;
    }
    if (m==1){
        uwrite(kasumi(2,n));
        return 0;
    }
    if (m==2)
        swap(n,m);
    if (n==2){
        long long ans;
        ans=(long long)(kasumi(3,m-1));
        ans=ans*4%MOD;
        uwrite((int)(ans));
        return 0;
    }
    if (m==3)
        swap(n,m);
    if (n==3){
        long long ans;
        ans=(long long)(kasumi(3,m-3));
        ans=ans*112%MOD;
        uwrite((int)(ans));
        return 0;
    }
    if (m==4)
        swap(n,m);
    if (n==4){
        if (m==4){
            uwrite(912);
            return 0;
        }
        long long ans;
        ans=(long long)(kasumi(3,m-4));
        ans=ans*896%MOD;
        uwrite((int)(ans));
        return 0;
    }
    if (m==5)
    	swap(n,m);
    if (n==5){
    	if (m==5){
    		uwrite(7136);
    		return 0;
        }
        long long ans;
        ans=(long long)(kasumi(3,m-5));
        ans=ans*7104%MOD;  //7136-2**5
        uwrite((int)(ans));
        return 0;
    }
    if (m==6)
    	swap(n,m);
    if (n==6){
    	if (m==6){
    		uwrite(56768);
    		return 0;
        }
        long long ans;
        ans=(long long)(kasumi(3,m-6));
        ans=ans*56704%MOD;  //56768-2**6
        uwrite((int)(ans));
        return 0;
    }
    if (m==7)
    	swap(n,m);
    if (n==7){
    	if (m==7){
    		uwrite(453504);
    		return 0;
        }
        long long ans;
        ans=(long long)(kasumi(3,m-7));
        ans=ans*453376%MOD;  //453504-2**7
        uwrite((int)(ans));
        return 0;
    }
    if (m==8)
    	swap(n,m);
    if (n==8){
    	if (m==8){
    		uwrite(3626752);
    		return 0;
        }
        long long ans;
        ans=(long long)(kasumi(3,m-8));
        ans=ans*3626496%MOD;  //3626752-2**8
        uwrite((int)(ans));
        return 0;
    }
    return 0;
}

int kasumi(int a,int b){
    ll ans=1;
    while (b){
        if (b&1)
            ans=((ll)(a)*ans)%MOD;
        a=(ll)(a)*(ll)(a)%MOD;
        b>>=1;
    }
    return int(ans);
}

io_t uread(void){
    io_t ans=0;
    char ch;
    int symbol=0;
    ch=getchar();
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

void uwrite(io_t x,char spliter){
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
        iotemp[len++]=x%10;
        x/=10;
    }
    while (len){
        len--;
        putchar(iotemp[len]+'0');
    }
    putchar(spliter);
}
