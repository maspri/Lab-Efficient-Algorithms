import random
import numpy as np
import sys


def gen_test():
    
    a = np.zeros((0))
    
    with open('test.cases','w') as f,open('test.results','w') as f2:
        for i in range(11000):
            n = random.randint(1,100)
            a = np.append(a,n)
            f.write(str(n)+'\n')
            f2.write(str(int(np.median(a)))+'\n')
            
def gen_test_reverse_case():
    a = np.zeros((0))
    
    with open('test.cases','w') as f,open('test.results','w') as f2:
        for i in range(10999,-1,-1):
            a = np.append(a,i)
            f.write(str(i)+'\n')
            f2.write(str(int(np.median(a)))+'\n')

if __name__ == '__main__':
    if sys.argv[1] == '1':
        gen_test()
    elif sys.argv[1] == '2':
        gen_test_reverse_case()
