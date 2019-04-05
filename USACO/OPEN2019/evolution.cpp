#include <iostream>
#include <cstdio>
#include <map>
#include <string>
#include <bitset>
#define MAXN 27
#define MAXT 705
using namespace std;
map<string,int> mp;
bitset<MAXN> bs[MAXT];
int main(void){
    int n;
    int skills=0;
    freopen("evolution.in","r",stdin);
    freopen("evolution.out","w",stdout);
    cin >> n;
    for (int i=1;i<=n;i++){
        int k;
        cin >> k;
        while (k--){
            string tsk;
            cin >> tsk;
            if (mp.count(tsk))
                bs[mp[tsk]].set(i);
            else {
                mp[tsk]=(++skills);
                bs[mp[tsk]].set(i);
            }
        }
    }
    for (int i=1;i<=skills;i++){
        bitset<MAXN> & tbs=bs[i];
        for (int j=1;j<i;j++){
            bitset<MAXN> calc=bs[j]&tbs;
            if (calc.any() && calc!=tbs && calc!=bs[j]){
                cout << "no\n";
                return 0;
            }
        }
        for (int j=i+1;j<=skills;j++){
            bitset<MAXN> calc=bs[j]&tbs;
            if (calc.any() && calc!=tbs && calc!=bs[j]){
                cout << "no\n";
                return 0;
            }
        }
    }
    cout << "yes\n";
    return 0;
}