//
//  main.cpp
//  Lab1_Task3c
//
//  Created by 朱麟凱 on 2022/1/26.
//

#include <iostream>
using namespace std;
int main(){
    int b;
    int i;
    int j;
    int cnt = 1;
    cout << "Enter a number:" << endl;
    cin >> b;
    for(j = 3; j < b; j++){
        for(i=2; i<j; i++){
            if(j%i==0)
               break;
        }
        if(i == j)
            cnt++;
    }
    
    cout << b << " has " << cnt << " prime numbers smaller than it!" << endl;
    return 0;
}
