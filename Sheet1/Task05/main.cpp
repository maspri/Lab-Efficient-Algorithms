#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <chrono>

using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

using namespace std;

class center{
public:
    int x,y,i;
    center():x(100),y(100),i(100){}
    void set_coords(int i){
        this->i = i;
        x = i % 5;
        y = i / 5;
    }
    friend std::ostream& operator<< (std::ostream& stream, const center& center1) {
        stream << "i: " << center1.i << " x: " << center1.x << " y: " << center1.y << endl;
    }
};

class node
{
public:
    int x,y,p,id;
    center *nearest;
    int dist_to_nearest;
    node(int x,int y, int p,int id):
        x(x),
        y(y),
        p(p),
        id(id),
        nearest(nullptr),
        dist_to_nearest(10000) {}
};

int manhattan(const node &n1,const center &n2){
    return abs(n1.x - n2.x) + abs(n1.y - n2.y);
}


/*tuple<int,int> min_dist(const node &n1,const vector<node> &nodes,const vector<int> centers){
    int dist = numeric_limits<int>::max();
    int j = 0;
    for(int i=0;i<centers.size();i++){
        int d = manhattan(n1,nodes[centers[i]]);
        if(d < dist){
            dist = d;
            j=i;
        }
    }
    return make_tuple(dist,j);
}*/
/**
 *
 * @param cost aktuelle kosten
 * @param nodes alle mit personen besetze Felder
 * @param centers die aktuellen center
 * @param changedcenter das center das sich zuletzt geändert hat
 * @return
 */
int update(int cost,vector<node> &nodes,vector<center> &centers,center &changedcenter){
    for(node &n: nodes){
        //check if the center that changed was the nearest center of n
        if(n.nearest == &changedcenter){
            //if so find nearest center to n
            int mindist = numeric_limits<int>::max();
            int k = 0;

            for(int i = 0; i < centers.size(); ++i) {
                int nd = manhattan(n, centers[i]);
                if(nd < mindist){
                    mindist = nd;
                    k = i;
                }
            }

            cost = cost + (mindist - n.dist_to_nearest) * n.p;
            n.nearest = &centers[k];
            n.dist_to_nearest = mindist;

        } else {
            //otherwise we only need to check if the new center is closer than the current nearest
            int nd = manhattan(n, changedcenter);
            if (n.dist_to_nearest > nd) {
                cost = cost + (nd - n.dist_to_nearest) * n.p;
                n.nearest = &changedcenter;
                n.dist_to_nearest = nd;
            }
        }

    }
    return cost;
}
/**
 * verschachtelete 'for-schleife' um die zentrums kombinationen zu iterieren
 */
void iterate(int &mincost,
             int &cost,
             vector<node> &nodes,
             int start,
             int k,
             vector<center> &centers,
             vector<center> &centers_out/*,
             int &n*/){

    //base case - wir sind in der 5 for-schleife
    if(k == centers.size()-1){
        for (int i = start; i < 25; ++i) {
            centers[k].set_coords(i);
            int newcost = update(cost,nodes,centers,centers[k]);

            if(newcost < mincost){
                centers_out = centers;
                mincost = newcost;
            }

            cost = newcost;
            //n++;
        }
        //recusive case
    } else if (k < centers.size()){
        for (int i = start; i < 25; ++i) {
            centers[k].set_coords(i);
            int newcost = update(cost,nodes,centers,centers[k]);
            if(newcost < mincost){
                centers_out = centers;
                mincost = newcost;
            }
            cost = newcost;
            iterate(mincost,cost,nodes,i+1,k+1,centers,centers_out);
        }
    }
}

void calc_min(vector<node> &noodles){

    vector<center> centers(5);
    vector<center> centers_min(5);

    int mincost = numeric_limits<int>::max();
    int cost = 0;
    for (int i = 0; i < noodles.size(); ++i) {
        cost += noodles[i].dist_to_nearest*noodles[i].p;
    }
    int n = 0;

    //time_point<Clock> start = Clock::now();

    iterate(mincost,cost,noodles,0,0,centers,centers_min);

    //time_point<Clock> end = Clock::now();
    //milliseconds diff = duration_cast<milliseconds>(end - start);

    //cout << "n: " << n << endl;
    cout << mincost << endl;
    /*for(auto j : centers_min) {
        cout << j;
    }
    std::cout << diff.count() << "ms" << std::endl;*/
}

int main() {

    int n;
    char newline = '\0';

    cin >> n;

    for(int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        vector<node> nodes(k,node(0,0,0,0));
        //cout << k << endl;
        for(int j = 0;j<k;j++){
            cin >> nodes[j].x >> nodes[j].y >> nodes[j].p;
            //cout << nodes[j].x << " " << nodes[j].y << " " << nodes[j].p << endl;
        }

        calc_min(nodes);

    }
    /*vector<node> nodes1 = {{0,0,20,0},
                          {0,1,26,0},
                          {1,2,13,0},
                          {2,0,5,0},
                          {3,0,16,0},
                          {3,2,19,0},
                          {4,1,28,0},
                          {4,2,8,0}};
    vector<node> nodes2 = {{0,2,10,0},
                          {0,3,5,0},
                          {0,4,5,0},
                          {1,1,7,0},
                          {2,0,12,0},
                          {2,2,28,0},
                          {2,3,20,0},
                          {2,4,25,0},
                          {4,3,11,0},
                          {4,4,24,0}};

    calc_min(nodes1);
    calc_min(nodes2);*/


    return 0;
}
