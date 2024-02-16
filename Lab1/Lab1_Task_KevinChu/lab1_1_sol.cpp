//
//  main.cpp
//  Task1
//
//  Created by 朱麟凱 on 2022/1/25.
//

#include <iostream>
using namespace std;
int main() {
    float C;
    float F;
    cout << "Enter the temperature in Celsius:" << endl;
    cin >> C;
    F = C*9/5 +32;
    cout << "The temperature is " << F << " degree Ferenheit" << endl;
    return 0;
}
