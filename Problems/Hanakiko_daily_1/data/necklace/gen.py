import random
import cyaron

class Necklace:
    def __init__(self,raw:str):
        self.raw=raw
        self.sorted=str(sorted(list(raw)))
    def __eq__(self,rhs:"Necklace")->bool:
        if self.sorted!=rhs.sorted:
            return False
        l=len(self.raw)
        astr=self.raw+self.raw
        for i in range(0,l):
            if astr[i:i+l]==rhs.raw:
                return True
        return False

charsets="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

n_lst=[0,2,2,2,2,2,2,700,700,700,700]
l_lim_lst=[0,1000,1000,1000,20000,20000,20000,5000,5000,5000,5000]
p=993244853

for ti in range(1,11):
    if ti==7:
        ttttt=input()
    fin=open("necklace%d.in"%ti,"w",newline="\n")
    fout=open("necklace%d.out"%ti,"w",newline="\n")
    fin.write("5\n")
    n=n_lst[ti]
    l_lim=l_lim_lst[ti]
    if ti==1:
        char_choose="A"
    else:
        char_choose=charsets
    for test in range(5):
        fin.write("%d\n"%n)
        if n==2:
            tuniq=random.choice((1,2))
        else:
            tuniq=random.randint(n//3,n//2)
        tuniq=max(tuniq,1)
        if ti==1:
            tuniq=1
        uniq_lst=[]
        appear_lst=[0]*tuniq
        leng=0
        while leng<tuniq:
            tstr_l=[]
            for j in range(l_lim):
                tstr_l.append(random.choice(char_choose))
            tstr=''.join(tstr_l)
            tne=Necklace(tstr)
            if tne not in uniq_lst:
                uniq_lst.append(tne)
                leng+=1
        for i in range(n):
            this_str_ind=random.randint(0,tuniq-1)
            appear_lst[this_str_ind]+=1
            this_str=uniq_lst[this_str_ind].raw
            ttstr=this_str+this_str
            tlen=len(this_str)
            tstart=random.randint(0,tlen-1)
            fin_str=ttstr[tstart:tstart+tlen]
            #print(type(fin_str))
            fin.write("%s\n"%fin_str)
        ans=n*(n-1)//2
        ans=pow(ans,p-2,p)
        tcnt=0
        for i in appear_lst:
            if i<2:
                continue
            ttans=i*(i-1)//2
            ttans%=p
            tcnt=(tcnt+ttans)%p
        ans=ans*tcnt%p
        fout.write("%d\n"%ans)
    fin.close()
    fout.close()
    print("%d done."%ti)
