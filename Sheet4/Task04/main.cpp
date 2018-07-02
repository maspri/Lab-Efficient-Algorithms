#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <cmath>
#include <tuple>
#include <queue>
#include <set>
#include <fstream>
#include <sstream>

using namespace std;

class mycomparison
{
public:
    bool operator() (const pair<double,int> &a, const pair<double,int> &b) const {
        if(a.first != b.first) {
            return get<0>(a) < get<0>(b);
        } else {
            return get<1>(a) < get<1>(b);
        }
    }
};

void deleteshortest(int i,vector<vector<int >> &distances,
                    vector<vector<int>> &shortest_paths,
                    vector<bool> &can_use){
    can_use[i] = false;
    for (int j = 0; j < shortest_paths[i].size(); ++j) {
        distances[shortest_paths[i][j]][i] = -1;
        can_use[shortest_paths[i][j]] = false;
        if(shortest_paths[shortest_paths[i][j]].size() > 0) {
            deleteshortest(shortest_paths[i][j], distances, shortest_paths,can_use);
        }
    }
}
void deleteshortest2(int start,int goal,vector<vector<int >> &distances,
                    vector<int> dists,
                    vector<bool> &can_use){
    int n = distances.size();
    queue<int> q1;
    q1.push(goal);
    can_use[goal] = -1;
    while(!q1.empty()) {
        int k = q1.front();
        q1.pop();
        for (int i = 0; i < n; ++i) {
            if (distances[i][k] != -1) {
                if (dists[i] + distances[i][k] == dists[k]) {
                    distances[i][k] = -1;
                    can_use[i] = false;
                    if(i != start) {
                        q1.push(i);
                    }
                }
            }
        }
    }
}

int dijkstra(int N,int start, int goal, vector<vector<int >> &distances,vector<bool> &can_use){

    if(!can_use[start]){
        return -1;
    }
    set<pair<int,int>, mycomparison> open;
    open.insert(make_pair(0.0,start));
    vector<int> prev(N,-1);
    vector<int> dists(N,numeric_limits<int>::max());
    vector<vector<int>> shortest_paths(N,vector<int>());
    dists.at(start) = 0;

    while (open.size() > 0){
        const pair<int,int> pair1 = *open.cbegin();
        int current_node = pair1.second;

        /*if(current_node == goal){
            break;
        }*/
        open.erase(open.cbegin());

        for (int j = 0; j < N; ++j) {
            if(distances.at(current_node).at(j) != -1 && can_use[j]){
                int dist = dists.at(current_node) + distances.at(current_node).at(j);

                if (dist < dists.at(j)){
                    open.erase(make_pair(dists.at(j),j));
                    dists.at(j) = dist;
                    open.insert(make_pair(dists.at(j),j));
                    prev.at(j) = current_node;

                    shortest_paths[j].clear();
                    shortest_paths[j].push_back(current_node);
                } else if(dist == dists.at(j)){
                    shortest_paths[j].push_back(current_node);
                }
            }
        }
    }


    //delete shortest paths
    deleteshortest2(start,goal,distances,dists,can_use);

    if(dists.at(goal) == numeric_limits<int>::max()){
        return -1;
    } else {
        return dists.at(goal);
    }
}



int main() {

    int n = 1,m=1,home=0,cinema=0,workplace=0,gym=0;
    while(1) {
        cin >> n >> m;
        if(n == 0 && m == 0){
            break;
        }
        cin >> home >> cinema;
        cin >> workplace >> gym;

        vector<vector<int>> distances(n, vector<int>(n, -1));

        int v,w,c;
        for (int i = 0; i < m; ++i) {
            cin >> v >> w >> c;
            distances.at(v).at(w) = c;
        }
        vector<bool> can_use(n,true);
        dijkstra(n,workplace,gym,distances,can_use);
        cout << dijkstra(n,home,cinema,distances,can_use) << endl;
    }


    return 0;
}

