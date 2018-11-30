#include <cstdio>
#include <algorithm>
#define MAXN 505
#define MAXT 50005
#define INF 100000000
using namespace std;

int a[MAXN],temp_a[MAXN]; //a依次记录来坐车的人来的时间, temp_a用于将时间进行压缩 
int f[MAXT][MAXN]; //f用于记录算出的答案，避免重复计算 
int max_time; //max_time记录最大时间 
int n,m;

int dfs(int now_time,int last_sent);

int main(void){
    scanf("%d%d",&n,&m);
    if (m<=1){ //每个时刻都可以发车，不需等待 
        printf("0\n");
        return 0;
    }
    for (int i=1;i<=n;i++)
        scanf("%d",a+i);
    sort(a+1,a+1+n); //对时间进行排序
    
    int m_times_2=m*2; //2m
    for (int i=1;i<=n;i++){
        int lst_pos=lower_bound(a+1,a+n+1,a[i])-1-a; //找到上一个有人的时刻 
        if (a[i]>a[lst_pos]+m_times_2)
            //上一个有人的时刻在2m个单位时间之前，可以把这之后的时间向前平移 
            temp_a[i]=temp_a[lst_pos]+m_times_2;
        else
            //这两个时刻的间距不足2m
            //保持间距 
            temp_a[i]=temp_a[lst_pos]+(a[i]-a[lst_pos]);
    }
    
    //将处理后的时间复制到原位 
    for (int i=1;i<=n;i++)
        a[i]=temp_a[i];
    
    max_time=a[n]+m_times_2;
    for (int i=a[1];i<=max_time;i++)
        for (int j=0;j<=n;j++)
            f[i][j]=INF; //把f数组初始化为INF, 表示没有计算过 
    
    for (int i=0;i<m;i++)
        dfs(a[1]+i,0); //枚举首班车时间
    int ans=INF;
	for (int i=0;i<m;i++) //枚举首班车时间
	    if (f[a[1]+i][0]<ans)
	        ans=f[a[1]+i][0];
    printf("%d\n",ans);
    return 0;
}

int dfs(int now_time,int last_sent){
	//在now_time时刻发车, 计算last_sent+1~n这些人的最短等待时间之和 
    if (f[now_time][last_sent]<INF) //已经求解过一次
        return f[now_time][last_sent]; //直接返回 
    //要求在now_time时刻发车
    int now_ans=0,now_sent=last_sent; //now_ans表示等待这趟车的人的等待时间之和 
    //把等待这一趟车的人的等待时间累加入答案中
    while (now_sent<n && a[now_sent+1]<=now_time){
    	//表示now_sent+1这个人可以乘坐这趟车 
        now_sent++;
        now_ans+=(now_time-a[now_sent]);
    }
    if (now_sent==n){
    	//说明所有的人都已经有车可乘 
        f[now_time][last_sent]=now_ans; //将答案存储起来 
        return now_ans;
    }
    //枚举下一班车的时间
    int m_times_2=m*2;
    int return_ans=INF; //存储将要返回的最小答案，即last_sent+1到n这些人的最小等待时间 
    for (int i=m;i<m_times_2;i++){
    	//相邻两班车的时间间隔不小于m,不大于2m 
        int tans=dfs(now_time+i,now_sent); //tans表示后面的人(now_sent+1~n)等车的最小时间 
        if (tans+now_ans<return_ans)
            return_ans=tans+now_ans;
    }
    f[now_time][last_sent]=return_ans; //记录答案
    return return_ans;
}
