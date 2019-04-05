#include <cstdio>
#include <cmath>
#define MAXN 200005
using namespace std;
double a[MAXN];
int main(void){
    int test_datas;
    scanf("%d",&test_datas);
    for (int test_datai=1;test_datai<=test_datas;test_datai++){
        printf("Case #%d:\n",test_datai);
        int n,m;
        scanf("%d%d",&n,&m);
        if (n<=1000 && m<=1000){
            for (int i=1;i<=n;i++)
                scanf("%lf",a+i);
            while (m--){
                int op;
                scanf("%d",&op);
                if (op==1){
                    //op==1
                    int l,r;
                    double v;
                    scanf("%d%d%lf",&l,&r,&v);
                    for (int i=l;i<=r;i++)
                        a[i]+=v;
                }
                else {
                    //op==2
                    double ans=0;
                    int l,r;
                    scanf("%d%d",&l,&r);
                    for (int i=l;i<=r;i++)
                        ans+=cos(a[i]);
                    printf("%.3f\n",ans);
                }
            }
        }
        else {
            for (int i=1;i<=n;i++)
                scanf("%lf",a+i);
            a[0]=0;
            for (int i=n;i;i--)
                a[i]-=a[i-1];
            int opi=0;
            for (opi=0;opi<m;opi++){
                int op;
                scanf("%d",&op);
                if (op==2)
                    break;
                int l,r;
                double v;
                scanf("%d%d%lf",&l,&r,&v);
                a[l]+=v,a[r+1]-=v;
            }
            a[0]=0;
            for (int i=1;i<=n;i++)
                a[i]+=a[i-1];
            for (int i=1;i<=n;i++)
                a[i]=cos(a[i])+a[i-1];

            {
                //Deal with the rest operation
                int l,r;
                scanf("%d%d",&l,&r);
                printf("%.3f\n",a[r]-a[l-1]);
                opi++;
            }

            for (;opi<m;opi++){
                int op,l,r;
                scanf("%d%d%d",&op,&l,&r);
                printf("%.3f\n",a[r]-a[l-1]);
            }
        }
    }
    return 0;
}