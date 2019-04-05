#include <cstdio>
#include <cctype>
#include <algorithm>
#include <functional>
#define MAXN 500005
using namespace std;
int w[MAXN];
int sw[MAXN]; //The weight if i issues are passed
int forw[MAXN],againstw[MAXN]; //The weight of the people who is for or against the issue
int f[MAXN]; //Dp array
int uread(void);
int main(void){
    int n,m;
    n=uread(),m=uread();
    for (int i=1;i<=n;i++)
        w[i]=uread();
    for (int i=1;i<=n;i++){
        int x,y;
        x=uread(),y=uread();
        switch (x){
            case 1:
                forw[y]+=w[i];
                break;
            case 2:
                againstw[y]+=w[i];
                break;
            case 3:
                //sw[y:m+1]+=w[i]
                sw[y]+=w[i];
                //sw[m+1]-=w[i]; // Not needed
                break;
            case 4:
                //sw[0:y+1]+=w[i]
                sw[0]+=w[i];
                sw[y+1]-=w[i];
                break;
        }
    }
    for (int i=1;i<=m;i++)
        sw[i]+=sw[i-1];    
    for (int i=1;i<=m;i++){
        f[i]=f[i-1]+forw[i];
        for (int j=i-1;j;j--)
            f[j]=max(f[j]+againstw[j],f[j-1]+forw[i]);
        f[0]+=againstw[i];
    }
    printf("%d %d\n",f[0],f[1]);
    printf("%d %d\n",sw[0],sw[1]);
    int ans=sw[0]+f[0];
    for (int i=1;i<=m;i++)
        ans=max(ans,f[i]+sw[i]);
    
    printf("%d\n",ans);
    return 0;
}

int uread(void){
    int ans=0;
    int symbol=0;
    char ch;
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