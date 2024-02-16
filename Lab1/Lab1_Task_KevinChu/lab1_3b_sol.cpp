//
//  main.cpp
//  Lab_Task3b
//
//  Created by 朱麟凱 on 2022/1/26.
//

#include <iostream>
using namespace std;
int main(){
    int a;
    int i;
    cout << "Enter a number:" << endl;
    cin >> a;
    for (i = 2; i < a; i++) {
        if (a%i == 0){
            cout << a << " is not a prime number!" << endl;
            return 0;
        }
    }
    cout << a << " is a prime number!" << endl;
    return 0;
}
