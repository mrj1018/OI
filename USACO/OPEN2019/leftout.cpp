#include <cstdio>
#define MAXN 1005
using namespace std;
int grid[MAXN][MAXN];
int get_ch(void);
int main(void){
    int n;
    int x1=0,y1=0,x2=0,y2=0,ok1=0,ok2=0;
    freopen("leftout.in","r",stdin);
    freopen("leftout.out","w",stdout);
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            grid[i][j]=get_ch();
    
    for (int i=1;i<=n;i++)
        if (grid[n][i])
            for (int j=1;j<=n;j++)
                grid[j][i]=(grid[j][i])?(0):(1);
    
    for (int i=1;i<=n;i++){
        int num_0=0,num_1=0;
        for (int j=1;j<=n;j++)
            (grid[i][j])?(num_1++):(num_0++);
        if (num_1==1){
            if (ok1){
                ok1=-1;
                break;
            }
            ok1=1;
            for (int j=1;j<=n;j++){
                if (grid[i][j]){
                    x1=i,y1=j;
                    break;
                }
            }
        }
        if (num_1>1){
            if (num_0>1 || (num_0==1 && ok1)){
                ok1=-1;
                break;
            }
            for (int j=1;j<=n;j++){
                grid[i][j]=(grid[i][j])?(0):(1);
                if (grid[i][j])
                    x1=i,y1=j,ok1=1;
            }
        }
    }

    for (int i=1;i<=n;i++)
        if (grid[1][i])
            for (int j=1;j<=n;j++)
                grid[j][i]=(grid[j][i])?(0):(1);
    
    for (int i=1;i<=n;i++){
        int num_0=0,num_1=0;
        for (int j=1;j<=n;j++)
            (grid[i][j])?(num_1++):(num_0++);
        if (num_1==1){
            if (ok2){
                ok2=-1;
                break;
            }
            ok2=1;
            for (int j=1;j<=n;j++){
                if (grid[i][j]){
                    x2=i,y2=j;
                    break;
                }
            }
        }
        if (num_1>1){
            if (num_0>1 || (num_0==1 && ok2)){
                ok2=-1;
                break;
            }
            for (int j=1;j<=n;j++){
                grid[i][j]=(grid[i][j])?(0):(1);
                if (grid[i][j])
                    x2=i,y2=j,ok2=1;
            }
        }
    }
    /*for (int i=1;i<=n;i++){
        int num_0=0,num_1=0;
        for (int j=1;j<=n;j++)
            (grid[j][i])?(num_1++):(num_0++);
        if (num_1>num_0){
            for (int j=1;j<=n;j++)
                grid[j][i]=(grid[j][i])?(0):(1);
        }
    }
    for (int i=1;i<=n;i++){
        int num_0=0,num_1=0;
        for (int j=1;j<=n;j++)
            (grid[i][j])?(num_1++):(num_0++);
        if (num_1>num_0){
            for (int j=1;j<=n;j++)
                grid[i][j]=(grid[i][j])?(0):(1);
        }
    }

    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++)
            putchar((grid[i][j])?('R'):('L'));
        putchar('\n');
    }
    printf("%d:(%d,%d), %d:(%d,%d)\n",ok1,x1,y1,ok2,x2,y2);*/
    
    if (ok1==0 || ok2==0 || (ok1+ok2==-2))
        printf("-1\n");
    else {
        if (ok1!=-1)
            printf("%d %d\n",x1,y1);
        else if (ok2!=-1)
            printf("%d %d\n",x2,y2);
    }
    return 0;
}

int get_ch(void){
    char ch;
    ch=getchar();
    while (ch!='L' && ch!='R')
        ch=getchar();
    return (ch=='L')?(0):(1);
}