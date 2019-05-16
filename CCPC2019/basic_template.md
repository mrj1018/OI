## 基础模板 by Hanakiko, Sweetlemon

### ACM 基本框架

```cpp
#include <cstdio>
#include <cctype>
#include <iostream>
#include <algorithm>
#define MAXIOLG 25
typedef long long ll;
typedef int io_t;
io_t iotemp[MAXIOLG];
using namespace std;

io_t seto(void);
void ayano(io_t x,char spliter='\n');

int main(void){
    int testdatas=seto();
    while (testdatas--){
		//Do something
    }
    return 0;
}

io_t seto(void){
    int symbol=0;
    io_t ans=0;
    char ch=getchar();

    while (!isdigit(ch)){
        if (ch=='-')
            symbol=1;
        ch=getchar();
    }
    while (isdigit(ch)){
        ans=ans*10+(ch-'0');
        ch=getchar();
    }
    return (symbol)?(-ans):(ans);
}

void ayano(io_t x,char spliter){
    if (!x){
        putchar('0');
        putchar(spliter);
        return;
    }
    if (x<0){
        putchar('-');
        x=-x;
    }
    int len=0;
    while (x){
        io_t d=x/10;
        iotemp[len++]=x-d*10;
        x=d;
    }
    while (len){
        len--;
        putchar(iotemp[len]+'0');
    }
    putchar(spliter);
}
```

### 数学

#### $\gcd$

```cpp
int gcd(int a,int b){
    int t;
    while (b)
        t=a,a=b,b=t%b;
    return a;
}
```

#### $\mathrm{exgcd}$

```cpp
int exgcd(int a,int b,int &x,int &y){
    if (!b){
        x=1,y=0;
        return a;
    }
    int g,xx,yy;
    int q,r;
    q=a/b,r=a-q*b;
    g=exgcd(b,r,xx,yy);
    x=yy,y=xx-q*yy;
    return g;
}
```

#### $\mathrm{kasumi}$

```cpp
inline int kasumi(int a,int b,int p){
    int ans=0;
    while (b){
        (b&1)?(ans=(ans*a)%p):(0);
        a=(a*a)%p;
        b>>=1;
    }
    return ans;
}
```

#### 线性筛

```cpp
int minp[MAXN]={0}; //Min prime factor
int prime[MAXN],pr=0;
void make_p(int n){
    minp[1]=2; //No meaning
    for (int i=2;i<=n;i++){
        if (!minp[i]){
            minp[i]=i;
            prime[pr++]=i;
        }
        int t;
        for (int j=0;j<pr && (t=prime[j]*i)<=n;j++){
            minp[t]=prime[j];
            if (prime[j]==minp[i])
                break;
        }
    }
}
```

#### 整除分块

$$\sum^{n}_{i=1}\lfloor \frac{n}{i} \rfloor$$

```cpp
l=1;
while (l<=n){
    d=n/l;
    r=n/d+1;
    ans+=d*(r-l); //ans=f(d)*(r-l)
    l=r;
}
```

#### 线性递推逆元

```cpp
inv[1]=1;
for (int i=2;i<=n;i++)
    inv[i]=ll(p-p/i)*inv[p%i]%p;
```

#### 数位$\mathrm{dp}$

给定两个正整数$a$和$b$，求在$[a,b]$中的所有整数中，每个数码各出现了多少次。

