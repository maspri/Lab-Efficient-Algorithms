#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;
int blergh(const vector<int> &coins,int coinIndex,int V);

vector<int> lookup;

bool myfunction (int i,int j) { return (i>j); }

int mblergh(const vector<int> &coins,int coinStart,int V){
    if(lookup[V] != -1){
        return lookup[V];
    } else {
        int num = blergh(coins,coinStart,V);
        lookup[V] = num;
        return num;
    }
}

int blergh(const vector<int> &coins,int coinIndex,int V){
    if(V > 0 && coinIndex < coins.size()){
        //try biggest number of largest coin first
        int n  = V / coins[coinIndex];
        for (int j = n; j >= 0; --j) {
            int num = mblergh(coins,coinIndex+1, V - j*coins[coinIndex]);
            if(num >= 0){
                return j + num;
            }
        }
        return -1;

    } else if ( V > 0 && coinIndex == coins.size()) {

        return -1;

    } else {

        return 0;

    }
}


int main() {

    int n = 0;
    cin >> n;
    for(int i=0;i<n;i++){
        int k=0,V=0;
        cin >> k >> V;
        vector<int> coins(k,0);
        lookup = vector<int>(V*V,-1);
        for(int j=0;j<k;j++){

            int b=0,e=0;
            cin >> b >> e;
            coins[j] = b*b+e*e;

        }
        sort(coins.begin(),coins.end(),myfunction);

        vector<int> nonzerocoins;
        nonzerocoins.reserve(coins.size());

        for (int l = 0; l < coins.size(); ++l) {
            if (coins[i] > 0)
                nonzerocoins.push_back(coins[i]);
        }

        int num = blergh(nonzerocoins,0,V*V);
        if(num == -1){
            cout << "impossible" << endl;
        } else {
            cout << num << endl;
        }
        //lookup.clear();
    }


    return 0;
}

