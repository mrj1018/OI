//SP48
#include <iostream>
#include <string>
using namespace std;
int main(void){
    string s;
    string ss;
    int n;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    while (n--){
        cin >> s;
        ss=s+s;
        int i=0,j=1,k=0;
        int status=0; //0-i,1-j
        int l=s.size();
        while (i<l && j<l){
            status=2;
            for (int k=0;k<l;k++){
                if (ss[i+k]<ss[j+k]){
                    status=0;
                    break;
                }
                if (ss[i+k]>ss[j+k]){
                    status=1;
                    break;
                }
            }
            switch (status){
                case 0:
                    j+=(k+1);
                    break;
                case 1:
                    i+=(k+1);
                    break;
                case 2:
                    status=0;
                    j+=(k+1);
                    break;
            }
        }
        cout << (status?(j+1):(i+1)) << endl;
    }
}