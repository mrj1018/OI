#include <cstdio>
#include <cstring>
using namespace std;
char title[105];

int main(void){
    int ans=0,length;
    while (scanf("%s",title)==1){
        //当读入的字符串数目为1,即还有字符串可以读入时继续循环
        length=strlen(title); //利用strlen函数获取字符串长度
        for (int i=0;i<length;i++)
            if (i!=' ' && i!='\n' && i!='\r')
                //'\n'是换行符,'\r'是回车符
                ans++;
    }
    printf("%d\n",ans);
    return 0;
}
