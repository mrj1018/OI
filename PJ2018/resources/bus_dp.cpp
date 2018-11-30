#include <cstdio>
#include <algorithm>
#define MAXN 5005
#define MAXT 5000005
#define INF 100000000
using namespace std;

int a[MAXN],temp_a[MAXN]; //a依次记录来坐车的人来的时间, temp_a用于临时存储 
int cnt[MAXT],scnt[MAXT]; //cnt[i]为时刻i来坐车的人数,scnt[i]为1~i时刻来坐车的人数 
long long wcnt[MAXT]; //用于计算等待时间 
int f[MAXT];
//f[i]表示：若首班车在i时刻发出，i+1时刻及以后所有人的最小等待时间 

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
    int m_times_2=m*2; //2m
    for (int i=0;i<n;i++){
        int lst_pos=lower_bound(a,a+n,a[i])-1-a; //找到上一个有人的时刻 
        if (a[i]>a[lst_pos]+m_times_2)
            //上一个有人的时刻在2m个单位时间之前，可以把这之后的时间向前平移 
            temp_a[i]=temp_a[lst_pos]+m_times_2;
        else
            //这两个时刻的间距不足2m
            //保持间距 
            temp_a[i]=temp_a[lst_pos]+(a[i]-a[lst_pos]);
    }
    
    //将处理后的时间复制到原位 
    for (int i=0;i<n;i++)
        a[i]=temp_a[i];
    
    max_time=0,min_time=INF;
    for (int i=0;i<n;i++){
        //更新min_time和max_time 
        if (a[i]<min_time)
           min_time=a[i];
        if (a[i]>max_time)
           max_time=a[i];
        cnt[a[i]]++; //cnt记录每一个时刻的人数 
    }
    
    int time_end=max_time+m_times_2; //time_end即为max_time+m_times_2,这是我们需要处理的最大时间 
    
    //scnt数组记录cnt数组的前缀和，即scnt[i]为1~i时刻的总人数 
    for (int i=min_time;i<=time_end;i++)
        scnt[i]=scnt[i-1]+cnt[i];
    
    //wcnt数组用于计算一个区间内的所有人需要等待的总时间 
    for (int i=min_time;i<=time_end;i++)
        wcnt[i]=cnt[i]*(time_end-i);
    for (int i=min_time;i<=time_end;i++){
        wcnt[i]+=wcnt[i-1];
    }
    
    for (int i=max_time;i>=min_time;i--){
        f[i]=INF;
        for (int j=i+m;j<i+m_times_2;j++){
            //下一班车可以在i+m~i+2m这段时间发出
            int waiting=(wcnt[j-1]-wcnt[i])-(time_end-j)*(scnt[j-1]-scnt[i]);
            //waiting计算i+1~j-1这段时间的所有人，等待到j时刻的总等待时间
            if (f[j]+waiting<f[i])
               f[i]=f[j]+waiting;
        }
    }
    
    int ans=INF;
    for (int i=min_time;i<=max_time;i++){
        int tans; //计算首班车在i时刻发出时的答案
        //tans=1~i-1的人等待首班车所需要的时间 + i+1~max_time的人等待的时间(f[i])
        //下面计算min_time~i-1这段时间的所有人，等待到i时刻的总等待时间
        tans=(wcnt[i-1]-wcnt[min_time-1])-(time_end-i)*(scnt[i-1]-scnt[min_time-1]);
        tans+=f[i];
        if (tans<ans)
            ans=tans;
    }
    printf("%d\n",ans);
    return 0;
}
