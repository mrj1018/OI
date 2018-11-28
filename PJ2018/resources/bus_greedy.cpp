#include <cstdio>
#include <algorithm>
#define MAXN 5005
#define MAXT 5000005
#define INF 100000000
using namespace std;

int a[MAXN]; //a依次记录来坐车的人来的时间

int main(void){
    int n,m;
    int max_time,min_time; //保存最晚和最早的到达时间 
    scanf("%d%d",&n,&m);
    if (m<=1){ //每个时刻都可以发车，不需等待 
        printf("0\n");
        return 0;
    }
    for (int i=0;i<n;i++){
        scanf("%d",a+i);
        a[i]++; //将时间向右平移一个单位，便于处理 
	}
    sort(a,a+n); //对时间进行排序
    int ans=0;
    int last_gone,last_bus;
    for (int i=0;i<n;i++){
        if (a[i]==last_bus){
            last_gone=i;
            continue;
        }
        if (a[i]>=last_bus+m){
            for (int j=last_gone+1;j<n;j++){
                
                ans+=a[i]-a[j];
            }
            last_gone=i;
            last_bus=a[i];
        }
    }
    printf("%d\n",ans);
    return 0;
}
