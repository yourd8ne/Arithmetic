#include <iostream>
#include "arithmetic.h"

int main()
{
    char a [] = "a+b";
    char* a1;
    Arithm f(a);
    int errors[100]; int count; int k; int* p;
    p = f.CheckExp(count, k);
    cout << "Num errors = "<< count;
    for (int i = 0; i < k/2; i++)
    {
        cout << p[i]<< ' '<<p[i+1];
    }
    if (count == 0)
    {


        a1 = f.Postfix();
        cout << endl <<"Postfix: " <<a1;
        double* res = f.Calculate(a1);
        cout << endl;
        if (res[1] != 0)
            cout << "in postf mist";
        else
        {
            cout << "res" <<res[0] << endl;
        }
            
    }
}