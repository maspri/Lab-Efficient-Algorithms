#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef vector<vector<int>> field_type;

int kadane(const vector<int> sums){
    int max_subsum_i = sums[0];
    int maximum = sums[0];
    for (int i = 1; i < sums.size(); ++i) {
        max_subsum_i = max(sums[i],max_subsum_i+sums[i]);
        maximum = max(maximum,max_subsum_i);
    }
    return maximum;
}

int try_rectangles(field_type &table){
    int n = table.size();
    vector<int> sums(n,0);
    int maximum = numeric_limits<int>::min();
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                int A = table[k][j];
                int B = i > 0 ? table[k][i-1] : 0;
                sums[k] = A - B;
            }

            maximum = max(maximum,kadane(sums));

        }
    }
    return maximum;
}

void calc_summed_row_table(const field_type &field,field_type &table){

    int n = field.size();

    for (int l = 0; l < n; ++l) {
        table[l][0] = field[l][0];
    }
    for (int i = 0; i < n; ++i) {

        for (int j = 1; j < n; ++j) {
            table[i][j] = field[i][j] + table[i][j-1];
        }
    }
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

    calc_summed_row_table(field,table);

    /*print_field(field);
    cout << endl;
    print_field(table);*/

    int cost = try_rectangles(table);

    cout << cost << endl;

    return 0;
}

