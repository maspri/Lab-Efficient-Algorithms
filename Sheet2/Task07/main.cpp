#include <iostream>
#include <vector>
#include <limits>
#include <map>

using namespace std;
int blergh(const vector<int> &coins,int V);

map<int,int> lookup;

int mblergh(const vector<int> &coins,int V){
    map<int,int>::iterator it;
    it = lookup.find(V);
    if(it != lookup.end()){
        return get<1>(*it);
    } else {
        return blergh(coins,V);
    }
}

int blergh(const vector<int> &coins,int V){
    if(V > 0){
        int mincoins = numeric_limits<int>::max();
        int impossible = 0;
        for(int i=0;i<coins.size();i++){
            if(coins[i] <= V){
                int num = mblergh(coins, V - coins[i]);
                if(num < mincoins){
                    mincoins = num;
                }
            } else {
                impossible++;
            }
        }
        if(impossible == coins.size()){
            return -1;
        } else {
            return 1 + mincoins;
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
        for(int j=0;j<k;j++){

            int b=0,e=0;
            cin >> b >> e;
            coins[j] = b*b+e*e;

        }
        int num = blergh(coins,V*V);
        if(num == -1){
            cout << "impossible" << endl;
        } else {
            cout << num << endl;
        }
        lookup.clear();
    }


    return 0;
}

