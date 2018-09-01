#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
struct point{
    point(double x, double y): x(x),y(y){};
    int x;
    int y;
};

class fraction{
public:
    int numerator,denominator;
    fraction():numerator(0),denominator(1){}
    fraction(int numerator,int denominator):numerator(numerator),denominator(denominator){
        kuerzen();
    }

    void kuerzen(){
        int v = numerator;
        int u = denominator;
        while ( v != 0) {
            unsigned r = u % v;
            u = v;
            v = r;
        }
        numerator /= u;
        denominator /= u;

        if(numerator < 0 || denominator < 0){
            if (denominator < 0){
                numerator *= -1;
                denominator *= -1;
            }
        }
    }

    bool operator==(const fraction &other) const{
        return numerator == other.numerator && denominator == other.denominator;
    }
};

bool is_close(double a, double b){
    return abs(a-b) < 1E-12;
}

struct less_than_key
{
    inline bool operator() (const fraction& a, const fraction& b)
    {
        return (a.numerator*b.denominator < b.numerator*a.denominator);
    }
};

int main() {

    /*fraction ab(-42,0);
    cout << ab.numerator << " " << ab.denominator << endl;
    cout << 0 % 42 << endl;*/

    int n = 0;
    cin >> n;
    vector<point> points(n,point(0.0,0.0));

    for (int i = 0; i < n; ++i) {

        double x,y;

        cin >> x >> y;

        points[i].x = (int)round(100*x);
        points[i].y = (int)round(100*y);
    }

    int max_num = 0;
    for (int i = 0; i < n; ++i) {

        int m = 0;
        vector<fraction> slope;
        for (int j = 0; j < n; ++j) {
            if(i == j){
                continue;
            }
            slope.emplace_back(points[j].y-points[i].y,points[j].x-points[i].x);

            /*if(points[j].x-points[i].x == 0 && points[j].y-points[i].y > 0){
                slope[m] = numeric_limits<double>::max();
            } else if(points[j].x-points[i].x == 0 && points[j].y-points[i].y < 0){
                slope[m] = numeric_limits<double>::lowest();
            } else if(points[j].x-points[i].x == 0 && points[j].y-points[i].y == 0){
                slope[m] = 0;
            } else {
                slope[m] = (points[j].y-points[i].y)/(points[j].x-points[i].x);
            }*/
            m++;
        }

        sort(slope.begin(),slope.end(),less_than_key());
        fraction last = slope[0];
        int count = 1;
        int max_so_far = 0;
        for (int k = 1; k < n; ++k) {
            if(slope[k] == last){
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
            max_num = max_so_far;
        }
    }

    //+1 because the point considered at the moment is not in the slope array
    cout << (max_num+1) << endl;

    return 0;
}