```cpp
#include <iostream>
#define MAXDIGITS 25
using namespace std;
typedef long long ll;
ll digcal[MAXDIGITS]={0};
ll digans[MAXDIGITS]={0};
ll f[MAXDIGITS];
ll dignum[]={0,10,90,900,9000,90000,900000,9000000,90000000,900000000ll,9000000000ll,90000000000ll,900000000000ll,9000000000000ll,90000000000000ll};
ll pow10[]={1,10,100,1000,10000,100000,1000000,10000000,100000000ll,1000000000ll,10000000000ll,100000000000ll,1000000000000ll,10000000000000ll};
void solve(ll x,ll dig); //00000-x, takes up dig digits.
void update_0(ll x); //minus the fore 0
ll get_dig(ll x); //how many digits does x take up

int main(void){
    ll a,b;
    ll diga,digb;
    cin >> a >> b;
    a--;
    //calc [0,a]
    diga=get_dig(a);
    solve(a,diga);
    update_0(a); //Delete the fore 0
    for (int i=0;i<=9;i++){
        digans[i]=-digcal[i];
        digcal[i]=0;
    }
    //calc [0,b]
    digb=get_dig(b);
    solve(b,digb);
    update_0(b);
    for (int i=0;i<=9;i++){
        digans[i]+=digcal[i];
        cout << digans[i] << ' ';
    }
    cout << endl;
    return 0;
}

void solve(ll x,ll dig){
    if (!dig)
        return;
    ll num_first=x/pow10[dig-1];
    
    for (int i=0;i<num_first;i++)
        digcal[i]+=(pow10[dig-1]);
    if (dig>1){
        for (int j=0;j<=9;j++)
            digcal[j]+=(dig-1)*pow10[dig-2]*num_first;
    }
    ll left=x%pow10[dig-1];
    digcal[num_first]+=(left+1);
    if (dig>1)
        solve(left,dig-1);
}

void update_0(ll x){
    ll dig=get_dig(x);
    for (int i=1;i<dig;i++)
        digcal[0]-=(dignum[i]*(dig-i));
}

ll get_dig(ll x){
    if (!x)
       return 1;
    ll ans=0;
    while (x){
        ans++;
        x/=10;
    }
    return ans;
}
```

#### 莫比乌斯反演

对于给定的整数$a,b,d$，有多少正整数对$(x,y)$，满足$x\le a,\ \ y\le b,\ \ \gcd(x,y)=d.$

```cpp
#include <cstdio>
#define N 50000
#define MAXN 50005
using namespace std;
typedef long long ll;
bool is_np[MAXN]={0};
int primes[MAXN],mu[MAXN];
int prime_cnt=0;

void sieve(void);
int main(void){
    int test_datas;
    scanf("%d",&test_datas);
    sieve();
    for (int i=2;i<=N;i++)
        mu[i]+=mu[i-1];
    while (test_datas--){
        int a,b,d;
        scanf("%d%d%d",&a,&b,&d);
        a/=d,b/=d;
        (a<b)?(d=a,a=b,b=d):(0);
        int l=1,r;
        ll ans=0;
        while (l<=b){
            int d1,d2,r1,r2;
            d1=a/l,d2=b/l;
            r1=a/d1+1,r2=b/d2+1;
            (r1<r2)?(r=r1):(r=r2);
            ans+=1ll*d1*d2*(mu[r-1]-mu[l-1]);
            l=r;
        }
        printf("%lld\n",ans);
    }
    return 0;
}

void sieve(void){
    is_np[1]=1,mu[1]=1;
    for (int i=2;i<=N;i++){
        if (!is_np[i]){
            primes[prime_cnt++]=i;
            mu[i]=-1;
        }
        for (int j=0;j<prime_cnt;j++){
            int p=primes[j],k=i*p;
            if (k>N)
                break;
            is_np[k]=1;
            if (i/p*p==i){
                mu[k]=0;
                break;
            }
            else
                mu[k]=-mu[i];
        }
    }
}
```

#### 杜教筛

给定一个正整数$N(N\le2^{31}-1)$，求

$$ans_1=\sum_{i=1}^n\varphi(i)$$

$$ans_2=\sum_{i=1}^n \mu(i)$$

