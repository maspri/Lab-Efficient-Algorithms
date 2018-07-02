#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <fstream>
#include <sstream>
#include <string>
#include <assert.h>

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

void augment(int v,int w,double &flow,double df,
             vector<node> &nodes){
    for(auto &ttt: nodes[w].out){
        if(ttt.index == v){
            ttt.flow -= df;
        }
    }

    flow += df;
}

double augment_along_path(vector<int> prev,int w,double min_df,vector<node> &nodes){
    int v = prev[w];
    for (auto &e: nodes[v].out) {
        if (e.index == w  ) {
            if(e.capacity - e.flow > 0.0 && e.capacity - e.flow < min_df) {
                min_df = augment_along_path(prev, v, e.capacity - e.flow, nodes);
            } else{
                min_df = augment_along_path(prev, v, min_df, nodes);
            }
            augment(v,w,e.flow,min_df,nodes);
            return min_df;
        }
    }
}


double edmond_karp(int n,int source,int sink,vector<node> &nodes){

    vector<int> prev(n,-1);
    while(bfs(n,source,sink,nodes,prev) != -1){
        int v=prev[sink],w=sink;
        double df = numeric_limits<double >::max();
        while(v != -1) {
            for (auto &e: nodes[v].out) {
                if (e.index == w && e.capacity - e.flow > 0 &&  e.capacity - e.flow < df) {
                    df = e.capacity - e.flow;
                }
            }
            w = v;
            v = prev.at(v);
        }
        v=prev[sink],w=sink;
        while(v != -1) {
            for (auto &e: nodes[v].out) {
                if (e.index == w && e.capacity - e.flow > 0) {
                    augment(v,w,e.flow,df,nodes);
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

void read_dimacs(){
    ifstream infile("../104_0412_16bins.max");
    std::string line;
    int n,m;

    while (std::getline(infile, line))
    {
        istringstream iss(line);
        char c;
        iss >> c;

        if(c == 'p') {
            for (int i = 0; i < 3; ++i) {
                iss >> c;
            }
            iss >> n >> m;
            break;
        }
    }


    int source,sink;
    vector<node> nodes(n,node());

    while (std::getline(infile, line))
    {
        istringstream iss(line);
        char c;
        iss >> c;
        int v,w,cc;
        switch (c){
            case 'c':
                break;
            case 'n':
                int tmp;
                char which;
                iss >> tmp >> which;
                if(which == 's'){
                    source = tmp-1;
                } else {
                    sink = tmp-1;
                }
                break;
            case 'a':
                iss >> v >> w >> cc;
                nodes[v-1].out.emplace_back(w-1,cc,0.0);
                nodes[w-1].out.emplace_back(v-1,0.0,0.0);
                break;

        }

    }
    cout << edmond_karp(n,source,sink,nodes) << endl;

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

    /*int t = 0;
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
            nodes[w].out.emplace_back(v,0.0,0.0);
            auto it = find(sinks.cbegin(),sinks.cend(),w);
            if(it != sinks.end()){
                sink_capacities[distance(sinks.cbegin(),it)] += c;
            }
        }

        //add single source and sink nodes and connect them to each source and sink
        for (auto const &v:sources) {
            nodes[0].out.emplace_back(v,nodes[v].get_sum_out_cap(),0.0);
            nodes[v].out.emplace_back(0,0.0,0.0);
        }
        for (int j = 0;j<sinks.size();j++) {
            nodes[sinks[j]].out.emplace_back(n+1,sink_capacities[j],0.0);
            nodes[n+1].out.emplace_back(sinks[j],0.0,0.0);
        }

        cout.precision(2);
        cout << fixed << edmond_karp(n+2,0,n+1,nodes) << endl;

    }*/

    read_dimacs();

    return 0;
}