import random
import numpy as np
import itertools

def brute_force(N,start,goal,distances,capacity_speed):
    #Dont look at it. Its the worst.
    nodes = []
    for i in range(N):
        if i != start and i != goal:
            nodes.append(i)
    
    min_dist = 100000000.0
    for m in range(0,N-1):
        for subset in itertools.combinations(nodes,m):
            for perm in itertools.permutations(subset):
                dist = 0
                p = start
                for pp in [*perm,goal]:
                    weight = distances[p,pp]/capacity_speed[p,1]
                    if weight > 0 and weight < capacity_speed[p,0]:
                        dist += weight
                        p = pp
                    else:
                        dist = 100000001.0
                        break
                if dist < min_dist:
                    min_dist = dist
    if min_dist == 100000000.0:
        return -1.0
    else:
        return min_dist
        
        

def calc_opt(N,Q,capacity_speed,distances,queries):
    dists = []
    for v,w in queries:
        dists.append(brute_force(N,v-1,w-1,distances,capacity_speed))
    return dists

def gen_single(f1,f2):
    N = 10
    Q = 20
    
    f1.write(str(N)+' '+str(Q)+'\n')
    
    locations = np.zeros((N,2))
    capacity_speed = np.zeros((N,2),dtype=int)
    queries = []
    distances = np.zeros((N,N),dtype=int)
    
    for i in range(N):
        #locations[i,0] = randint(1,150)
        #locations[i,1] = randint(1,150)
        capacity_speed[i,0] = random.randint(10,20)
        capacity_speed[i,1] = 1#random.randint(1,20)
        f1.write(str(capacity_speed[i,0])+' '+str(capacity_speed[i,1])+'\n')
    
    for i in range(N):
        s = ''
        for j in range(N):
            if random.random() < 0.1 or i == j:
                distances[i,j] = -1
            else:
                distances[i,j] = random.randint(1,20)
                
    for i in range(N):
        s = ''
        for j in range(N):
            s+= str(distances[i,j])+' '
        f1.write(s[:-1]+'\n')
        
    for i in range(Q):
        v = 0
        w = 0
        while v == w:
            v = random.randint(1,N)
            w = random.randint(1,N)
        queries += [(v,w)]
        f1.write(str(v)+' '+str(w)+'\n')
    
    f2.write(' '.join(map(lambda res:'{:0.2f}'.format(res),calc_opt(N,Q,capacity_speed,distances,queries)))+' ')
    
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
    
