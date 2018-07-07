import random
import numpy as np
import itertools


def calc_opt(points,pairs,taken):
    n = len(points)

def gen_single(f1,f2):

    N = 100
    f1.write(str(N)+'\n')
    
    points = np.zeros((N,2))
    num = 0
    maxnum = 0
    
    while num < N:
        sx = random.randint(-100,100)
        sy = random.randint(-100,100)
        
        dirX = random.randint(-10,10)
        dirY = random.randint(-10,10)
        
        n = random.randint(1,N-num);
        if n > maxnum:
            maxnum = n
        for i in range(n):
            l = random.uniform(1,20)
            points[num,0] = sx + l*dirX
            points[num,1] = sy + l*dirY
            num += 1
            
    np.random.shuffle(points)
    for p in points:
        f1.write(str(p[0])+' '+str(p[1])+'\n')
        
            
    f2.write(str(maxnum)+'\n')
        
    

def gen_test(num):
    for k in range(num):
        numberstr = ''
        if k < 10:
            numberstr = '0'+str(k)
        else:
            numberstr = str(k)
        print(numberstr)
        with open('test.cases.' + numberstr, 'w') as f1, open('test.results.' + numberstr, 'w') as f2:
            gen_single(f1,f2)
            

if __name__ == '__main__':
    gen_test(10)
    
