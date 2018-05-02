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
        print(math.ceil(m*n / 2))
    elif type == 'Q':
        # every queen has its own column, row and diagonal
        print(m)
    elif type == 'r':
        # place one rook on each diagonal
        print(m)
    else:
        kings = int(1 / 2 * (m + 1)) * int(1 / 2 * (n + 1))
        print(kings)
