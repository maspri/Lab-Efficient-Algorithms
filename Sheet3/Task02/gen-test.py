import random
import itertools
import numpy as np
import math

def find_max_prob(probs,k):
    n = len(probs)
    
    max_prob = 0
    max_committee = []
    ovar = 0
    for commitee in itertools.combinations(probs, k):
        var = sum(map(lambda p: p-p*p,commitee))
        expected = sum(commitee)
        delta1 = (k//2+0.5)/expected-1.0
        delta2 = 1-(k//2-0.5)/expected
        #print(1-var/(k//2+0.5-expected))
        #print(expected,var)#,math.exp(-expected*delta1*delta1/3.0),math.exp(-expected*delta2*delta2/2.0),commitee)
        print(expected,var)
        
        prob = 0.0
        for s in itertools.product([0, 1], repeat=k): 
            ones = 0
            tmp = 1.0
            for i,p in enumerate(commitee):
                if s[i] == 1:
                    ones += 1
                    tmp *= p
                else:
                    tmp *= (1.0-p)
                    
            if ones == k//2:
                prob += tmp
        if prob > max_prob:
            max_prob = prob
            max_committee = commitee
            ovar = var
    print(max_prob,max_committee,ovar)
    return max_prob,max_committee
        
        

def gen_test(num):
    for k in range(num):
        numberstr = ''
        if k < 10:
            numberstr = '0'+str(k)
        else:
            numberstr = str(k)
        with open('test.cases.' + numberstr, 'w') as f1, open('test.results.' + numberstr, 'w') as f2:
            n = 5#random.randint(2,15)
            k = random.randint(1,n//2)*2
            probs = np.zeros(n)
            f1.write(str(n)+' '+str(k)+'\n')
            for i in range(n):
                tmp = random.randint(0,100)/100.0
                probs[i] = float('{:0.2f}'.format(tmp))
                f1.write('{:0.2f}\n'.format(tmp))
            max_prob,max_committee = find_max_prob(probs,k)
            f2.write('{:0.2f}'.format(max_prob)+'\n')
            f2.write('('+','.join(map(str,max_committee))+')')
                

if __name__ == '__main__':
    #gen_test(1)
    #print(find_max_prob([0.43,0.51,0.05,0.43,0.28],4))
    print(find_max_prob([0.1,0.3,0.9,0.6,0.5,0.3,0.9,0.5],4))
