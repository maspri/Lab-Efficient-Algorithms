import random
import sys

def calc_max_freqs(parts,queries):
    with open('test.results','w') as f:
        for i,j in queries:
            max_freq = 0
            for left,right,amount in parts:
                if i < left and right < j:
                    max_freq = max(max_freq,amount)
                elif i > right or j < left:
                    continue
                elif left <= i and i <= right:
                    max_freq = max(max_freq,right-i+1)
                elif left <= j and j <= right:
                    max_freq = max(max_freq,j-left+1)
                else:
                    max_freq = max(max_freq,j-i+1)
            f.write(str(max_freq)+'\n')

def gen_test(n,q,max_reps):
    queries = []
    parts = []
    
    with open('test.cases','w') as f:
        f.write(str(n)+' '+str(q)+'\n')
        i = 0
        num = 0
        while num < n:
            reps = random.randint(1,max_reps)
            s = ''
            parts += [(num+1,num+reps,reps)]
            
            for j in range(reps):
                s += str(i)+' '
                
            if num+reps >= n:
                s = s[:-1]
                s +='\n'
            f.write(s)
            i = i+1
            num = num + reps
        
        for k in range(q):
            left = random.randint(1,n)
            right = random.randint(1,n)
            if left > right:
                tmp = right
                right = left
                left = tmp
                
            queries += [(left,right)]
            
            f.write(str(left)+' '+str(right)+'\n')
        f.write('0\n')
    calc_max_freqs(parts,queries)
        
    
    
if __name__ == '__main__':
    n = random.randint(1,100000)
    q = random.randint(1,100000)
    max_reps = 10000
    if len(sys.argv) == 4:
        n = int(sys.argv[1])
        q = int(sys.argv[2])
        max_reps = int(sys.argv[3])
    gen_test(n,q,max_reps)
