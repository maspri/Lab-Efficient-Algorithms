import random
import itertools
import math

def dist(a,b):
    x1,y1 = a
    x2,y2 = b
    return math.sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))

def tsp(points):
    
    p1 = points[0]
    
    min_dist = 101010101010.0
    for perm in itertools.permutations(points[1:]):
        p = p1
        d = 0.0
        for pp in perm:
            d += dist(p,pp)
            p = pp
        if d < min_dist:
            min_dist = d
    return min_dist
            
            

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
            val = tsp(points)+(n-1)*8*2
            
            f1.write(str(n)+'\n')
            for x,y in points:
                f1.write(str(x)+' '+str(y)+'\n')
            f1.write('0\n')
            f2.write('{:0.2f}'.format(val)+'\n')
        
        
        
if __name__ == '__main__':
    gen_test(60,10)
    #print(tsp([(7,21),(57,30),(40,103),(30,64),(113,86),(45,118)])+5*8*2)
    #print(tsp([(10,26),(83,98),(141,80),(87,29),(94,37)])+4*8*2)
    #print(tsp([(133,74),(50,87),(73,112)])+2*8*2)
        
        
