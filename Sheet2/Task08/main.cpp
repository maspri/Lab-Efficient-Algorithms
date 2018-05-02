#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef vector<vector<int>> field_type;


void calc_summed_area_table(const field_type &field,field_type &table){

    int n = field.size();

    table[0][0] = field[0][0];

    /*calculate first row and column*/
    for (int k = 1; k < n; ++k) {
       table[k][0] = field[k][0] + table[k-1][0];
    }
    for (int k = 0; k < n; ++k) {
        table[0][k] = field[0][k] + table[0][k-1];
    }

    for(int i = 1; i < n; ++i) {
        for(int j = 1; j<n; ++j){
            table[i][j] = field[i][j] + table[i-1][j] + table[i][j-1] - table[i-1][j-1];
        }
    }
}

int try_rectangles(const field_type &table){

    int n = table.size();
    int cost = numeric_limits<int>::min();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {


            for (int k = i; k < n; ++k) {
                for (int l = j; l < n; ++l) {

                    int A = (i > 0 && j > 0) ? table[i-1][j-1] : 0;
                    int B = i > 0 ? table[i-1][l] : 0;
                    int C = j > 0 ? table[k][j-1] : 0;
                    int D = table[k][l];

                    int new_cost = A - B - C + D;

                    if(new_cost > cost){
                        cost = new_cost;
                    }
                }
            }

        }
    }

    return cost;
}

void print_field(const field_type &field){
    int n = field.size();

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j<n; ++j){
            cout << field[i][j] << " | ";
        }
        cout << endl;
    }
}

int main() {

    int n = 3;

    cin >> n;

    //field_type field = {{-1,4,-1},{-2,1,2},{-2,-1,-3}};

    field_type field(n,vector<int>(n,0));
    field_type table(n,vector<int>(n,0));

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j<n; ++j){
            cin >> field[i][j];
        }
    }

    calc_summed_area_table(field,table);

    /*print_field(field);
    cout << endl;
    print_field(table);*/

    int cost = try_rectangles(table);

    cout << cost << endl;

    return 0;
}

