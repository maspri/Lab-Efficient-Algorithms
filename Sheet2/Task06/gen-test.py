import random
import itertools
import sys

def mis(instance):
    max_ind = 0
    for i in range(1,instance['n']+1):
        for i_subset in itertools.combinations(range(instance['n']),i):
            independent = True
            for j in range(i):
                for k in range(j+1,i):
                    if (i_subset[j],i_subset[k]) in instance['edges'] or (i_subset[k],i_subset[j]) in instance['edges']:
                        independent = False
            if independent:
                if i > max_ind:
                    max_ind = i
    instance['mis'] = max_ind
                        
def gen_instance(n,prob_edge):
    instance = {}
    instance['n'] = n
    instance['prob_edge'] = prob_edge
    instance['edges'] = []
    for i in range(n):
        for j in range(i+1,n):
            if random.random() <= prob_edge:
                instance['edges'] += [(i,j)]
    mis(instance)
    return instance

def write_instance(instance,f1,f2):
    f1.write(str(instance['n'])+' '+str(len(instance['edges']))+'\n')
    for i,j in instance['edges']:
        f1.write(str(i+1)+' '+str(j+1)+'\n')
    f2.write(str(instance['mis'])+'\n')

def gen_test(n,num,prob):
    with open('test.cases','w') as f1, open('test.results','w') as f2:
        f1.write(str(num)+'\n')
        for i in range(num):
            print(i)
            instance = gen_instance(n,prob)
            write_instance(instance,f1,f2)

if __name__ == '__main__':
    if len(sys.argv) == 4:
        gen_test(int(sys.argv[1]),int(sys.argv[2]),int(sys.argv[3]))
    elif len(sys.argv) == 3:
        gen_test(int(sys.argv[1]),int(sys.argv[2]),0.3)
    else:
        gen_test(12,10,0.1)
    
    
