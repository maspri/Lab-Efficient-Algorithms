import random
import numpy as np
import itertools

def LU(field):
    pass


def fill(m,n):
    field = np.zeros((m*n,m*n),dtype=bool)
    for i in range(m*n):
        x = i / n
        y = i % n
        if x > 0:
            field[i,(x-1)*n+y] = True
        if x < m-1:
            field[i,(x + 1)*n+y] = True
        if y > 0:
            field[i,x*n + (y - 1)] = True
        if y < n-1:
            field[i,x*n+(y + 1)] = True
    LU(field)

def gen_single(f1,f2):
    m,n = (16,16)
    N = 16
    num = random.randint(5,50)
    field = np.zeros((m,n),dtype=bool)
    
    for i in range(num):
        x = random.randint(0,m-1)
        y = random.randint(0,n-1)
        field[x,y] = not field[x,y]
        if x > 0:
            field[x-1,y] = not field[x-1,y]
        if x < m-1:
            field[x+1,y] = not field[x+1,y]
        if y > 0:
            field[x,y-1] = not field[x,y-1]
        if y < n-1:
            field[x,y+1] = not field[x,y+1]
            
    for i in range(m):
        s = ''
        for j in range(n):
            if field[i,j]:
                s+= 'o'
            else:
                s+= '#'
        f1.write(s+'\n')
    f2.write(str(num)+'\n')
            

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
    
