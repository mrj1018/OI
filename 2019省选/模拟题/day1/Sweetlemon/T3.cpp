#include <cstdio>
#include <algorithm>
const int MAXN=100005;
using namespace std;
struct Basket{
    int a,b,c;
    Basket(void):a(0),b(0),c(0){}
    Basket(int ta,int tb,int tc):a(ta),b(tb),c(tc){}
    Basket(const Basket& tb):a(tb.a),b(tb.b),c(tb.c){}
    friend bool operator<(const Basket& lhs,const Basket& rhs);
    friend bool operator==(const Basket& lhs,const Basket& rhs);
};

int main(void){

    return 0;
}

bool operator<(const Basket& lhs,const Basket& rhs){
    if (lhs.a<rhs.a)
        return 1;
    if (lhs.a>rhs.a)
        return 0;
    if (lhs.b<rhs.b)
        return 1;
    if (lhs.b>rhs.b)
        return 0;
    return (lhs.c<rhs.c);
}

bool operator==(const Basket& lhs,const Basket& rhs){
    return lhs.a==rhs.a && lhs.b==rhs.b && lhs.c==rhs.c;
}