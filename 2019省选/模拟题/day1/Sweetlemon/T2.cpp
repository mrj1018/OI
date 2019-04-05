#include <cstdio>
#include <algorithm>
using namespace std;
int a[505];
int main(void){
    int test_datas;
    scanf("%d",&test_datas);
    for (int test_datai=1;test_datai<=test_datas;test_datai++){
        printf("Case #%d: ",test_datai);
        int n,ans=0;
        scanf("%d",&n);
        for (int i=1;i<=n;i++)
            scanf("%d",a+i);
        sort(a+1,a+n+1);
        do {
            int p=0;
            for (int i=1;i<=n;i++){
                int q=a[i];
                (p<q)?(p=q-p):(p=p-q);
            }
            (p>ans)?(ans=p):(0);
        }
        while (next_permutation(a+1,a+n+1));
        printf("%d\n",ans);
    }
    return 0;
}