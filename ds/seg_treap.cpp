#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <ctime>
#define MAXIOLG 25
#define FILENAME(x)\
freopen(x".in","r",stdin);\
freopen(x".out","w",stdout);
#define MAXN 50005
#define MAX4N 200005
#define MAXNLGN 800005
using namespace std;

typedef int io_t;
io_t shin[MAXIOLG];
io_t seto(void);
void ayano(io_t x,char spliter='\n');

struct Seg_node{
    int l,r,root;
    #define SL(x) ((seg[(x)]).l)
    #define SR(x) ((seg[(x)]).r)
    #define RT(x) ((seg[(x)]).root)
};

Seg_node seg[MAX4N];

struct Treap_node{
    int val,pr,lc,rc,sz,cn;
    #define X(x) ((treap[(x)]).val)
    #define PR(x) ((treap[(x)]).pr)
    #define LC(x) ((treap[(x)]).lc)
    #define RC(x) ((treap[(x)]).rc)
    #define SZ(x) ((treap[(x)]).sz)
    #define CN(x) ((treap[(x)]).cn)
};

Treap_node treap[MAXNLGN];
int pcnt=0;

void insert(int &root,int x);
void del(int &root,int x);
int newnode(int x);
void zig(int &x);
void zag(int &x);
void calcsz(int x);

int main(void){
    srand(time(0));
    return 0;
}

void insert(int &root,int x){
    if (!root){
        root=newnode(x);
        return;
    }
    if (x==X(root)){
        SZ(root)++,CN(root)++;
        return;
    }
    if (x<X(root)){
        insert(LC(root),x);
        (PR(LC(root))>PR(root))?(zig(root)):(calcsz(root));
    }
    else {
        insert(RC(root),x);
        (PR(RC(root))>PR(root))?(zag(root)):(calcsz(root));
    }
}

void del(int &root,int x){
    if (!root)
        return;
    if (x==X(root)){
        if (CN(root)>1){
            SZ(root)--,CN(root)--;
            return;
        }
        if (LC(root) && RC(root)){
            if (PR(LC(root))>PR(RC(root))){
                zig(root);
                del(RC(root),x);
            }
            else {
                zag(root);
                del(LC(root),x);
            }
            calcsz(root);
        }
        return;
    }
    if (x<X(root))
        del(LC(root),x);
    else
        del(RC(root),x);
    calcsz(root);
}

int newnode(int x){
    pcnt++;
    X(pcnt)=x,PR(pcnt)=rand();
    LC(pcnt)=RC(pcnt)=0;
    SZ(pcnt)=CN(pcnt)=1;
    return pcnt;
}

void zig(int &x){
    int y=LC(x);
    LC(x)=RC(y),RC(y)=x;
    calcsz(x),calcsz(y);
    x=y;
}
void zag(int &x){
    int y=RC(x);
    RC(x)=LC(y),LC(y)=x;
    calcsz(x),calcsz(y);
    x=y;
}
inline void calcsz(int x){
    SZ(x)=SZ(LC(x))+SZ(RC(x))+CN(x);
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
