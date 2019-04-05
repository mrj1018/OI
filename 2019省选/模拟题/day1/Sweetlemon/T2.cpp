#include <cstdio>
#define MAXN 505
using namespace std;
int a[MAXN];
int main(void){
    int test_datas;
    scanf("%d",&test_datas);
    for (int test_datai=1;test_datai<=test_datas;test_datai++){
        printf("Case #%d: ",test_datai);
        int n;
        scanf("%d",&n);
        for (int i=1;i<=n;i++)
            scanf("%d",a+i);
        
    }
    return 0;
}