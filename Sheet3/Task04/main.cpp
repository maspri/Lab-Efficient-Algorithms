#include <iostream>
#include <vector>
#include <bitset>
#include <limits>
#include <algorithm>
#include <cmath>
#include <tuple>

using namespace std;


float dist(const tuple<int, int> &a,const tuple<int, int> &b){
    return sqrt((get<0>(a)-get<0>(b))*(get<0>(a)-get<0>(b))+(get<1>(a)-get<1>(b))*(get<1>(a)-get<1>(b)));
}
/**
 * enumerates subsets of size s
 * @param s
 * @param k
 * @param N
 * @param subset
 * @param nodes
 * @param mem
 */
void enumerate_subsets_s(int s, int k, int N, int subset, const vector<tuple<int, int>> &nodes, vector<vector<float >> &mem){
    if(s > 0) {
        for (int i = k; i < N-s+1; ++i) {
            enumerate_subsets_s(s - 1, i+1, N, subset | (1 << i), nodes, mem);
        }
    } else {
        for (int i = 1; i < N; ++i) {
            if(subset & (1 << i)){

                float min = numeric_limits<float>::max();
                for (int j = 0; j < N; ++j) {
                    if(subset & (1 << j) && j != i){
                        float tmp = mem.at(subset & ~(1 << i)).at(j) + dist(nodes.at(i),nodes.at(j));
                        if (tmp < min){
                            min = tmp;
                        }
                    }
                }

                mem.at(subset).at(i) = min;
            }
        }
    }
}

float tsp(const vector<tuple<int,int>> &nodes){
    int N =  nodes.size();
    //we can be wasteful as N <= 14
    int num_subsets = (int)pow(2.0,N);
    //mem[subset][k] is the length of the minimum path starting at node 1, visiting all nodes in
    // the subset and ending at node k
    vector<vector<float >> mem(num_subsets,vector<float >(N,numeric_limits<float>::max()));
    for (int i = 1; i < N; ++i) {
        mem.at((1 << i)).at(i) = dist(nodes.at(0),nodes.at(i));
    }

    for (int s = 2; s <= N-1; ++s) {
        enumerate_subsets_s(s,1,N,0,nodes,mem);
    }

    float min = numeric_limits<float>::max();
    int all_except_first = (0xFFFFFFFF >> (32-N)) & ~1;
    for (int j = 1; j < N; ++j) {
            float tmp = mem.at(all_except_first).at(j);
            if (tmp < min){
                min = tmp;
            }
    }

    return min;
}

int main() {

    int P=0;

    while(1){
        cin >> P;
        if(P == 0 ){
            break;
        }

        vector<tuple<int ,int>> piles(P,make_tuple(0,0));
        int v=0,w=0;
        for (int i = 0; i < P; ++i) {
            cin >> v >> w;
            get<0>(piles.at(i)) = v;
            get<1>(piles.at(i)) = w;
        }

        float dist = tsp(piles)+(P-1)*8*2;
        cout.precision(2);
        cout << fixed << dist << endl;
    }


    return 0;
}

