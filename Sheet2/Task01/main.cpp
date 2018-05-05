#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

union S{
    int x;
    bitset<32> bits;
};

void calc_ab(S x, vector<S> &ab){

    int num_ones = 0;
    for(int i=0;i<32;i++){
        if(x.bits[i]) num_ones++;
    }

    ab[0].x = 0;
    ab[1].x = 0;

    bool start = false;
    if(num_ones % 2 != 0) start = true;

    for(int i=0;i<32;i++){
        if(x.bits[i]){
            ab[start].bits[i] = 1;
            start = !start;
        } else {
            ab[0].bits[i] = 0;
            ab[1].bits[i] = 0;
        }
    }

}


int main() {


    S x = {0};
    vector<S> ab(2,{0});

    while (1){
        cin >> x.x;
        if(x.x == 0){
            break;
        } else {
            calc_ab(x,ab);
            cout << ab[0].x << " " << ab[1].x << endl;
        }

    }


    return 0;
}

