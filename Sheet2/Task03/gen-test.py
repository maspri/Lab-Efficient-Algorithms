import random
import numpy as np


def gen_test():
    
    a = np.zeros((0),dtype='intc')
    
    with open('test.cases','w') as f,open('test.results','w') as f2:
        for i in range(11000):
            n = random.randint(1,100)
            a.append(a,n)
            f.write(str(n)+'\n')
            f2.write(str(a.median())+'\n'))

if __name__ == '__main__':
    gen_test()