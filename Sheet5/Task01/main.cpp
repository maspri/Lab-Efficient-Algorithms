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

double edmond_karp(int n,int source,int sink,vector<node> &nodes){

    vector<int> prev(n,-1);
    while(bfs(n,source,sink,nodes,prev) != -1){
        //augment along the path we found
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




int main() {


    while(1) {
        //read in instance
        int B = 0,S = 0;
        cin >> B >> S;

        if(B==0 && S == 0){
            break;
        }

        /**
         * Transformation to max flow, given Graph G = (V,E) as described in the task:
         * For each node v except for 1 and B add a new node v'. All outgoing
         * edges are moved to v' i.e. if (v,w) \in E(G) we add (v',w) and remove (v,w).
         * Add two edges (v,v') and (v',v) with capacity set to the cost of destruction of
         * v.
         */
        vector<node> nodes(2*B,node());

        for (int l = 0; l < B-2; ++l) {
            int node,cost;
            cin >> node >> cost;
            node--;
            nodes[node].out.emplace_back(node+B,cost,0.0);
            nodes[node+B].out.emplace_back(node,cost,0.0);
        }

        nodes[0].out.emplace_back(B,nodes[B].get_sum_out_cap(),0.0);

        for (int k = 0; k < S; ++k) {
            int v,w;
            double c;
            cin >> v >> w >> c;
            v--;
            w--;
            nodes[v+B].out.emplace_back(w,c,0.0);
            nodes[w+B].out.emplace_back(v,0.0,0.0);
        }

        cout.precision(0);
        cout << fixed << edmond_karp(2*B,B,B-1,nodes) << endl;

    }

    return 0;
}