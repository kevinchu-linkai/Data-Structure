//============================================================================
// Name         : lab2_1
// Author       : Kevin Chu
// Version      :
// Date Created :
// Date Modified:
// Description  : Find Min. and Max. values from an Array passed to a function
//                using pass-by reference.
//============================================================================
#include<iostream>
#include<cstdlib>
using namespace std;

void findMinMax(int[],int, int&, int&);    //function declaration

int main(void)
{
    int* x; int y; int min = 0; int max = 0;//Declare variables
    cout << "Enter Size of the Array: "; cin >> y;//Prompt user for the array size
    x = new int[y];//Create dynamic array
    for(int i = 0; i < y; i++){
        x[i] = rand()%101;
    }
    //Populate the array with random values
    findMinMax(x, y, min, max);//Call function finMinMax()
    for (int i = 0; i < y; i++) {
        cout << "array[" << i << "] = " << x[i] << endl;
    }
    cout << "Min : " << min << endl;
    cout << "Max : " << max << endl;
    //Print the values of array followed by min and max values
    delete []x;//Do Necessary cleanup, e.g. delete dynamically allocated memory.
    return EXIT_SUCCESS;
}

//Function Definition
void findMinMax(int array[], int arraySize, int& min, int& max)
{
    min = array[0];
    max = array[0];
    for (int i = 1; i < arraySize; i++) {
        if (array[i] > max) {
            max = array[i];
        }
        if (array[i] < min) {
            min = array[i];
        }
    }
    //define function body.
}
