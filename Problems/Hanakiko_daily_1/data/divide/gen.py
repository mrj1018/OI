import random
import cyaron

n_lst=cyaron.ati([0,1,1,8,8,50,50,1000,1000,10000,10000])
m_lst=cyaron.ati([0,1,8,8,8,50,50,100, 100, 1000, 1000])


for i in range(1,11):
    test_data=cyaron.IO(file_prefix="divide",data_id=i)

    n=n_lst[i]
    m=m_lst[i]

    bjmax=min(m//4,10)
    if bjmax<1:
        bjmax=1
    bjmin=max(1,bjmax//10)
    wmax=max(n/m*3//2,1)
    if i==5:
        bjmax=1
    if bjmin>bjmax:
        bjmin=bjmax

    test_data.input_writeln(n,m)

    w=[random.randint(1,wmax) for i in range(m)]
    if sum(w)<n:
        w[random.randint(0,len(w)-1)]+=n-sum(w)

    test_data.input_writeln(w)

    for i in range(n):
        bj=random.randint(bjmin,bjmax)
        lst=random.sample(range(1,m+1),bj)
        random.shuffle(lst)
        test_data.input_writeln(bj,lst)

    test_data.output_gen("D:/OI/Problems/Hanakiko_daily_1/data/divide/std.exe")