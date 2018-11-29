#include <cstdio>
#include <algorithm>
#define MAXN 5005
#define MAXT 5000005
#define INF 100000000
using namespace std;

int a[MAXN]; //a依次记录来坐车的人来的时间

int main(void){
    int n,m;
    scanf("%d%d",&n,&m);
    if (m<=1){ //每个时刻都可以发车，不需等待 
        printf("0\n");
        return 0;
    }
    for (int i=0;i<n;i++)
        scanf("%d",a+i);
    sort(a,a+n); //对时间进行排序
    int ans=0;
    int last_bus_time=a[0]; //记录当前的最后一班车的时间 
    for (int i=0;i<n;i++){
    	if (a[i]>=last_bus_time+m) //再发一班车以搭载第i个人 
    		last_bus_time=a[i];
    	if (a[i]>last_bus_time)
    		last_bus_time+=m;
        ans+=(last_bus_time-a[i]); //将第i个人等待的时间累加入答案中 
    }
    printf("%d\n",ans);
    return 0;
}
