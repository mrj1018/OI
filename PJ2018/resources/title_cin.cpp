#include <iostream>
#include <cstring>
using namespace std;
char title[105];

int main(void){
    int ans=0,length;
    while (cin >> title){ //当还有字符串可读的时候循环会进行 
        length=strlen(title);
        for (int i=0;i<length;i++)
            if (i!=' ' && i!='\n' && i!='\r')
                ans++;
    }
   cout << ans << endl;
    return 0;
}