```cpp
#include <iostream>
#include <unordered_map>
#define MAXSIEVE 1999939
#define MAXSIEVEN 1999955
using namespace std;
typedef long long ll;
int is_n_prime[MAXSIEVEN]={0},primes[MAXSIEVEN],prime_cnt=0;
ll mu[MAXSIEVEN];
unordered_map<ll,ll> mp_mu;

ll calc_phi(ll x);
ll calc_mu(ll x);
void sieve(void);
int main(void){
    int test_datas;
    
    sieve();
    mu[1]=1;
    for (int i=2;i<=MAXSIEVE;i++)
        mu[i]+=mu[i-1]; //S of mu

    cin >> test_datas;
    while (test_datas--){
        ll n;
        cin >> n;
        cout << calc_phi(n) << ' ' << calc_mu(n) << endl;
    }
    return 0;
}

ll calc_phi(ll x){
    ll ans=0;
    int l,r;
    l=1;
    while (l<=x){
        int d=x/l;
        r=x/d+1;
        ll tans=(ll)(d)*d;
        tans*=(calc_mu(r-1)-calc_mu(l-1));
        ans+=tans;
        l=r;
    }

    //Convert to ans
    ans--;
    ans>>=1;
    ans++;
    return ans;
}

ll calc_mu(ll x){
    if (x<=MAXSIEVE)
        return mu[x];
    if (mp_mu.count(x))
        return mp_mu[x];
    ll l,r;
    l=2;
    ll ans=1;
    while (l<=x){
        ll d=x/l;
        r=x/d+1;
        ans-=calc_mu(d)*(r-l);
        l=r;
    }
    mp_mu[x]=ans;
    return ans;
}

void sieve(void){
    //...
}
```

#### 高斯消元

```cpp
#include <cstdio>
#include <cmath>
#define MAXN 105
#define EPS 0.00001
#define NOS "No Solution\n"
using namespace std;

struct vector{
	int n;
	double v[MAXN];
	vector(void){
		this->n=0;
		for (int i=0;i<MAXN;i++)
		    (this->v)[i]=0;
	}
	vector(int tn){
		this->n=tn;
		for (int i=0;i<tn;i++)
		    (this->v)[i]=0;
	}
	vector(const vector& cp){
		this->n=cp.n;
		for (int i=0;i<cp.n;i++)
		    (this->v)[i]=cp.v[i];
	}
	friend vector operator+(const vector& a,const vector& b);
	friend vector operator-(const vector& a,const vector& b);
	friend vector operator*(double lambda,const vector& v);
	friend double operator*(const vector& a,const vector& b);
};
double min(double a,double b);

int main(void){
	bool hss=1;
	bool found;
	int n,tint;
	vector ma[MAXN];
	vector ans;
	vector t;
	scanf("%d",&n);
	ans.n=n;
	for (int i=0;i<n;i++){
		ma[i].n=n+1;
		for (int j=0;j<=n;j++){
		    scanf("%d",&tint);
		    ma[i].v[j]=double(tint);
	    }
	}
	for (int i=0;i<n && hss;i++){ //消a_i
	    found=0;
		for (int j=i;j<n;j++){ //找a_i系数不为0的第j条方程
			if (abs(ma[j].v[i])>EPS){
				//交换第j条方程与第i条方程
				if (j!=i){
				    t=ma[j];
				    ma[j]=ma[i];
				    ma[i]=t;
			    }
			    found=1;
				break;
			}
		}
		if (!found){
			hss=0;
			break;
		}
		ma[i]=(1.00/ma[i].v[i])*ma[i];
		for (int j=i+1;j<n;j++)
			ma[j]=ma[j]-(ma[j].v[i]/ma[i].v[i])*ma[i];
	}
	if (hss){
		for (int i=n-1;i>=0;i--){
			ans.v[i]=(ma[i].v[n]-ma[i]*ans)/(ma[i].v[i]);
		}
	}
	if (!hss)
	    printf(NOS);
	else
		for (int i=0;i<n;i++)
            printf("%.2lf\n",ans.v[i]);
	
	return 0;
}

vector operator*(double lambda,const vector& v){
	vector ans(v);for (int i=0;i<v.n;i++)ans.v[i]=ans.v[i]*lambda;return ans;}
vector operator+(const vector& a,const vector& b){vector ans(a);for (int i=0;i<b.n;i++)ans.v[i]+=b.v[i];return ans;}
vector operator-(const vector& a,const vector& b){
	//...
}
double operator*(const vector& a,const vector& b){
	double ans=0;
	int tn=min(a.n,b.n);
	for (int i=0;i<tn;i++){
		if (abs(a.v[i])<=EPS || abs(b.v[i])<=EPS)
		    continue;
	    ans+=(a.v[i]*b.v[i]);
	}
	return ans;
}

inline double min(double a,double b){return a<b?a:b;}
```

#### $\mathrm{FFT}$

