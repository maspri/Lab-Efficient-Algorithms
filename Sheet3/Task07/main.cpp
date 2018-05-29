#include <iostream>
#include <vector>
#include <bitset>
#include <limits>
#include <algorithm>
#include <tuple>
#include <queue>
#include <cmath>

using namespace std;
class element{
public:
    element():parent(nullptr),rank(0),x(0),y(0){}
    element *parent;
    int rank;
    int x;
    int y;
    double dist(const element *other){
        return sqrt((other->x - x)*(other->x - x)+(other->y -y)*(other->y -y));
    }
};

bool mycomp(const tuple<double,element*,element*> &a,const tuple<double,element*,element*> &b){
    return get<0>(a) < get<0>(b);
}

class mycomparison
{
public:
    bool operator() (const tuple<double,element*,element*> &a,const tuple<double,element*,element*> &b) const {
        return get<0>(a) > get<0>(b);
    }
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

    int n = 0,m=0;

    cin >> n >> m;
    vector<element> elements(n,element());
    int num_connected_components = n;

    for (int i = 0; i < n; ++i) {
        int x=0,y=0;
        cin >> x >> y;
        elements[i].x = x;
        elements[i].y = y;
    }

    for (int i = 0; i < m; ++i) {
        int v=0,w=0;
        cin >> v >> w;
        v--;
        w--;
        if (_find(&elements[v]) != _find(&elements[w])){
            _union(&elements[v],&elements[w]);
            num_connected_components--;
        }
    }

    vector<tuple<double,element*,element*>> skrrt;
    skrrt.reserve(n*n);
    for (int i = 0; i < n-1; ++i) {
        for (int j = i+1; j < n; ++j) {
            skrrt.push_back(make_tuple(elements[i].dist(&elements[j]),&elements[i],&elements[j]));
        }
    }

    priority_queue<tuple<double,element*,element*>,vector<tuple<double,element*,element*>>,mycomparison>
            queue1(skrrt.begin(),skrrt.end());

    double max_dist = 0;
    while(num_connected_components > 1) {
        auto &tp = queue1.top();
        if (_find(get<1>(tp)) != _find(get<2>(tp))){
            double tmp = get<1>(tp)->dist(get<2>(tp));

            if(tmp > max_dist){
                max_dist = tmp;
            }
            num_connected_components--;
            _union(get<1>(tp),get<2>(tp));
        }
        queue1.pop();
    }

    cout.precision(3);
    cout << fixed << max_dist << endl;

    return 0;
}

