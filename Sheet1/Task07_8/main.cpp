#include <tuple>
#include <iostream>
#include <cmath>

using namespace std;

bool is_close(double a, double b, double eps) {
    return fabs(a - b) < eps;
}

std::tuple<int, int, int> calc_triple(double U, double V, double W) {
    /**
     * Note:
     * z is positive. We know xyz > 0, thus we cant have x,y and z < 0.
     * Because we are looking for the lexicographically minimal tuple and the equations
     * are symmetric the two options for signs are +,+,+ and -,-,+.
     * Furthermore we have z <= sqrt(W-y^2-z^2),
     *                 and x^2+y^2 >= xy = V/z >= V/sqrt(W)
     * Thus             z <= sqrt(W-y^2-z^2) <= sqrt(W-V/sqrt(W))
     */
    long int bound = sqrt(W - V/sqrt(W));

    double z;
    for (long int i = bound; i > 0; i--) {
        z = i;
        /**
         * Given z we solve
         * (I)  x+y+z = U
         * (II) xyz = V
         * for x (it turns out the two solutions of the
         * quadratic equation are x and y or vice versa):
         */
        double tmp = sqrt(-(V / z) + (U - z) * (U - z) / 4);
        double x1 = (U - z) / 2 + tmp;
        double x2 = (U - z) / 2 - tmp;

        /**
         * If the solution is integer and fulfills equation
         * (III) x^2+y^2+z^2 = W,
         * we return the lexicographically smaller triple,
         * (x1,x2,z) or (x2,x1,z).
         */
        if ( is_close(x1 * x1 + x2 * x2 + z * z, W,1e-2) && is_close(x1, round(x1), 1e-6)) {
            if (x1 < x2 && x1 != z && x2 != z) {
                return make_tuple((int) round(x1), (int) round(x2), (int) z);
            } else if (x2 < x1 && x1 != z && x2 != z) {
                return make_tuple((int) round(x2), (int) round(x1), (int) z);
            } else {
                break;
            }
        }
    }
    return make_tuple(1, 1, 1);
}


int main() {
    int n;

    cin >> n;

    for (int i = 0; i < n; ++i) {
        long int U, V, W;
        long int x, y, z;
        cin >> U >> V >> W;
        std::tie(x, y, z) = calc_triple(U, V, W);
        if (x == 1 && y == 1 && z == 1) {
            cout << "empty set" << endl;
        } else {
            cout << x << " " << y << " " << z << endl;
        }
    }

    return 0;
}
