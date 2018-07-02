#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <cmath>
#include <tuple>
#include <queue>
#include <set>

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

double dijkstra(int N,int start, int goal, const vector<vector<double >> &distances){

    set<pair<double,int>, mycomparison> open;
    open.insert(make_pair(0.0,start));
    vector<int> prev(N,-1);
    vector<double> dists(N,numeric_limits<double>::max());
    dists[start] = 0.0;

    while (open.size() > 0){
        const pair<double,int> pair1 = *open.cbegin();

        if(pair1.second == goal){
            break;
        }
        open.erase(open.cbegin());

        for (int j = 0; j < N; ++j) {
            if(distances[pair1.second][j] != -1) {
                double dist = dists[pair1.second] + distances[pair1.second][j];

                if (dist < dists[j]){
                    open.erase(make_pair(dists[j],j));
                    dists[j] = dist;
                    open.insert(make_pair(dists[j],j));
                    prev[j] = pair1.second;
                }
            }
        }
    }
    if(dists[goal] == numeric_limits<double>::max()){
        return -1;
    } else {
        return dists[goal];
    }
}

/*void dijkstra_transitive_edges(int N,int start,int capacity, int speed,
                                 vector<vector<int >> &distances,
                                 vector<vector<double >> &new_distances){

    set<pair<double,int>, mycomparison> open;
    open.insert(make_pair(0.0,start));
    vector<double> dists(N,numeric_limits<double>::max());
    dists[start] = 0.0;

    while (open.size() > 0){
        const pair<double,int> pair1 = *open.cbegin();
        open.erase(open.cbegin());

        for (int j = 0; j < N; ++j) {
            if(distances[pair1.second][j] != -1) {
                double dist = dists[pair1.second] + distances[pair1.second][j];

                if (dist < dists[j]){
                    open.erase(make_pair(dists[j],j));
                    dists[j] = dist;
                    open.insert(make_pair(dists[j],j));
                }
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        if((dists[i]/(double)speed) <= capacity) {
            new_distances[start][i] = (dists[i]/(double)speed);
        }
    }
}*/

vector<vector<double >> floyd_warshal_transitive_edges(int N,vector<vector<int>> &distances,
                                    vector<int> &capacities,
                                    vector<int> &speeds){
    vector<vector<double >> new_distances(N,vector<double>(N,numeric_limits<double>::max()));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if(distances[i][j] > 0) {
                new_distances[i][j] = (double) distances[i][j];
            }
        }
    }

    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if(new_distances[i][j] > new_distances[i][k] + new_distances[k][j]){
                    new_distances[i][j] = new_distances[i][k] + new_distances[k][j];
                }
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if(new_distances[i][j]/speeds[i] <= capacities[i]) {
                new_distances[i][j] = (double) new_distances[i][j]/speeds[i];
            } else {
                new_distances[i][j] = -1;
            }
        }
    }
    return new_distances;

}


int main() {

    int N = 0, Q = 0;
    cin >> N >> Q;
    vector<int> capacities(N, 0);
    vector<int> speeds(N, 0);
    vector<vector<int>> distances(N, vector<int >(N, 0));

    for (int i = 0; i < N; ++i) {
        cin >> capacities[i] >> speeds[i];
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> distances[i][j];
            /*double w = distances[i][j] / speeds[i];
            if (w > 0 && w < capacities[i]) {
                distances[i][j] = w;
            } else {
                distances[i][j] = -1.0;
            }*/
        }
    }

    vector<vector<double>> actual_distances = floyd_warshal_transitive_edges(N,distances,capacities,speeds);


    for (int k = 0; k < Q; ++k) {
        int v = 0, w = 0;
        cin >> v, cin >> w;
        cout.precision(2);
        cout << fixed << dijkstra(N, v - 1, w - 1, actual_distances) << " ";
    }


    return 0;
}

