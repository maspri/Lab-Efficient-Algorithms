#include <tuple>
#include <iostream>
#include <cmath>

using namespace std;

std::tuple<int, int, int> calc_triple(long int U,long int V,long int W){
    // We have |x| <= sqrt(W-y^2-z^2) <= sqrt(W)
    long int boundX = sqrt(W);
    long int x,y,z;
    for(long int i=-boundX;i <= boundX;i++){
        x = i;
        if(i==0 || W-x*x <= 0) continue;
        long int boundY = ceil(sqrt(W-x*x));
        for(long int j=-boundY;j <= boundY;j++){
            y = j;
            if(j == 0 || x == y || W-x*x-y*y <= 0) continue;

            z = U - x - y;

            if(x*y*z==V && x*x+y*y+z*z==W){
                return std::make_tuple(x,y,z);
            }
        }

    }
    return std::make_tuple(1,1,1);
}

int main() {
    int n;

    cin >> n;

    for(int i = 0; i < n; ++i) {
        long int U,V,W;
        int x,y,z;
        cin >> U >> V >> W;
        std::tie(x,y,z) = calc_triple(U,V,W);
        if(x == 1 && y == 1 && z == 1){
            cout << "empty set" << endl;
        } else {
            cout << x << " " << y << " " << z << endl;
        }
    }

    return 0;
}
