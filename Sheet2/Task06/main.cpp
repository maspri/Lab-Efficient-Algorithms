#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

bool comp(const pair<int,int> &lhs,const pair<int,int> &rhs){
    return get<0>(lhs) > get<0>(rhs);
}

int mis(vector<vector<bool >> &adjacency,
        vector<int > &mask,
        int n,
        int current_is_size,
        int max_so_far){
    if(n <= 1) {
        //return if |G| <= 1
        return n;
    } else if(n+current_is_size <= max_so_far){
        //cut rule
        return 0; //doesnt matter
    } else {
        int i = 0;
        int d = 0;
        //find maximum degree node
        for (int k = 0; k < adjacency.size(); ++k) {
            if(!mask.at(k)){
                int tmp = 0;
                for (int j = 0; j < adjacency.size(); ++j) {
                    if (!mask.at(j) && adjacency.at(k).at(j) && j != k) tmp++;
                }
                if (tmp > d){
                    d = tmp;
                    i = k;
                }
            }
        }

        //go through neighbors of i
        //note that by increasing mask even for excluded neighbors,
        //we can do the reverse easily
        for (int j = 0; j < adjacency.size(); ++j) {
            //if j is neighbor of i
            if(adjacency.at(i).at(j)) {
                //if j has not already been excluded
                mask.at(j)++;
            }
        }

        int with_i = mis(adjacency,mask,n-d-1,current_is_size+1,max_so_far);


        for (int j = 0; j < adjacency.size(); ++j) {
            if(adjacency.at(i).at(j)) {
                mask.at(j)--;
            }
        }

        //nodes with degree one or zero can always be selected.
        //i.e. we don't need to consider the other case
        if(d == 1 || d == 0){
            return 1 + with_i;
        }

        mask.at(i)++;

        int without_i = mis(adjacency,mask,n-1,current_is_size,max(current_is_size+1+with_i,max_so_far));

        mask.at(i)--;

        return max(1+with_i,without_i);
    }
}

/**
 * Select single vertices.
 * @param adjacency adjacency matrix
 */
/*int select_single(vector<vector<bool >> &adjacency,
                  vector<int> &mask,
                  vector<int> &degrees) {
    int num_selected = 0;
    for (int j = 0; j < adjacency.size(); ++j) {
        if (degrees[j] == 0) {
            num_selected++;
            mask[j]++;
        }
    }
    return num_selected;
}

void remove_dominated(vector<vector<bool >> &adjacency,
                     vector<int> &mask,
                     vector<int> &degrees){

    int n = degrees.size();

    vector<pair<int,int> > considered(n, {0,0});
    for (int l = 0; l < n; ++l) {
        get<0>(considered[l]) = degrees[l];
        get<1>(considered[l]) = l;
    }

    sort(considered.begin(),considered.end(),comp);

    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            bool superset = true;
            for (int k = 0; k < n; ++k) {
                //test if N[i] c N[j]
                // thus if k is not a neighbor of i but of j we can break
                if(!(!adjacency[get<1>(considered[i])][k] && adjacency[get<1>(considered[j])][k])){
                    superset = false;
                    break;
                }
            }
            if (superset){
                mask[get<1>(considered[i])]++;
                for (int k = 0; k < n; ++k) {
                    if (adjacency[get<1>(considered[i])][k]){
                        degrees[k]--;
                    }
                }
            }
        }
    }
}*/


void read_and_do_mis(){
    int n=0,m=0;
    cin >> n >> m;

    vector<vector<bool >> adjacency(n,vector<bool >(n, false));
    vector<int> mask(n,0);
    vector<int> degrees(n,0);

    for (int j = 0; j < m; ++j) {
        int v=0,w=0;

        cin >> v >> w;
        v--;
        w--;

        adjacency[v][w] = true;
        adjacency[w][v] = true;

        degrees[v]++;
        degrees[w]++;

    }

    for (int k = 0; k < n; ++k) {
        adjacency[k][k] = true;
    }


    //clock_t startTime = clock();

    //int num_selected = select_single(adjacency,mask,degrees);
    int max = mis(adjacency,mask,adjacency.size(),0,0);

    //cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;

    cout << max << endl;
}

int main() {

    int t = 0;
    cin >> t;

    for(int i=0;i<t;i++){
        read_and_do_mis();
    }

    return 0;
}

