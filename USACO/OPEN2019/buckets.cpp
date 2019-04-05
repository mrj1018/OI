#include <cstdio>
#include <queue>
#define n 10
#define MAXN 55
#define INF 19260817
using namespace std;
struct Pos{
    int x,y;
    Pos(void):x(0),y(0){}
    Pos(int tx,int ty):x(tx),y(ty){}
    Pos(const Pos& tp):x(tp.x),y(tp.y){}
};
int grid[MAXN][MAXN];
int dis[MAXN][MAXN];
const int movex[]={0,0,1,-1};
const int movey[]={1,-1,0,0};
queue<Pos> q;
int get_ch(void);

int main(void){
    freopen("buckets.in","r",stdin);
    freopen("buckets.out","w",stdout);
    int sx,sy,tx,ty;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            int tv=get_ch();
            grid[i][j]=tv;
            dis[i][j]=INF;
            if (tv==2)
                sx=i,sy=j;
            if (tv==3)
                tx=i,ty=j;
        }
    }
    q.push(Pos(sx,sy));
    dis[sx][sy]=0;
    while (!q.empty()){
        int nx,ny,nd;
        int ok=0;
        Pos tp=q.front();
        q.pop();
        nx=tp.x, ny=tp.y;
        nd=dis[nx][ny];
        for (int i=0;i<4;i++){
            int tarx,tary;
            tarx=nx+movex[i];
            tary=ny+movey[i];
            if (grid[tarx][tary] && dis[tarx][tary]>nd+1){
                dis[tarx][tary]=nd+1;
                if (tarx==tx && tary==ty){
                    ok=1;
                    break;
                }
                q.push(Pos(tarx,tary));
            }
        }
        if (ok)
            break;
    }
    printf("%d\n",dis[tx][ty]-1);
    return 0;
}

int get_ch(void){
    char ch;
    ch=getchar();
    while (ch!='.' && ch!='R' && ch!='B' && ch!='L')
        ch=getchar();
    switch (ch){
        case '.':
            return 1;
        case 'B':
            return 2;
        case 'L':
            return 3;
        case 'R':
            return 0;
    }
    return -1;
}