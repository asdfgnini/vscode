#include <iostream>
using namespace std;

void cin_fun()
{
    string input;
    cout << "input your words " << endl;
    cin >> input;
    cout << "your input is " << endl;
    cout << input << endl;
}


int main()
{
    // cin_fun();
    unsigned char num = -2 % 256;
    char num1 = -200;
    
    printf("num = %d\r\n",num);
    cout << dec << num << endl;

    printf("num1 = %d\r\n",num1);
    cout << dec << num1 << endl;


    // cout << num1;


    return 0;
}
