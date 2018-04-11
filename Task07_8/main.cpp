#include <tuple>
#include <iostream>
#include <cmath>

using namespace std;

bool is_close(long double a, long double b, long double eps){
    return fabs(a-b) < eps;
}

std::tuple<int, int, int> calc_triple(long double U,long double V,long double W){
    // We have |x| <= sqrt(W-y^2-z^2) <= sqrt(W)
    long int bound = sqrt(W);
    long double x;
    for(long int i=-bound;i <= bound;i++){
        if (i == 0) continue;
        x = i;
        /**
         * Given x we solve
         * (I)  x+y+z = U
         * (II) xyz = V
         * for z (it turns out the two solutions of the
         * quadratic equation are z and y or vice versa):
         */
        long double z1 = (U-x)/2 + sqrt(-(V/x)+(U-x)*(U-x)/4);
        long double z2 = (U-x)/2 - sqrt(-(V/x)+(U-x)*(U-x)/4);

        /**
         * If the solution is integer and fulfills equation
         * (III) x^2+y^2+z^2 = W,
         * we return the lexicographically smaller triple,
         * (x,z1,z2) or (x,z2,z1).
         */
        if(is_close(z1,round(z1),1e-15L) && is_close(x*x+z1*z1+z2*z2,W,1e-15L)){
            if(z1 < z2){
                return std::make_tuple((int)x,(int)round(z1),(int)round(z2));
            } else if (z2 < z1){
                return std::make_tuple((int)x,(int)round(z2),(int)round(z1));
            } else{
                continue;
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
