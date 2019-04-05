#include "testlib.h"
#define MAXN 500005
#define MAXM 500005
int a[MAXM];

int main(int argc,char * argv[]){
    registerTestlibCmd(argc,argv);
    int n,m;
    int fin_ans=0,your_ans,std_ans;
    n=inf.readInt();
    m=inf.readInt();
    for (int i=1;i<=m;i++)
        a[i]=inf.readInt();
    your_ans=ouf.readInt();
    std_ans=ans.readInt();
    for (int i=1;i<=n;i++){
        int tchose;
        tchose=ouf.readInt();
        if (tchose<1 || tchose>m){
            if (i==1 && (!tchose) && your_ans==std_ans)
                quitp(0.6,"You didn't give the method and you get %d percent.",60);
            else
                quitf(_wa,"Invalid method.");
        }
        a[tchose]--;
        if (a[tchose]<0)
            quitf(_wa,"Invalid method.");
        int bj=inf.readInt();
        int ok=0;
        while (bj--){
            int t=inf.readInt();
            if (t==tchose)
                ok=1;
        }
        ok?(fin_ans++):(0);
    }
    if (fin_ans==your_ans && your_ans==std_ans)
        quitf(_ok,"Correct answer and best method.");
    if (fin_ans!=your_ans)
        quitf(_wa,"Wrong answer, expected %d matches but got %d in fact.",your_ans,fin_ans);
    double perc=int(your_ans*10/std_ans)/10.0;
    quitp(perc,"Your answer isn't good enough and you get %d percent.",int(perc*100));
}