```cpp
#include <cstdio>
#include <cmath>
#define MAXDEG 2097152
#define LGDEG 21
#define HIGHEST 1048576
#define MAXDEGN 3000005
#define EPS 0.00001
using namespace std;
struct Complex{
    double re,im;
    Complex(void):re(0.0),im(0.0){}
    Complex(double tr,double ti=0.0):re(tr),im(ti){}
    Complex(const Complex& tc):re(tc.re),im(tc.im){}
    friend Complex operator+(const Complex& lhs,const Complex& rhs);
    friend Complex operator-(const Complex& lhs,const Complex& rhs);
    friend Complex operator*(const Complex& lhs,const Complex& rhs);
    friend Complex operator-(const Complex& x);
};

const double pi=acos(-1.0);
int reverse[MAXDEGN];
Complex a[MAXDEGN],b[MAXDEGN],t[MAXDEGN];
void fft(Complex* f,int is_inv=0);

int main(void){
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=0;i<=n;i++){
        double t;
        scanf("%lf",&t);
        a[i].re=t;
    }
    for (int i=0;i<=m;i++){
        double t;
        scanf("%lf",&t);
        b[i].re=t;
    }
    reverse[0]=0;
    for (int i=1;i<MAXDEG;i++)
        reverse[i]=(i&1)?(HIGHEST^(reverse[i>>1]>>1)):(reverse[i>>1]>>1);
    
    fft(a);
    fft(b);
    for (int i=0;i<MAXDEG;i++)
        a[i]=a[i]*b[i];
    
    fft(a,1);
    int npm=n+m;
    for (int i=0;i<=npm;i++)
        printf("%d ",(int)(a[i].re+0.5+EPS));
    return 0;
}

void fft(Complex* f,int is_inv){
    for (int i=0;i<MAXDEG;i++)
        t[i]=f[reverse[i]];
    for (int i=0;i<LGDEG;i++){
        int cur_len=1<<i;
        int tran_len=cur_len<<1;
        Complex omega_n=Complex(cos(pi/cur_len),sin(pi/cur_len)); //2pi/tran_len=pi/cur_len
        (is_inv)?(omega_n.im=-omega_n.im):(0);
        for (int unit_l=0;unit_l<MAXDEG;unit_l+=tran_len){
            Complex omega=Complex(1.0,0.0);
            for (int k=0;k<cur_len;k++,omega=omega*omega_n){
                //kth couple
                int cpa=unit_l+k;
                int cpb=cpa+cur_len;
                Complex a_val=t[cpa];
                Complex b_val=omega*t[cpb];
                t[cpa]=a_val+b_val;
                t[cpb]=a_val-b_val;
            }
        }
    }
    for (int i=0;i<MAXDEG;i++)
        f[i]=t[i];
    if (is_inv)
        for (int i=0;i<MAXDEG;i++)
            f[i].re/=MAXDEG,f[i].im/=MAXDEG;
}

Complex operator+(const Complex& lhs,const Complex& rhs){
    return Complex(lhs.re+rhs.re,lhs.im+rhs.im);
}
Complex operator-(const Complex& lhs,const Complex& rhs){/*...*/}
Complex operator*(const Complex& lhs,const Complex& rhs){
    return Complex(lhs.re*rhs.re-lhs.im*rhs.im, lhs.re*rhs.im+lhs.im*rhs.re);
}
Complex operator-(const Complex& x){
    return Complex(-x.re,-x.im);
}
```

#### $\mathrm{NTT}$

