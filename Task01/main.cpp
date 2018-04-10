#include <iostream>

using namespace std;

int main() {
    int t;

    cin >> t;

    for(int i = 0; i < t; ++i) {
        int a, b;
        cin >> a >> b;
        if( a < b ){
            cout << "less than" << endl;
        } else if (a > b) {
            cout << "greater than" << endl;
        } else {
            cout << "equal to" << endl;
        }
    }

    return 0;
}
