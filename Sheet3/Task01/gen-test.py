import random
import itertools
import numpy as np


def find_opt(dists):
    minmax = 10000000
    dists = np.insert(dists, 0, 0)
    for s in itertools.product([0, 1], repeat=len(dists) - 2):
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

        if max(max_b_so_far, max_f_so_far) < minmax:
            minmax = max(max_b_so_far, max_f_so_far)
    print(minmax)
    return minmax


def gen_test(num, num_floes):
    for k in range(num):

        with open('test.cases.' + str(k), 'w') as f1, open('test.results.' + str(k), 'w') as f2:
            D = 0
            dists = np.zeros(num_floes + 1)
            # ds = [10,2,2,3,8,12]
            for i in range(num_floes + 1):
                d = random.randint(1, 10)
                D += d
                dists[i] = D
            opt = find_opt(dists)

            f1.write(str(num_floes) + ' ' + str(D)+'\n')
            for i in range(num_floes):
                f1.write('s '+str(int(dists[i])) + '\n')
            f2.write(str(int(opt)))


if __name__ == '__main__':
    gen_test(10,7)
