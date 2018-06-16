import random
import numpy as np
import itertools

def relabel_to_front(C, source, sink):
     n = len(C) # C is the capacity matrix
     F = [[0] * n for _ in xrange(n)]
     # residual capacity from u to v is C[u][v] - F[u][v]

     height = [0] * n # height of node
     excess = [0] * n # flow into node minus flow from node
     seen   = [0] * n # neighbours seen since last relabel
     # node "queue"
     nodelist = [i for i in xrange(n) if i != source and i != sink]

     def push(u, v):
         send = min(excess[u], C[u][v] - F[u][v])
         F[u][v] += send
         F[v][u] -= send
         excess[u] -= send
         excess[v] += send

     def relabel(u):
         # find smallest new height making a push possible,
         # if such a push is possible at all
         min_height = 10000000000
         for v in xrange(n):
             if C[u][v] - F[u][v] > 0:
                 min_height = min(min_height, height[v])
                 height[u] = min_height + 1

     def discharge(u):
         while excess[u] > 0:
             if seen[u] < n: # check next neighbour
                 v = seen[u]
                 if C[u][v] - F[u][v] > 0 and height[u] > height[v]:
                     push(u, v)
                 else:
                     seen[u] += 1
             else: # we have checked all neighbours. must relabel
                 relabel(u)
                 seen[u] = 0

     height[source] = n # longest path from source to sink is less than n long
     excess[source] = 1000000000 # send as much flow as possible to neighbours of source
     for v in xrange(n):
         push(source, v)

     p = 0
     while p < len(nodelist):
         u = nodelist[p]
         old_height = height[u]
         discharge(u)
         if height[u] > old_height:
             nodelist.insert(0, nodelist.pop(p)) # move to front of list
             p = 0 # start from front of list
         else:
             p += 1

     return sum(F[source])


def calc_opt():
    pass

def gen_single(f1,f2):
    N = 100
    M = 1000
    
    f1.write(str(1)+'\n')
    f1.write(str(N)+' '+str(M)+'\n')
    f1.write(str(1)+'\n'+str(0)+'\n'+str(1)+'\n'+str(N-1)+'\n')
    
    capacities = np.zeros((N,N))
    
    num = 0
    while num < M:
        v = random.randint(0,N-1)
        w = random.randint(0,N-1)
        while(v == w):
            w = random.randint(0,N-1)
        c = random.random()
        if capacities[v,w] == 0:
            capacities[v,w] = c
            num += 1
        
    for i in range(N):
        for j in range(N):
            if(capacities[i,j] > 0):
                f1.write(str(i)+' '+str(j)+' '+str(capacities[i,j])+'\n')
    
    f2.write(str(relabel_to_front(capacities,0,N-1))+'\n')
        
    

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
    gen_test(20)
    
