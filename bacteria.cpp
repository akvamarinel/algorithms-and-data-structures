#include <iostream>
#include <string>
using namespace std;

int main()
{
    int a;
    int b;
    int c;
    int d;
    int k;
    cin >> a; // бактерии
    cin >> b; // образуется новых бактерий из 1 бактери
    cin >> c; // извлекаемые бактерии
    cin >> d; // помещаемые в контейнер
    cin >> k; // количество дней
    int tmp; // количество новых бактерий

// Я ПЛАКАЛА
//int block =1;

//cout « a « b « c « d « k;
    int previous = -9999;

    for (int i=0; i<k; i++){
        tmp = a * b;
        if (tmp <= c){
            cout << 0;
            return 0;
        }
        if (d > tmp -c) {
            a = tmp -c;
        }
        else {
            a = d;
        }
        if (a == previous){
            cout << a;
            return 0;
        }
        previous = a;
    }
    cout << a;


}