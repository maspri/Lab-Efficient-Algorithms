import random
import numpy as np

def path_exists(edges,visited,v,w):
    if v == w:
        return True
    else:
        visited[v] = 1
        found = False
        if v in edges:
            for z in edges[v]:
                if visited[z] == 0:
                    found = path_exists(edges,visited,z,w)
        return found

def gen_test():
    with open('test.cases','w') as f,open('test.results','w') as f2:
        n = random.randint(1,50)
        ne = random.randint(1,200)

        edges = {}
        succ = 0
        fail = 0
        
        f.write(str(1)+'\n')
        f.write(str(n)+' '+str(ne)+'\n')

        for i in range(ne):
            et = random.choice(['n','q'])

            v,w = random.randint(1,n),random.randint(1,n)
            if et == 'n':
                while v == w:
                    v,w = random.randint(1,n),random.randint(1,n)

                if not v in edges:
                    edges[v] = []
                if not w in edges:
                    edges[w] = []
                if v not in edges[w]:
                    edges[w] += [v]
                if w not in edges[v]:
                    edges[v] += [w]

                f.write('n '+str(v)+' '+str(w)+'\n')
                print('n '+str(v)+' '+str(w)+'\n')
            else:
                f.write('q '+str(v)+' '+str(w)+'\n')
                if path_exists(edges,np.zeros(n+1),v,w):
                    print('q '+str(v)+' '+str(w)+' success\n')
                    succ = succ+1
                else:
                    print('q '+str(v)+' '+str(w)+' fail\n')
                    fail = fail+1
        f2.write(str(succ)+' '+str(fail)+'\n')
        print(str(succ)+' '+str(fail)+'\n')


if __name__ == '__main__':
    gen_test()
