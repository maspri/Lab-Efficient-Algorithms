import math

cnt = int(input())
for i in range(1, cnt+1):
    type, m, n = input().split()

    m = int(m)
    n = int(n)

    # turn chess board to keep #rows smaller than #columns
    if m > n:
        tmp = m
        m = n
        n = tmp

    if type == 'k':
        # knights placed on all dark or white squares
        print(int(m*n / 2))
    elif type == 'Q':
        # every queen has its own column, row and diagonal
        print(m)
    elif type == 'r':
        # place one rook on each diagonal
        print(m)
    else:
        # divide chess board in quadratic boards
        sub_boards = n % m
        # columns of the remaining board part
        new_n = n - m * sub_boards

        kings = sub_boards*m**2 / 4
        # each king can be placed on a 2*2 square
        kings += math.ceil(new_n / 2) * m/2
        '''remaining chess board kings
        example 4*7
        0 0 0 0   0 0 0
        1 0 1 0   1 0 1
        0 0 0 0   0 0 0
        1 0 1 0   1 0 1
        
        a row can have m/2 kings
        every second column is empty
        if new_n is even  new_n/2 gets the number of columns in which kings are positioned
        if new_n is odd the ceiling of .5 to the next integer yields the correct amount
        '''
        print(int(kings))
