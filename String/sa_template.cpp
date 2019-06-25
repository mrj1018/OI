#include <cstdio>
#include <cctype>
#include <algorithm>
#define MAXIOLG 25
#define FILENAME(x)\
freopen(x".in","r",stdin);\
freopen(x".out","w",stdout);
#define MAXN 1000005
using namespace std;

typedef int io_t;
io_t shin[MAXIOLG];
io_t seto(void);
int seto_str(void);
void ayano(io_t x,char spliter='\n');

char str[MAXN];
int sa[MAXN],rk[MAXN],tp[MAXN],bucket[MAXN];

void suffix_sort(int n);
void bucket_sort(int n,int m);

int main(void){
    int n=seto_str();
    suffix_sort(n);
    
    return 0;
}

void suffix_sort(int n){
    int m='z'-'a'+1;
    for (int i=1;i<=n;i++)
        rk[i]=str[i]-'a'+1,tp[i]=i;
    bucket_sort(n,m);
    for (int p=0,w=1;p<n;m=p,w<<=1){
        p=0;
        for (int i=n-w+1;i<=n;i++)
            tp[++p]=i;
        for (int i=1;i<=n;i++)
            (sa[i]>w)?(tp[++p]=sa[i]-w):(0);
        bucket_sort(n,m);
        swap(rk,tp);
        rk[sa[1]]=1;
        p=1;
        for (int i=2;i<=n;i++)
            rk[sa[i]]=(tp[sa[i]]==tp[sa[i-1]] && tp[sa[i]+w]==tp[sa[i-1]+w])?
            (p):(++p);
    }
}

void bucket_sort(int n,int m){
    //rk: id->val, bucket: val->rk
    //tp, sa: rk->id
    for (int i=0;i<=m;i++)
        bucket[i]=0;
    for (int i=1;i<=n;i++)
        bucket[rk[i]]++;
    for (int i=1;i<=m;i++)
        bucket[i]+=bucket[i-1];
    for (int i=n;i;i--)
        sa[bucket[rk[tp[i]]]--]=tp[i];
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

int seto_str(void){
    int len=1;
    char ch=getchar();
    while (!isalnum(ch))
        ch=getchar();
    while (isalnum(ch)){
        str[len++]=ch;
        ch=getchar();
    }
    str[len]='\0';
    return len-1;
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
