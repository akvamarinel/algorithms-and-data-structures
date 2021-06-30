#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int l;
    int window;


    cin >> l;
    cin >> window;
    int mass [l];

    for(int i = 0; i<l; i++){
        cin >> mass[i];
    }
int index;
    for(int i=0; i<l-window+1; i++) {
            if(i==0){

                index = min_element(mass + i, mass + i + window) - mass;
                cout << mass[index] << " " ;
                continue;
            }
            if(index >= i){
                if(mass[index]>mass[i+window-1]){
                    cout << mass[i+window-1] << " ";
                }
                else {
                    cout << mass[index] << " ";
                }
            }
            else {
                index = min_element(mass + i, mass + i + window) - mass;
                cout << mass[index] << " " ;
            }


    }

}