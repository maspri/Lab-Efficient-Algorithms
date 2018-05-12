#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int mincoins(const vector<int> &coins, vector<int> &lookup,int V){

    if(V > 0 && lookup[V] != -2){

        return lookup[V];

    } else  if(V > 0){

        bool possible = false;
        int min = numeric_limits<int>::max();

        for (int i = 0; i < coins.size(); ++i) {
            if (coins[i] <= V){

                int num = mincoins(coins,lookup,V-coins[i]);

                if(num < min && num != -1){
                    possible = true;
                    min = num;
                }

            }

        }
        if(possible){
            lookup[V] = 1 + min;
            return 1 + min;
        } else{
            lookup[V] = -1;
            return -1;
        }

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
        vector<int> lookup(V*V+1,-2);
        vector<int> nonzerocoins;
        nonzerocoins.reserve(coins.size());



        for(int j=0;j<k;j++){

            int b=0,e=0;
            cin >> b >> e;
            coins[j] = b*b+e*e;

        }

        for (int l = 0; l < coins.size(); ++l) {
            if (coins[l] > 0) {
                nonzerocoins.push_back(coins[l]);
            }
        }


        int num = mincoins(nonzerocoins,lookup,V*V);


        if(num == -1){
            cout << "impossible" << endl;
        } else {
            cout << num << endl;
        }
    }


    return 0;
}

