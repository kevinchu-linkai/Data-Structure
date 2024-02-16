//
//  main.cpp
//  Lab1_Task3a
//
//  Created by 朱麟凱 on 2022/1/26.
//

#include <iostream>
using namespace std;
int main() {
    int A;
    int B;
    int cnt;
    int i;
    cout << "Enter an integer:" << endl;
    cin >> A;
    cnt = 1;
    for (i = 9; i > 0; i--) {
        cout << "Enter an integer:" << endl;
        cin >> B;
        if (B > A){
            A = B;
            cnt = 1;
        }
        else if (B == A){
            cnt++;
        }
    }
    cout << "The largest number is " << A << endl;
    cout << "The occurance of the number is " << cnt << " times" << endl;
}
