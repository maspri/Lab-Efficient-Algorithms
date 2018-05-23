#include <iostream>
#include <vector>
#include <bitset>
#include <limits>

using namespace std;

int main() {

    int n = 0,D=0;

    cin >> n >> D;

    vector<int> dists(n+2,0);

    int max = 0;
    char last = '\0';
    for (int i = 2; i < n+2; ++i) {
        int d = 0;
        char t;
        cin >> t >> d;

        dists[i] = d;

        if (last == 'b'){
            if(dists[i]-dists[i-1] > max) {
                max = dists[i] - dists[i - 1];
            }
        } else if(dists[i]-dists[i-2] > max) {
            max = dists[i]-dists[i-2];
        }

        last = t;
    }

    if(last == 's' && D-dists[n+1-1] > max){
        max = D-dists[n+1-1];
    } else if(last == 'b' && D-dists[n+1] > max){
        max = D-dists[n+1];
    }

    cout << max;

    return 0;
}

