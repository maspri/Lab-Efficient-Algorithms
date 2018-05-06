#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class element{
public:
    element():parent(nullptr),rank(0){}
    element *parent;
    int rank;
};

element* _find(element *v){
    if(v->parent == nullptr){
        return v;
    } else {
        //v->parent = _find(v->parent);
        return _find(v->parent);
    }
}
 void _union(element *v,element *w){
     element *rootv = _find(v);
     element *rootw = _find(w);

    if (rootv != rootw){
        if(rootv->rank == rootw->rank){
            rootw->parent = rootv;
            rootv->rank++;
        } else if (rootv->rank > rootw->rank){
            rootw->parent = rootv;
        } else{
            rootv->parent = rootw;
        }
    }
}


int main() {

    int t = 0;
    cin >> t;

    for(int i=0;i<t;i++){
        int n=0,num_events=0;
        cin >> n >> num_events;

        vector<element> elements(n+1,element());
        int success=0,fail=0;

        for (int j = 0; j < num_events; ++j) {
            char event_type = '\0';
            int v=0,w=0;
            cin >> event_type >> v >> w;

            if(event_type == 'n'){
                _union(&elements[v],&elements[w]);
            } else if (event_type == 'q'){
                if (_find(&elements[v]) == _find(&elements[w])){
                    //cout << "q " << v << " " << w << " success" << endl;
                    success++;
                } else {
                    //cout << "q " << v << " " << w << " fail" << endl;
                    fail++;
                }
            }

        }

        cout << success << " " << fail << endl;
    }


    return 0;
}

