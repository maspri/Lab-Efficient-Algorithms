#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;
class point {
public:
    double x,y;
    point():x(0.0),y(0.0){}
    point(double x, double y):x(x),y(y){}

    double dist(point &other){
        return sqrt((x-other.x)*(x-other.x)+(y-other.y)*(y-other.y));
    }
};

double triangula(int n,vector<point> &points){
    vector<vector<double>> table(n,vector<double>(n,0.0));

    for (int d = 2; d <= n-2; ++d) {
        for (int i = 0; i < n; ++i) {
            double min_option = 0.0;
            if(d > 2){
                min_option = min(table[(i+1) % n][(i+d) % n],table[i][(i+d-1) % n]);
            }
            table[i][(i+d) % n] = points[i].dist(points[(i+d) % n])+min_option;
        }
    }

    double min = numeric_limits<double>::max();
    for (int j = 0; j < n; ++j) {
        if (table[j][(j+n-2) % n] < min){
            min = table[j][(j+n-2) % n];
        }
    }
    return min;
}

int main(){
    int n=0;
    cin >> n;

    vector<point> points(n,point());

    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }
    cout.precision(3);
    cout << fixed << triangula(n,points);
}
