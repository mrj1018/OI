#include <cstdio>
#include <cctype>
#include <map>
#include <string>
#define MAXL 50005
#define MOD 993244853
using namespace std;
typedef long long ll;
char tstr[MAXL];
const ll two_inv=496622427;
string tstring;
map<string,int> mp;

int get_str(void);
ll exgcd(ll a,ll b,ll &x,ll &y);
int main(void){
    int test_cases;
    scanf("%d",&test_cases);
    while (test_cases--){
        int n;
        mp.clear();
        scanf("%d",&n);
        for (int i=0;i<n;i++){
            int l=get_str();
            int min_pos;
            {
                //copy
                char *p1,*p2,*ptar;
                p1=tstr,p2=ptar=tstr+l;
                while (p1<ptar)
                    *p2=*p1,p1++,p2++;
            }
            {
                //get_min
                int ti=0,tj=1,tk=0;
                int status=0; //0-i,1-j
                while (ti<l && tj<l){
                    for (tk=0;tk<l;tk++){
                        int apos=ti+tk,bpos=tj+tk;
                        if (tstr[apos]<tstr[bpos]){
                            status=0;
                            break;
                        }
                        if (tstr[apos]>tstr[bpos]){
                            status=1;
                            break;
                        }
                    }
                    switch (status){
                        case 0:
                            tj+=(tk+1);
                            (ti==tj)?(tj++):(0);
                            break;
                        case 1:
                            ti+=(tk+1);
                            (ti==tj)?(ti++):(0);
                            break;
                        default:
                            status=0;
                            tj+=(tk+1);
                            (ti==tj)?(tj++):(0);
                            break;
                    }
                }
                min_pos=(status)?(tj):(ti);
            }
            tstring=string(tstr+min_pos,l);
            if (mp.count(tstring))
                mp[tstring]++;
            else
                mp[tstring]=1;
        }
        ll total_inv=(ll)(n)*(n-1)%MOD;
        total_inv=total_inv*two_inv%MOD;
        {
            //get total inv
            ll x,y;
            exgcd(total_inv,ll(MOD),x,y);
            x=(x%MOD+MOD)%MOD;
            total_inv=x;
        }
        ll tmethods=0;
        for (map<string,int>::iterator it=mp.begin();it!=mp.end();it++){
            ll a=ll(it->second);
            if (a==1)
                continue;
            ll imethods=a*(a-1)%MOD;
            imethods=imethods*two_inv%MOD;
            tmethods=(tmethods+imethods)%MOD;
        }
        ll ans=tmethods*total_inv%MOD;
        printf("%lld\n",ans);
    }
    return 0;
}

int get_str(void){
    char ch;
    int l=0;
    ch=getchar();
    while (!isalpha(ch))
        ch=getchar();
    while (isalpha(ch)){
        tstr[l++]=ch;
        ch=getchar();
    }
    return l;
}

ll exgcd(ll a,ll b,ll &x,ll &y){
    if (!b){
        x=1,y=0;
        return a;
    }
    ll g,q,r,xx,yy;
    q=a/b,r=a-q*b;
    g=exgcd(b,r,xx,yy);
    x=yy;
    y=xx-q*yy;
    return g;
}