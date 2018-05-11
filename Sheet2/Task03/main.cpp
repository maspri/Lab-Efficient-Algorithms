#include <iostream>
#include <vector>
#include <random>

using namespace std;


void insert(vector<int> &numbers,int start,int end, int newnumber){
    if(start == end){
        numbers.insert(numbers.begin()+start,newnumber);
    } else if(newnumber > numbers[start+(end-start)/2]){
        insert(numbers,start+(end-start)/2+1,end,newnumber);
    } else if(newnumber <= numbers[start+(end-start)/2]){
        insert(numbers,start,start+(end-start)/2,newnumber);
    }
}

void print(vector<int> &numbers){
    for (int i = 0; i < numbers.size(); ++i) {
        cout << numbers[i] << " ";
    }
    cout << endl;
}

int main() {

    vector<int > numbers;
    numbers.reserve(11000);

    int i=0;
    while(i < 11000){

        int n = 0;
        cin >> n;

        insert(numbers,0,numbers.size(),n);

        int k = numbers.size();

        cout << ((numbers.size() % 2 == 0) ? (numbers[k/2-1]+numbers[k/2])/2 : numbers[(k+1)/2-1]);

        i++;
    }


    return 0;
}

