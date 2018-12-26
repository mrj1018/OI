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

int n,m;
int ans=0;
int methods;
int w[MAXN][MAXN];

struct Method{
    int path;
    int w;
    friend bool operator<(const Method& lhs,const Method& rhs);
};
Method me[MAXMET];

void dfs(int x,int y);
void check(int x,int y,int tpath,int tw);
int kasumi(int a,int b);

int main(void){
    n=uread(),m=uread();
    if (n==1){
        uwrite(kasumi(2,m));
        return 0;
    }
    if (m==1){
        uwrite(kasumi(2,n));
        return 0;
    }
    /*if (m==2)
        swap(n,m);
    if (n==2){
        long long ans;
        ans=(long long)(kasumi(3,m-1));
        ans=ans*4%MOD;
        uwrite((int)(ans));
        return 0;
    }*/
    /*if (m==3)
        swap(n,m);
    if (n==3){
        long long ans;
        ans=(long long)(kasumi(3,m-3));
        ans=ans*112%MOD;
        uwrite((int)(ans));
        return 0;
    }*/
    if (m==4)
        swap(n,m);
    if (n==4){
        if (m==4){
            uwrite(912);
            return 0;
        }
        long long ans;
        ans=(long long)(kasumi(3,m-5));
        ans=ans*2688%MOD;
        uwrite((int)(ans));
        return 0;
    }
    //BF Search
    dfs(1,1);
    uwrite(ans);
    return 0;
}

void dfs(int x,int y){
	printf("dfs(%d,%d)\n",x,y);
    if (y==m+1){
        methods=0;
        check(1,1,0,0);
        sort(me,me+methods);
        int ok=1;
        for (int i=1;i<methods;i++){
            if (me[i].w<me[i-1].w){
                ok=0;
                break;
            }
        }

        for (int i=1;i<=n;i++){
            for (int j=1;j<=m;j++){
            	printf("%d ",w[i][j]);
	        }
			printf("\n");
		}
		printf("-- %s --\n",ok?"ok":"nok");

        if (ok){
            ans++;
            if (ans==MOD)
                ans=0;
        }
        return;
    }
    if (x==n+1){
        dfs(1,y+1);
        return;
    }
    w[x][y]=0;
    printf("w[%d][%d]=%d\n",x,y,0);
    dfs(x+1,y);
    //if (x==n || y==1 || w[x+1][y-1]){
    	w[x][y]=1;
        printf("w[%d][%d]=%d\n",x,y,1);
    	dfs(x+1,y);
//}
}

void check(int x,int y,int tpath,int tw){
    tw=(tw<<1)|(w[x][y]);
    if (x==n && y==m){
        me[methods].path=tpath;
        me[methods].w=tw;
        methods++;
        return;
    }
    //R
    if (y<m)
        check(x,y+1,((tpath<<1)|1),tw);
    
    //D
    if (x<n)
        check(x+1,y,((tpath<<1)),tw);
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

bool operator<(const Method& lhs,const Method& rhs){
    return lhs.path<rhs.path;
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
