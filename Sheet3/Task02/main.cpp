#include <iostream>
#include <vector>
#include <bitset>
#include <limits>
#include <algorithm>

using namespace std;

double prob(vector<double> &probs,int k){
    vector<vector<double>> table(k,vector<double>(k,0.0));
    table[0][0] = 1-probs[0];
    table[0][1] = probs[0];

    for (int i = 1; i < k; ++i) {
        table[i][0] = (1-probs[i])*table[i-1][0];
        for (int j = 1; j < k; ++j) {
            table[i][j] = (1-probs[i])*table[i-1][j] + probs[i]*table[i-1][j-1];
        }
    }

    return table[k-1][k/2];
}

double find_max_prob(vector<double> &probs,int k){
    int n = probs.size();
    sort(probs.begin(),probs.end());

    double max_prob = 0.0;

    vector<double> probs2(k,0.0);
    for (int i = 0; i < k; ++i) {
        probs2[i] = probs[i];
    }

    max_prob = prob(probs2,k);

    int r = probs.size()-1;
    for (int j = k-1; j >= 0 ; j--) {
        probs2[j] = probs[r];
        r--;
        double tmp = prob(probs2,k);
        if (tmp > max_prob){
            max_prob = tmp;
        }
    }

    return max_prob;
}

int main() {

    int n = 0,k=0;

    cin >> n >> k;

    vector<double > probs(n,0);

    for (int i = 0; i < n; ++i) {
        double p = 0.0;
        cin >> p;
        probs[i] = p;
    }
    double max = find_max_prob(probs,k);
    cout.precision(2);
    cout << fixed << max;

    return 0;
}

