#include <cstdio>
using namespace std;
int main(void){
    char ch; //储存当前输入的字符
    int ans=0; //保存答案，即非空字符数
    ch=getchar(); //先给ch变量读入一个字符
    while (ch!=EOF){ //当前读入的字符不是EOF时继续循环
        if (ch!='\n' && ch!=' ') //如果ch不是换行符或空格,就给累加器+1
            ans++;
        ch=getchar(); //读入下一个字符
    }
    printf("%d\n",ans); //输出答案
    return 0;
}
