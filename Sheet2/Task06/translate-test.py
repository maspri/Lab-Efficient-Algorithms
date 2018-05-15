import sys


def translate_single(n,edges):
    cedges = []
    for i in range(1,n+1):
        for j in range(i+1,n+1):
            if (i,j) in edges or (j,i) in edges:
                continue
            else:
                cedges += [(i,j)]
    return cedges
    

def translate(fs):
    
    with open('test.cases','w') as f:
        
        f.write(str(len(fs))+'\n')
        
        
        for ff in fs:
            edges = []
            graph = open(ff,'r')
            lines = graph.readlines()
            
            n,m = 0,0
            for line in lines:
                if line[0] == 'c':
                    continue
                elif line[0] == 'p':
                    asass, kjhg , sn, sm = line.split(' ')
                    n = int(sn)
                    
                    
                
                elif line[0] == 'e':
                    a,b = line[2:].split(' ')
                    
                    edges += [(int(a),int(b))]
                
            cedges = translate_single(n,edges)
            f.write(sn+' '+str(len(cedges))+'\n')
            
            for i,j in cedges:
                f.write(str(i)+' '+str(j)+'\n')
    
    
    
if __name__ == '__main__':
    translate(sys.argv[1:])
