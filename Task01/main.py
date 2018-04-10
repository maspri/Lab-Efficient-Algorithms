import sys

t = int(input())

for i in range(t):
    a,b = map(int,input().split())
    if  a < b:
        print("less than")
    elif a > b:
        print("greater than")
    else:
        print("equal to")

