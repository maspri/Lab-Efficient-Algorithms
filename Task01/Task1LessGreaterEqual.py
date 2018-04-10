f = open('Task1.txt', 'r')
cnt = f.readline()

for i in range(1, int(cnt)+1):  #range loops till < cnt not <= cnt
    txt = f.readline()
    a,b = txt.split()
    if int(a) == int(b):
        print('equal to')
    elif int(a) < int(b):
        print('less than')
    else:
        print('greater than')

