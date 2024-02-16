//
//  Task2
//
//  Created by 朱麟凱 on 2022/1/25.
//
#include <iostream>
using namespace std;
int main() {
    float M1;
    float M2;
    float D;
    cout << "Enter the current meter reading:" << endl;
    cin >> M1;
    cout << "Enter the previous meter reading:" << endl;
    cin >> M2;
    D = M1 - M2;
    if (D <= 100)
        D = D*0.1;
    else if (D > 100 && D <=200)
        D = (D - 100)*0.2 + 10;
    else if (D > 200 && D <= 500)
        D = (D - 200)*0.5 +30;
    else
        D = D - 500 + 180;
    cout << "The bill for this month is " << D << " Dirhams." << endl;
    return 0;
}
