#include <iostream>
#include <queue>
#include <vector>

using namespace std;

bool mycomp(int a,int b){
    return a > b;
}

void balance(std::priority_queue<int> &A,std::priority_queue<int,vector<int>,
             greater<int >> &B){
    if(A.size() > B.size()+1) {
        while (A.size() > B.size()) {
            int tmp = A.top();
            A.pop();
            B.push(tmp);
        }
    } else if (B.size() > A.size()+1) {
        while (B.size() > A.size()) {
            int tmp = B.top();
            B.pop();
            A.push(tmp);
        }
    }
}

int main() {

    std::priority_queue<int> A;
    std::priority_queue<int,vector<int>,greater<int >> B;

    int i=0;
    int n = 0;
    cin >> n;

    cout << n << endl;

    double median = n;

    A.push(n);

    while(i < 10999){

        cin >> n;
        i++;

        if(n >= median){
            B.push(n);
        } else {
            A.push(n);
        }

        balance(A,B);

        if(A.size() > B.size()){
            median = A.top();
            cout << A.top() << endl;
        } else if (A.size() < B.size()){
            median = B.top();
            cout << B.top() << endl;
        } else {
            median = (A.top()+B.top())/2.0;
            cout << (A.top()+B.top())/2 << endl;
        }

    }


    return 0;
}