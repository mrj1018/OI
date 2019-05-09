//Splay P3369 Normal BST
#include <cstdio>
#include <cctype>
#define MAXIOLG 25
#define FILENAME(x)\
freopen(x".in","r",stdin);\
freopen(x".out","w",stdout);
#define MAXN 100005
#define INF 19260817
using namespace std;

typedef int io_t;
io_t shin[MAXIOLG];
io_t seto(void);
void ayano(io_t x,char spliter='\n');

struct Node{
    int fa,cnt,sz,val;
    int ch[2];
    #define FA(x) ((tr[(x)]).fa)
    #define LC(x) (((tr[(x)]).ch)[0])
    #define RC(x) (((tr[(x)]).ch)[1])
    #define CH(x,t) (((tr[(x)]).ch)[(t)])
    #define CN(x) ((tr[(x)]).cnt)
    #define SZ(x) ((tr[(x)]).sz)
    #define X(x) ((tr[(x)]).val)
    #define ID(x) ((x)==CH(FA(x),1))
};

Node tr[MAXN];
int troot,pcnt;

void build_tree(void);
void insert(int x);
void del(int x);
void find(int x);
int getrank(int x);
int getx(int rank);
int getpre(int x);
int getpost(int x);
void splay(int x,int pos=0);
void rotate(int x);
void calcsz(int x);
int newnode(int x);
void delnode(int x);

int main(void){
    int q=seto();
    build_tree();
    while (q--){
        int op,x;
        op=seto(),x=seto();
        switch (op){
            case 1:
                insert(x);
                break;
            case 2:
                del(x);
                break;
            case 3:
                ayano(getrank(x));
                break;
            case 4:
                ayano(getx(x));
                break;
            case 5:
                ayano(getpre(x));
                break;
            case 6:
                ayano(getpost(x));
                break;
        }
    }
    return 0;
}

inline void build_tree(void){
    pcnt=troot=0;
    delnode(0);
}

void insert(int x){
    if (!troot){
        troot=newnode(x);
        return;
    }
    int root=troot;
    while (1){
        if (x==X(root)){
            CN(root)++,SZ(root)++;
            splay(root);
            break;
        }
        int st=(x>X(root));
        int t=CH(root,st);
        if (t){
            root=t;
            continue;
        }
        t=CH(root,st)=newnode(x);
        FA(t)=root;
        splay(t);
        break;
    }
}

void del(int x){
    if (!troot)
        return;
    find(x);
    if (X(troot)!=x)
        return;
    if (CN(troot)>1){
        CN(troot)--,SZ(troot)--;
        return;
    }
    if (!(LC(troot) || RC(troot))){
        delnode(troot);
        troot=0;
        return;
    }
    if (LC(troot) && RC(troot)){
        //get pre
        int pre,nxt=LC(troot);
        while (nxt)
            pre=nxt,nxt=RC(nxt);
        splay(pre,LC(troot));
        FA(RC(troot))=pre,CH(pre,1)=RC(troot);
        FA(pre)=0;
        delnode(troot);
        troot=pre;
        calcsz(pre);
    }
    else {
        int t=(LC(troot) | RC(troot));
        FA(t)=0;
        delnode(troot);
        troot=t;
    }
}

void find(int x){
    if (!troot)
        return;
    int root=troot;
    while (1){
        if (x==X(root)){
            splay(root);
            break;
        }
        int st=(x>X(root));
        int t=CH(root,st);
        if (t){
            root=t;
            continue;
        }
        splay(root);
        break;
    }
}

int getrank(int x){
    find(x);
    return SZ(LC(troot))+1;
}

int getx(int rank){
    int root=troot;
    while (root){
        if (rank<=SZ(LC(root))){
            root=LC(root);
            continue;
        }
        rank-=SZ(LC(root));
        if (rank>CN(root)){
            rank-=CN(root),root=RC(root);
            continue;
        }
        return X(root);
    }
    return INF;
}

int getpre(int x){
    find(x);
    if (X(troot)<x)
        return X(troot);
    int root=LC(troot);
    int ans=-INF;
    while (root)
        ans=X(root),root=RC(root);
    return ans;
}

int getpost(int x){
    find(x);
    if (X(troot)>x)
        return X(troot);
    int root=RC(troot);
    int ans=INF;
    while (root)
        ans=X(root),root=LC(root);
    return ans;
}

void splay(int x,int pos){
    int tarp=FA(pos);
    int p=FA(x);
    while (p && p!=tarp){
        int pp=FA(p);
        if (pp && pp!=tarp)
            rotate((ID(x)==ID(p))?(p):(x));
        rotate(x);
        p=FA(x);
    }
    (p)?(0):(troot=x);
}

void rotate(int x){
    int y=FA(x);
    if (!(x && y))
        return;
    int z=FA(y);
    int t;
    int idx=ID(x),idy=ID(y);
    t=CH(y,idx)=CH(x,idx^1);
    (t)?(FA(t)=y):(0);
    CH(x,idx^1)=y;
    FA(y)=x;
    FA(x)=z;
    (z)?(CH(z,idy)=x):(0);
    calcsz(y),calcsz(x);
}

inline void calcsz(int x){
    SZ(x)=SZ(LC(x))+SZ(RC(x))+CN(x);
}
inline int newnode(int x){
    pcnt++;
    X(pcnt)=x,FA(pcnt)=LC(pcnt)=RC(pcnt)=0;
    CN(pcnt)=SZ(pcnt)=1;
    return pcnt;
}
inline void delnode(int x){
    X(x)=FA(x)=LC(x)=RC(x)=CN(x)=SZ(x)=0;
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
