import math

ls=[]
for i in range(4499540860,4499540865):
    if i%1000000==0:
        print(i)
    a0=9*i  #0
    a1=a0+2 #2
    a2=a1+3 #5
    a3=a2+3 #8
    if not (a0%10==2 or a0%10==3 or a0%10==7 or a0%10==8):
        s=str(a0)
        x=int(s+s)
        sq=int(math.sqrt(x))
        if sq*sq==x:
            ls.append(x)
    if not (a1%10==2 or a1%10==3 or a1%10==7 or a1%10==8):
        s=str(a1)
        x=int(s+s)
        sq=int(math.sqrt(x))
        if sq*sq==x:
            ls.append(x)
    if not (a2%10==2 or a2%10==3 or a2%10==7 or a2%10==8):
        s=str(a2)
        x=int(s+s)
        sq=int(math.sqrt(x))
        if sq*sq==x:
            ls.append(x)
    if not (a3%10==2 or a3%10==3 or a3%10==7 or a3%10==8):
        s=str(a3)
        x=int(s+s)
        sq=int(math.sqrt(x))
        if sq*sq==x:
            ls.append(x)
print("---------------------------")
for i in ls:
    print(i)