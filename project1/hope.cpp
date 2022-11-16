#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main(){
    vector<int> a;
    vector<int> c;
    a.push_back(1);
    a.push_back(2);
    a.push_back(2);
    a.push_back(2);
    for (int i = 0; i < a.size(); i++){
        cout << a[i] << endl;
    }

    c = a;

    int b = a.size();
    for (int i = 0; i < b; i++){
        a.pop_back();
    }
    cout << "after:" << endl;
    for (int i = 0; i < a.size(); i++){
        cout << a[i] << endl;
    } 
    cout << "c: "  << c.size() << endl;
    

}