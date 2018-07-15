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

vector<vector<bool>> global_A = {};
vector<vector<bool>> global_L = {};
vector<vector<bool>> global_U = {};
vector<int> global_perm = {};

template <typename T>
void print(const char *s,const vector<vector<T>> &m) {
    //cout << s << endl;
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < m[i].size(); ++j) {
            cout << m[i][j] << "";
        }
        cout << endl;
    }
    cout << endl;
}
vector<vector<bool >> matrix_mul(const vector<vector<bool >> &A,const vector<vector<bool >> &B) {
    vector<vector<bool >> erg(A.size(), vector<bool>(B[0].size()));
    int n = A.size();
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < B[0].size(); ++j) {
            for (int k = 0; k < n; ++k) {
                erg[i][j] = (erg[i][j] != (A[i][k] && B[k][j]));
            }
        }
    }

    return erg;
}

void test(vector<vector<bool >> &L,
          vector<vector<bool >> &U,
          vector<vector<bool >> &P,
          vector<vector<bool >> &A,
          vector<int> &perm){

    //print("A:",A);
    //print("L:",L);
    print("U:",U);
    //print("P:",P);

    for (int k = 0; k < perm.size(); ++k) {
        cout << perm[k] << " ";
    }
    cout << endl;

    vector<vector<bool >> erg = matrix_mul(L,U);
    vector<vector<bool >> PA = matrix_mul(P,A);



    bool equals = true;
    int n = L.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            equals = equals && (erg[i][j] == PA[i][j]);
        }
    }

    if(equals){
        cout << "Equal!!" << endl;
    } else {
        cout << "Not Equal!!" << endl;
    }

}

int check(vector<bool> &x,vector<bool> &image){
    vector<vector<bool>> xx(x.size(),vector<bool>(1,false));
    for (int i = 0; i < x.size(); ++i) {
        xx[i][0] = x[i];
    }
    vector<vector<bool>> reconstruced = matrix_mul(global_A,xx);

    for (int j = 0; j < image.size(); ++j) {
        if(!(image[j] == reconstruced[j][0])){
            return -1;
        }
    }
    return 0;
}

void forward_sub(vector<bool> &image,vector<bool> &y){
    int n = image.size();
    vector<bool > pImage(n, false);
    for (int k = 0; k < n; ++k) {
        pImage[k] = image[global_perm[k]];
    }

    for (int i = 0; i < n; ++i) {
        y[i] = pImage[i];
        for (int j = 0; j < i; ++j) {
            y[i] = (y[i] != (global_L[i][j]*y[j]));
        }
        //this step is unnecessary since L[i][i] == 1, thus leaving y[i] unchanged
        //y[i] = y[i]/L[i][i];
    }
}

int backward_sub(const vector<bool> &y,vector<bool> &x){
    int n = y.size();


    int min_count = numeric_limits<int>::max();
    for (int k = 0; k < 256; ++k) {

        int count = 0;

        for (int l = 0; l < 8; ++l) {
            x[n-1-l] = false;
        }

        for (int l = 0; l < 8; ++l) {
            if(k & (1 << l)){
                x[n-1-l] = true;
            }
        }

        for (int i = n - 1 - 8; i >= 0; --i) {

            x[i] = y[i];

            if (y[i] && !global_U[i][i]) {
                return -1;
            }

            for (int j = i + 1; j < n; ++j) {
                x[i] = (x[i] != global_U[i][j] * x[j]);
            }

            if (x[i]) count++;

            //this is also unnecessary, since if U[i][i] == 0
            //then the whole row is 0 and we have to have y[i]=0
            //otherwise there is no solution
            //x[i] = x[i]/global_U[i][i];
        }

        if(count < min_count){
            min_count = count;
        }
    }

    return min_count;
}
void fill(vector<vector<bool >> &field){
    const int N = 256;
    const int sdj = 16;
    for (int i = 0; i < N; ++i) {
        int x = i / sdj;
        int y = i % sdj;
        field[x*sdj+y][i] = true;
        if(x > 0){
            field[(x-1)*sdj+y][i] = true;
        }
        if(x < sdj-1) {
            field[(x + 1)*sdj+y][i] = true;
        }
        if(y > 0) {
            field[x*sdj + (y - 1)][i] = true;
        }
        if(y < sdj-1){
            field[x*sdj+(y + 1)][i] = true;
        }

    }
}
template <typename T>
void swap_rows(int i,int j,int from,int to,vector<vector<T>> &m){
    T tmp;
    for (int k = from; k < to; ++k) {
        tmp = m[i][k];
        m[i][k] = m[j][k];
        m[j][k] = tmp;
    }
}

void LU(){
    const int N = 256;
    vector<vector<bool >> A(N,vector<bool >(N,false));
    vector<vector<bool >> U(N,vector<bool >(N,false));
    vector<vector<bool >> L(N,vector<bool >(N,false));
    vector<vector<bool >> P(N,vector<bool >(N,false));
    vector<int> perm(N,0);
    for (int i = 0; i < N; ++i) {
        L[i][i] = true;
        P[i][i] = true;
        perm[i] = i;
    }
    fill(A);
    fill(U);
    global_A = A;

    for (int k = 0; k < N-1; ++k) {

        int i=k;
        for (; i < N; ++i) {
            if (U[i][k]) break;
        }
        if(i==N){
            continue;
        }
        swap_rows(k,i,k,N,U);
        swap_rows(k,i,0,k,L);
        swap_rows(k,i,0,N,P);

        int tmp = perm[i];
        perm[i] = perm[k];
        perm[k] = tmp;

        for (int j = k+1; j < N; ++j) {
            if(!U[j][k]){
                continue;
            }
            for (int l = k; l < N; ++l) {

                //the pivot step over GF(2)
                L[j][k] = true;

                U[j][l] = (U[j][l] != U[k][l]);
            }
        }
    }

    //print("",L);
    //print("",U);


    global_U = U;
    global_L = L;
    global_perm = perm;
    //test(L,U,P,A,perm);
}

void solve(vector<bool> &image){
    vector<bool> y(image.size(), false);
    forward_sub(image,y);
    vector<bool> x(image.size(), false);
    int err = backward_sub(y,x);
    if(err > -1){

        //cout << err << endl;

        if(check(x,image) == 0){
            cout << err << endl;
        } else {
            cout << "This should not happen..." << endl;
        }

    } else {
        cout << "-1";
    }
}

int main() {

    /**
     * The main idea here is that we interpret the image as vector y
     * over GF(2)/ Z_2. The changes we can make to the image can also
     * be represented by vectors v_1,...,v_256 over Z_2 depending on which pixel
     * the change operates on. Thus we get the following linear equation system:
     * (v_1 v_2 ... v_256)x = y
     * This can just be solved using gaussian elimination.
     * The matrix (v_1 v_2 ... v_256) does not have full rank, thus in order
     * to find the vector achieving y with the least number of changes,
     * we can iterate through the solution set which has 256 elements, as the
     * kernel has 8 free variables.
     */

    LU();

    vector<bool> image(256,false);

    char t;
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            cin >> t;
            if(t != '#'){
                image[i*16+j] = true;
            }
        }
        //read newline. is last line newline terminated?
        //cin >> t;
    }

    solve(image);

    return 0;
}