#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct edge {
    edge(int index,double capacity,double flow):index(index),capacity(capacity),flow(0.0){};
    int index;
    double capacity;
    double flow;
};
class node{
public:
    node():out(){};

    //index,capacity
    vector<edge> out;

    double get_sum_out_cap(){
        double sum = 0.0;
        for(auto const &e:out){
            sum+= e.capacity;
        }
        return sum;
    }
};

double bfs(int N,int start, int goal, const vector<node> &nodes,vector<int> &prev){

    queue<int > open;
    open.push(start);
    vector<bool> visited(N,false);
    visited[start] = true;
    bool found = false;

    while (open.size() > 0){
        int v = open.front();
        open.pop();

        if(v == goal){
            found = true;
            break;
        }

        for (auto &e: nodes[v].out) {
            if(!visited[e.index] && e.capacity - e.flow > 0){
                open.push(e.index);
                prev[e.index] = v;
                visited[e.index] = true;
            }
        }
    }
    if(!found){
        return -1;
    } else {
        return 0;
    }
}

double edmond_karp(int n,int source,int sink,vector<node> &nodes){
    vector<int> prev(n,-1);

    while(bfs(n,source,sink,nodes,prev) != -1){
        int v=prev[sink],w=sink;
        double df = numeric_limits<double >::max();
        while(v != -1) {
            for (auto &e: nodes[v].out) {
                if (e.index == w && e.capacity - e.flow < df) {
                    df = e.capacity - e.flow;
                }
            }
            w = v;
            v = prev.at(v);
        }
        v=prev[sink],w=sink;
        while(v != -1) {
            for (auto &e: nodes[v].out) {
                if (e.index == w) {
                    e.flow += df;
                }
            }
            w = v;
            v = prev.at(v);
        }

    }

    double flow = 0.0;
    for(auto &e: nodes[source].out){
        flow += e.flow;
    }

    return flow;

}

vector<int > read_sources_or_sinks(){
    int b;
    cin >> b;
    vector<int> ss(b,0);
    for (int j = 0; j < b; ++j) {
        cin >> ss[j];
        ss[j]++;
    }
    return ss;
}

int main() {

    int t = 0;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        //read in instance
        int m = 0,n = 0;
        cin >> n >> m;
        vector<node> nodes(n+2,node());
        vector<int> sources = read_sources_or_sinks();
        vector<int> sinks = read_sources_or_sinks();
        vector<double> sink_capacities(sinks.size(),0.0);

        for (int k = 0; k < m; ++k) {
            int v,w;
            double c;
            cin >> v >> w >> c;
            v++;
            w++;
            nodes[v].out.emplace_back(w,c,0.0);
            auto it = find(sinks.cbegin(),sinks.cend(),w);
            if(it != sinks.end()){
                sink_capacities[distance(sinks.cbegin(),it)] += c;
            }
        }

        //add single source and sink nodes and connect them to each source and sink
        for (auto const &v:sources) {
            nodes[0].out.emplace_back(v,nodes[v].get_sum_out_cap(),0.0);
        }
        for (int j = 0;j<sinks.size();j++) {
            nodes[sinks[j]].out.emplace_back(n+1,sink_capacities[j],0.0);
        }

        cout.precision(2);
        cout << fixed << edmond_karp(n+2,0,n+1,nodes) << endl;

    }

    return 0;
}