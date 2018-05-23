import random
import itertools
import numpy as np

def find_costs(dists,s):
        sum_f = dists[0]
        sum_f_start_index = 0
        max_f_so_far = dists[0]
        sum_b = dists[0]
        sum_b_start_index = 0
        max_b_so_far = dists[0]

        for i, si in enumerate(s):
            if si == 1:
                sum_f_start_index = i + 1
                sum_f = dists[i + 2] - dists[sum_f_start_index]

                sum_b = dists[i + 2] - dists[sum_b_start_index]
            else:
                sum_b_start_index = i + 1
                sum_b = dists[i + 2] - dists[sum_b_start_index]

                sum_f = dists[i + 2] - dists[sum_f_start_index]

            max_f_so_far = max(max_f_so_far, sum_f)
            max_b_so_far = max(max_b_so_far, sum_b)

        # print(s)
        # print(max(max_b_so_far,max_f_so_far))
        return max(max_b_so_far, max_f_so_far)
    

def find_opt(dists):
    minmax = 10000000
    if len(dists) == 1:
        return dists[0]
    dists = np.insert(dists, 0, 0)
    for s in itertools.product([0, 1], repeat=len(dists) - 2):
        m = find_costs(dists,s)
        # print(s)
        # print(max(max_b_so_far,max_f_so_far))
        if m < minmax:
            minmax = m
    print(minmax)
    return minmax

def gen_test(num):
    for k in range(num):

        with open('test.cases.' + str(k), 'w') as f1, open('test.results.' + str(k), 'w') as f2:
            maximum = 0
            D = 0
            floes = []
            num_big_floes = random.randint(1,10)
            num_floes = num_big_floes-1
            for l in range(num_big_floes):
                num_tmp_floes = random.randint(0,13)
                D_tmp = 0
                dists_tmp = np.zeros(num_tmp_floes + 1)
                # ds = [10,2,2,3,8,12]
                for i in range(num_tmp_floes + 1):
                    d = random.randint(1, 200)
                    D_tmp += d
                    dists_tmp[i] = D_tmp
                opt = find_opt(dists_tmp)
                
                if(opt > maximum):
                    print(opt)
                    maximum = opt
                
                num_floes += num_tmp_floes
                
                for i in range(num_tmp_floes):
                    floes += ['s '+str(int(D+dists_tmp[i])) + '\n']
                    
                if(l < num_big_floes-1):
                    floes += ['b '+str(int(D+dists_tmp[num_tmp_floes])) + '\n']
                D += D_tmp
                    
            f1.write(str(num_floes) + ' ' + str(D)+'\n')
            for i in range(num_floes):
                f1.write(floes[i])
            f2.write(str(int(maximum)))


if __name__ == '__main__':
    gen_test(10)
