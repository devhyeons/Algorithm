#include <iostream>

using namespace std;

int main(void) {
    int a,b;
    cin>>a;
    cin>>b;
    int i=0, j=0;
        for(i=0; i<b; i++)
        {for(j=0; j<a; j++)
            cout<<"*";
            cout<<"\n";
        }
}