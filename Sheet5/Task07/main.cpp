#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <fstream>
#include <sstream>
#include <string>
#include <assert.h>

using namespace std;
struct point{
    point(double x, double y): x(x),y(y){};
    double x;
    double y;
};

bool is_close(double a, double b){
    return abs(a-b) < 1E-8;
}

int main() {

    int n = 0;
    cin >> n;
    vector<point> points(n,point(0.0,0.0));

    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    vector<double> slope(n-1,0.0);
    int max_num = 0;
    for (int i = 0; i < n; ++i) {

        int m = 0;
        for (int j = 0; j < n; ++j) {
            if(i == j){
                continue;
            }
            if(points[j].x-points[i].x == 0 && points[j].y-points[i].y > 0){
                slope[m] = numeric_limits<double>::max();
            } else if(points[j].x-points[i].x == 0 && points[j].y-points[i].y < 0){
                slope[m] = numeric_limits<double>::lowest();
            } else if(points[j].x-points[i].x == 0 && points[j].y-points[i].y == 0){
                slope[m] = 0;
            } else {
                slope[m] = (points[j].y-points[i].y)/(points[j].x-points[i].x);
            }
            m++;
        }

        sort(slope.begin(),slope.end());
        double last = slope[0];
        int count = 1;
        int max_so_far = 0;
        for (int k = 1; k < n; ++k) {
            if(is_close(slope[k],last)){
                count++;
            } else {
                if(count > max_so_far){
                    max_so_far = count;
                }
                count = 1;
                last = slope[k];
            }
        }
        if(max_so_far > max_num){
            //+1 because the point considered at the moment is not in the slope array
            max_num = max_so_far+1;
        }
    }

    cout << max_num << endl;

    return 0;
}