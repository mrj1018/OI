#include <cstdio>
#define MAXN 100005
#define MAXLG 19
#define LOWBIT(x) ((x)&(-(x)))
using namespace std;
int n;
int pow2[MAXLG];
int lg2[MAXN];
int a[MAXN];
int st[MAXLG][MAXN];
void rmq_init(void);
int rmq_query(int a,int b);
int main(void){
    scanf("%d",&n);
    lg2[1]=0,pow2[0]=1; //log_2(1)=0,2^0=1
    for (int i=2;i<=n;i++){
        if (LOWBIT(i)==i){
            lg2[i]=lg2[i-1]+1;
            pow2[lg2[i]]=i;
        }
        else
            lg2[i]=lg2[i-1];
    }
    for (int i=1;i<=n;i++)
        scanf("%d",a+i);
    rmq_init();
    return 0;
}

void rmq_init(void){
    //[i,i+2^k) - length is 2^k
    int lgn=lg2[n];
    for (int i=1;i<n;i++)
        st[0][i]=i;
    for (int k=1;k<=lgn;k++){
        int pw2=pow2[k];
        int pwk1=pow2[k-1];
        int ub=n-pw2+1;
        for (int i=1;i<=ub;i++){
            //[i,i+pwk1),[i+pwk1,i+pw2)
            int inda,indb;
            inda=st[k-1][i];
            indb=st[k-1][i+pwk1];
            st[k][i]=(a[inda]<a[indb])?(inda):(indb);
        }
    }
}

int rmq_query(int a,int b){
    //[a,b)
    int l=b-a;
    //Choose k that 2^(k+1)>=l
}
