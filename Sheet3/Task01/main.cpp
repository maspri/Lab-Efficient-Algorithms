#include <iostream>
#include <vector>
#include <bitset>
#include <limits>

using namespace std;

int calc_max(int i,int left,int right,vector<int> &dists,
             int max_f_so_far,int sum_f,int sum_f_start_index,
             int max_b_so_far,int sum_b,int sum_b_start_index) {

    if (max_f_so_far < max_b_so_far) {
        sum_f_start_index = i + 1;
        sum_f = dists[i + 2] - dists[sum_f_start_index];

        sum_b = dists[i + 2] - dists[sum_b_start_index];
    } else {
        sum_b_start_index = i + 1;
        sum_b = dists[i + 2] - dists[sum_b_start_index];

        sum_f = dists[i + 2] - dists[sum_f_start_index];


    }
    max_f_so_far = max(max_f_so_far, sum_f);
    max_b_so_far = max(max_b_so_far, sum_b);
}

int main() {
    int n = 0,D=0;
    cin >> n >> D;
    vector<int> dists(n+2,0);
    vector<int> large;
    for (int i = 0; i < n; ++i) {
        int d = 0;
        char t;
        cin >> t >> d;
        dists[i] = d;
        if (t == 'b'){
            large.push_back(i);
        }
    }
    dists[n+1] = D;

    int max = 0;
    for (int j = 0; j < large.size()-1; ++j) {
        int m = calc_max(large[j],large[j+1],dists);
        if(m > max){
            max = m;
        }
    }

    cout << max << endl;



    return 0;
}

