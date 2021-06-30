#include <iostream>
// я уже это скидывала, а потом скинула решение другой задачи, сейчас опять скину, чтобы горела галочка
//опять
using namespace std;

int main()
{
    int num;
    int b=1;
    int c=0;
    int q=0;
	int f=1;
    cin >> num;
    int flw[num];

    for(int i=0; i<num; i++){
        cin >> flw[i];
    }

    if(num==1){
            cout<<"1 1";
        }
        else{
    for(int i=0; i<num-1; i++){

        if(flw[i]==flw[i+1]){
            f=f+1;
            if(f!=3){
                b=b+1;
                if(b>c){
                    c=b;
                    q=i;
                }
            }
            if(f==3){
                    f=2;
                    b=2;

            }
        }
        else{
            f=1;
            b=b+1;
            if(b>c){
                c=b;
                q=i;
            }
        }
    }
    cout<<q+3-c<<" "<<q+2;
    }
    return 0;
}
