import random
import numpy as np
import itertools

def brute_force(N,start,goal,distances,allowed):
    #Dont look at it. Its the worst.
    nodes = []
    for i in range(N):
        if i != start and i != goal and allowed[i] == 0:
            nodes.append(i)
    
    min_dist = 100000000.0
    min_paths = []
    for m in range(0,N-1):
        for subset in itertools.combinations(nodes,m):
            for perm in itertools.permutations(subset):
                dist = 0
                p = start
                for pp in [*perm,goal]:
                    weight = distances[p,pp]
                    if weight > 0:
                        dist += weight
                        p = pp
                    else:
                        dist = 100000001.0
                        break
                if dist < min_dist:
                    min_dist = dist
                    min_paths = []
                    min_paths += [perm]
                elif dist == min_dist:
                    min_paths += [perm]
                    
    if min_dist == 100000000.0:
        return -1,()
    else:
        return min_dist,min_paths

def gen_single(f1,f2):
    N = 5
    M = 15
    
    f1.write(str(N)+' '+str(M)+'\n')
    
    distances = np.zeros((N,N),dtype=int)
    allowed = np.zeros(N,dtype=int)
    
    num = 0
    while num < M:
        v = random.randint(0,N-1)
        w = random.randint(0,N-1)
        while(v == w):
            w = random.randint(0,N-1)
        c = random.randint(1,20)
        if distances[v,w] == 0:
            distances[v,w] = c
            num += 1
    
    f1.write(str(1)+' '+str(N-2)+'\n')
    f1.write(str(0)+' '+str(N-1)+'\n')
        
    for i in range(N):
        for j in range(N):
            if(distances[i,j] > 0):
                f1.write(str(i)+' '+str(j)+' '+str(distances[i,j])+'\n')
        
    min_dist,min_paths = brute_force(N,0,N-1,distances,allowed)
    
    pp = 0
    allowed[pp] = 1
    for min_path in min_paths:
        for p in [*min_path,N-1]:
            allowed[p] = 1
            distances[pp,p] = -1
            pp = p
    
    min_dist1,min_path1 = brute_force(N,1,N-2,distances,allowed)  
    
    f1.write(str(0)+' '+str(0)+'\n')
    
    f2.write(str(min_dist1)+'\n')
    
    #        s += str(np.linalg.norm(locations[i]-locations[j]))
    #        distances[i,j] = np.linalg.norm(locations[i]-locations[j])
    
            
    
        
        
    

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
    
