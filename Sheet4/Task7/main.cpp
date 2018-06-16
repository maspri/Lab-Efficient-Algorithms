#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
class mycomparison
{
public:
    bool operator() (const tuple<int,int> &a, const tuple<int,int> &b) const {
        return get<0>(a) < get<0>(b);
    }
};
//distance,index
typedef priority_queue<tuple<int,int >,vector<tuple<int,int >>,mycomparison> mypq;

struct edge{
    edge(int index,double capacity,double flow):index(index),capacity(capacity),flow(0.0){};
    int index;
    double capacity;
    double flow;
};


class node{
public:
    node():out(),excess(0),distance(0),is_in_queue(false){};

    //index,capacity
    vector<edge> out;
    double excess;
    int distance;
    bool is_in_queue;

    double get_sum_out_cap(){
        double sum = 0.0;
        for(auto const &e:out){
            sum+= e.capacity;
        }
        return sum;
    }
};


void augment(int v,int w,double &flow,double df,
             vector<node> &nodes){
    for(auto &ttt: nodes[w].out){
        if(ttt.index == v){
            ttt.flow -= df;
        }
    }

    flow += df;

    nodes[w].excess += df;
    nodes[v].excess -= df;
}

void push(int v, int w,
          double &capacity, double &flow,
          vector<node> &nodes, mypq &active_queue, int s, int t){
    double df = min(nodes[v].excess,capacity-flow);

    augment(v,w,flow,df,nodes);

    if(!nodes[w].is_in_queue && nodes[w].excess > 0 && w != t && w != s) {
        nodes[w].is_in_queue = true;
        active_queue.push(make_tuple(nodes[w].distance, w));
    }
    if(!nodes[v].is_in_queue && nodes[v].excess > 0 && v != t && v != s) {
        nodes[v].is_in_queue = true;
        active_queue.push(make_tuple(nodes[v].distance, v));
    }

}

/**
 *
 * @param v edge start index
 * @param w edge end index
 * @param capacity reference to the forward edge capacity
 * @param flow  reference to the forward edge flow
 * @param nodes
 * @param active_queue
 */
/*void augment(int v,int w,
             double &capacity,double &flow,
             vector<node> &nodes,mypq &active_queue,int s,int t){
    //note: we could just work with the minimum, then we
    // dont need the if - but i want to explicitly set capacity
    // to zero in the else branch so as to avoid numerical issues
    assert(nodes[v].excess != 0.0);
    assert(capacity != 0.0);

    double df = 0.0;
    if(nodes[v].excess <= capacity){
        df = nodes[v].excess;

        for(auto &ttt: nodes[w].out){
            if(ttt.index == v){
                ttt.capacity += df;
                ttt.flow -= df;
            }
        }

        flow += df;
        capacity -= df; // this is always >= 0

        nodes[w].excess += df;
        nodes[v].excess = 0.0;

        if(w != t && w != s) {
            active_queue.push(make_tuple(nodes[w].distance, w));
        }

    } else {
        df = capacity;

        for(auto &ttt: nodes[w].out){
            if(ttt.index == v){
                ttt.capacity += df;
                ttt.flow -= df;
            }
        }

        nodes[v].excess -= df;
        nodes[w].excess += df;

        flow += df;
        capacity = 0.0;

        if(v != t && v != s) {
            active_queue.push(make_tuple(nodes[v].distance, v));
        }
        if(w != t && w != s) {
            active_queue.push(make_tuple(nodes[w].distance, w));
        }
    }

}*/

double push_relabel(int n,int source,int sink,vector<node> &nodes){

    //active_queue contains the active nodes i.e. those with excess flow
    //priority is the distance function

    mypq active_queue;

    nodes[source].distance = n;
    nodes[source].excess = numeric_limits<double>::max();
    for (auto &e: nodes[source].out) {
        //augment flow by capacity
        push(source, e.index, e.capacity, e.flow, nodes, active_queue, source, sink);
    };

    int i=0,augment_steps=0,no_admissible_num=0;
    while(!active_queue.empty()){

        if(i % 100000 == 0){
            cout << i << " " << active_queue.size() << " " << augment_steps << " " << no_admissible_num << endl;
            augment_steps = 0;
            no_admissible_num = 0;
        }
        i++;

        //cout << nodes[8261].excess << " " << nodes[8261].distance << endl;

        tuple<int ,int > ac = active_queue.top();
        int active_node = get<1>(ac);
        node &n1 = nodes[active_node];
        active_queue.pop();
        nodes[active_node].is_in_queue = false;

        node &nnnnn = nodes[active_node];
        assert(nodes[active_node].excess > 0);
        assert(active_node != source);
        assert(active_node != sink);


        bool no_admissible = true;
        int min_dist = n+1;

        for(auto &e: nodes[active_node].out){
            if(nodes[active_node].distance == nodes[e.index].distance+1 && e.capacity - e.flow > 0.0){
                //we have found an admissible node
                no_admissible = false;

                //push
                if(active_node == 8261 || e.index == 8261){
                    cout << "" << endl;
                }
                push(active_node, e.index, e.capacity, e.flow, nodes, active_queue, source, sink);
                augment_steps++;

                break;
            } else if(nodes[e.index].distance < min_dist && e.capacity - e.flow > 0.0){
                min_dist = nodes[e.index].distance;
            }
        }

        if(no_admissible){
            //relabel active node
            nodes[active_node].distance = min_dist+1;

            //active node still has positive excess flow
            assert(nodes[active_node].excess > 0);
            active_queue.push(make_tuple(nodes[active_node].distance,active_node));

            no_admissible_num++;
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
    vector<node> nodes(n+2,node());

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
                    source = tmp;
                } else {
                    sink = tmp;
                }
                break;
            case 'a':
                iss >> v >> w >> cc;
                nodes[v].out.emplace_back(w,cc,0.0);
                nodes[w].out.emplace_back(v,0.0,0.0);
                break;

        }

    }
    cout << push_relabel(n,source,sink,nodes) << endl;

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

    read_dimacs();
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

        cout << push_relabel(n+2,0,n+1,nodes) << endl;

    }*/

    return 0;
}

