#include <iostream>
#include <vector>
#include <bitset>
#include <limits>
#include <algorithm>

using namespace std;

double prob(vector<double> &probs,int j,int kh){
    if (j == probs.size()-1 && kh == 0){
        return 1-probs[j];
    } else if(j == probs.size()-1 && kh == 1){
        return probs[j];
    } else if(j < probs.size() && kh == 0){
        return (1 - probs[j]) * prob(probs, j + 1, kh);
    } else if(probs.size() - j == kh){
        return probs[j] * prob(probs, j + 1, kh - 1);
    } else {
        return probs[j] * prob(probs, j + 1, kh - 1) + (1 - probs[j]) * prob(probs, j + 1, kh);
    }
}

double find_max_prob(vector<double> &probs,int k){
    int n = probs.size();
    sort(probs.begin(),probs.end());

    vector<double > probs2;
    for (int i = 0; i < k/2; ++i) {
        probs2.push_back(probs[i]);
        probs2.push_back(probs[n-i-1]);
    }

    return prob(probs2,0,k/2);

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
    cout << max;

    return 0;
}

