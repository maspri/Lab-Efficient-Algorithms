import random
import itertools
import math
from scipy.sparse import csr_matrix
from scipy.sparse.csgraph import minimum_spanning_tree
import numpy as np

def dist(a,b):
    x1,y1 = a
    x2,y2 = b
    return math.sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))

def mst(points):
    
    p1 = points[0]
    n = len(points)
    dist_matrix = csr_matrix((n,n),dtype=np.float)
    
    for i in range(n-1):
        for j in range(i,n):
            dist_matrix[i,j] = dist(points[i],points[j])
    
    Tcsr = minimum_spanning_tree(dist_matrix)
    
    val = np.max(Tcsr.toarray())
    
    return val
            
            

def gen_test(num,n):
    for k in range(num):
        numberstr = ''
        if k < 10:
            numberstr = '0'+str(k)
        else:
            numberstr = str(k)
        print(numberstr)
        with open('test.cases.' + numberstr, 'w') as f1, open('test.results.' + numberstr, 'w') as f2:
            points = []
            for j in range(n):
                x = random.randint(1,150)
                y = random.randint(1,150)
                points += [(x,y)]
            val = mst(points)
            
            
            f1.write(str(n)+' 0\n')
            for x,y in points:
                f1.write(str(x)+' '+str(y)+'\n')
            f2.write('{:0.3f}'.format(val)+'\n')
        
        
        
if __name__ == '__main__':
    gen_test(1,1000)
    #print(tsp([(7,21),(57,30),(40,103),(30,64),(113,86),(45,118)])+5*8*2)
    #print(tsp([(10,26),(83,98),(141,80),(87,29),(94,37)])+4*8*2)
    #print(tsp([(133,74),(50,87),(73,112)])+2*8*2)
        
        
