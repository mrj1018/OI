import cyaron
import random

n_lst=cyaron.ati([0,15,13,14,15,5e3,5e3,5e3,5e5,5e5,5e5])
m_lst=cyaron.ati([0,1, 13,14,15,5e3,5e3,5e3,5e5,5e5,5e5])

for i in range(1,11):
    test_data=cyaron.IO(file_prefix="vote",data_id=i)

    n=n_lst[i]
    m=m_lst[i]

    test_data.input_writeln(n,m)

    w=cyaron.Vector.random(num=n,position_range=[(1,2000)],mode=1)

    test_data.input_writeln(w)

    for i in range(n):
        x=random.choice((1,2,3,4))
        if x==1 or x==2:
            y=random.randint(1,m)
        else:
            y=random.randint(0,m)
        test_data.input_writeln(x,y)

    #test_data.output_gen("D:/OI/Problems/Hanakiko_daily_1/data/vote/std.exe")