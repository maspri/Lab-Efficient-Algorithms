import random
import sys
import functools
import itertools

def gen_parts(height, width, max_people, occupied_prob):
    parts = []
    for i in range(height):
        for j in range(width):
            if random.random() > occupied_prob:
                p = random.randint(1, max_people)
                parts += [(i,j,p)]

    return parts


def manhattan(p1,p2):
    return abs(p1[0]-p2[0])+abs(p1[1]-p2[1])

def calc_costs(dims, parts, places):
    cost = 0.0
    for part in parts:
        dist = min(map(functools.partial(manhattan,part),places))
        cost += dist*part[2]
    return cost

def min_cost(dims,parts):
    cost = 10000000
    for places in itertools.combinations(range(dims[0]*dims[1]),5):
        real_places = []
        for place in places:
            x = place % dims[0]
            y = place // dims[0]
            real_places+=[(x,y)]
        dcost = calc_costs(dims,parts,real_places)
        if dcost < cost:
            cost = dcost
    return cost


def find_part(i,j,parts):
    for x,y,p in parts:
        if i == x and j == y:
            return p
    return 0

def print_parts(dims, parts,outfile):
    for i in range(dims[0]):
        for j in range(dims[1]):
            outfile.write('{0: <2}'.format(find_part(i,j,parts))+'|')
        outfile.write('\n')

def read_parts(filename):
    f = open(filename,'r')
    n = int(f.readline())
    parts = []
    for i in range(n):
        x,y,p = map(int, f.readline().split())
        parts += [(x,y,p)]

    return parts


def print_parts_to(parts,outfile):
    n = len(parts)
    outfile.write(str(n)+'\n')
    for i,j,p in parts:
        outfile.write(str(i)+" "+str(j)+" "+str(p)+'\n')

def gen_test_cases(max_height,max_width,max_people,n,occupied_prob):
    f1 = open('test.cases','w')
    f2 = open('test.results','w')
    f3 = open('test.cases_visual','w')
    f1.write(str(n)+'\n')
    for i in range(n):
        height = random.randint(1,max_height)
        width = random.randint(1,max_width)
        parts = gen_parts(height,width,max_people,occupied_prob)

        print_parts_to(parts,f1)

        print_parts((height,width),parts,f3)
        print_parts((height,width),parts,sys.stdout)
        print()


        cost = min_cost((height,width),parts)

        f2.write(str(int(cost))+'\n')
        f3.write(str(int(cost))+'\n')


    f1.close()
    f2.close()
    f3.close()


def do_test():
    parts = read_parts('test1')
    print_parts((5, 3), parts, sys.stdout)
    print('min_cost: ', min_cost((5, 3), parts))
    print()

    parts = read_parts('test2')
    print_parts((5, 5), parts, sys.stdout)
    print('min_cost: ', min_cost((5, 5), parts))
    print()

if __name__ == '__main__':

    #this is to test the correctness of the brute-force mincost finder
    #do_test()

    if len(sys.argv == 6):
        gen_test_cases(int(sys.argv[1]),int(sys.argv[2]),int(sys.argv[3]),int(sys.argv[4]),float(sys.argv[5]))
    else:
        gen_test_cases(7, 7, 30, 5, 0.5)