```cpp
#include <cstdio>
#define MOD 998244353
#define MODM 998244352
#define G 3
#define GINV 332748118
#define MAXDEGN 3000005
using namespace std;
typedef long long ll;

ll a[MAXDEGN],b[MAXDEGN],t[MAXDEGN];
int reverse[MAXDEGN];

void ntt(ll *f,int lim,int is_inv=0);
ll kasumi(ll a,ll b);

int main(void){
    int n,m,npm;
    int lim=1,highest;
    scanf("%d%d",&n,&m);
    npm=n+m;
    while (lim<=npm)
        lim<<=1;
    highest=lim>>1;
    for (int i=0;i<=n;i++)
        scanf("%lld",a+i);
    for (int i=0;i<=m;i++)
        scanf("%lld",b+i);
    reverse[1]=highest,reverse[0]=0;
    for (int i=2;i<lim;i++)
        reverse[i]=(i&1)?((reverse[i>>1]>>1)^highest):(reverse[i>>1]>>1);
    
    ntt(a,lim);
    ntt(b,lim);
    
    for (int i=0;i<lim;i++)
        a[i]=a[i]*b[i]%MOD;
    
    ntt(a,lim,1);
    for (int i=0;i<=npm;i++)
        printf("%lld ",a[i]);
    return 0;
}

void ntt(ll *f,int lim,int is_inv){
    for (int i=0;i<lim;i++)
        t[i]=f[reverse[i]];
    for (int cur_l=1;cur_l<lim;cur_l<<=1){
        int tl=cur_l<<1;
        ll omega_n=kasumi((is_inv)?(GINV):(G),MODM/tl);
        for (int unit_l=0;unit_l<lim;unit_l+=tl){
            ll omega=1;
            for (int cpid=0;cpid<cur_l;cpid++,omega=omega*omega_n%MOD){
                //cpid th couple
                int cpa=unit_l+cpid;
                int cpb=cpa+cur_l;
                ll a_val=t[cpa];
                ll b_val=t[cpb]*omega%MOD;
                t[cpa]=(a_val+b_val)%MOD;
                t[cpb]=(a_val+MOD-b_val)%MOD;
            }
        }
    }
    if (is_inv){
        ll lim_inv=kasumi(lim,MOD-2);
        for (int i=0;i<lim;i++)
            f[i]=t[i]*lim_inv%MOD;
    }
    else
        for (int i=0;i<lim;i++)
            f[i]=t[i];
}

ll kasumi(ll a,ll b){/*...*/}
```

#### 扩展中国剩余定理

```cpp
#include <cstdio>
#include <cctype>
#define MAXIOLG 25
#define FILENAME(x)\
freopen(x".in","r",stdin);\
freopen(x".out","w",stdout);
using namespace std;

typedef long long ll;
typedef ll io_t;
io_t shin[MAXIOLG];
io_t seto(void);
void ayano(io_t x,char spliter='\n');

ll gcd(ll a,ll b);
ll exgcd(ll a,ll b,ll &x,ll &y);
ll mul(ll a,ll b,ll p);

int main(void){
    ll n;
    ll ans=0;
    ll tmod=1;
    n=seto();
    while (n--){
        ll a,b;
        ll nmod;
        a=seto(),b=seto();
        ll g,x,y;
        ll tdelta;
        g=exgcd(tmod,a,x,y);
        nmod=tmod/g*a;
        tdelta=(b-ans)/g;
        (tdelta<0)?(tdelta+=nmod):(0);
        x%=nmod;
        (x<0)?(x+=nmod):(0);
        x=mul(x,tdelta,nmod);
        
        ans=(mul(x,tmod,nmod)+ans)%nmod;
        tmod=nmod;
    }
    ayano(ans);
    return 0;
}
```


#### 卢卡斯定理

给定$n,m,p\ \ (1\le n,m,p\le 10^5)$，求 $\mathrm{C}_{n+m}^{m} \pmod {p}$，保证$p$为质数。

```cpp
#include <iostream>
#define MAXN 200005
using namespace std;
typedef long long ll;
int c[MAXN],inv[MAXN];
int p;
int solve(int n,int m);
int main(void){
    int t;
    cin >> t;
    for (int ti=0;ti<t;ti++){
        int n,m;
        cin >> n >> m >> p;
        n+=m;
        inv[1]=1;
        for (int i=2;i<p;i++)
            inv[i]=ll(p-p/i)*inv[p%i]%p;
        cout << solve(n,m) << endl;
    }
    return 0;
}

int solve(int n,int m){
    if (n<p && m<p){
        if (m>n)
            return 0;
        c[0]=1;
        for (int i=1;i<=m;i++){
            c[i]=ll(c[i-1])*(n-i+1)%p;
            c[i]=ll(c[i])*inv[i]%p;
        }
        return c[m];
    }
    else
        return ll(solve(n%p,m%p))*solve(n/p,m/p)%p;
}
```
