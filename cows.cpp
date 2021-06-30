#include <iostream>
using namespace std;
bool check(int tmp, int coords [], int cows, int houses){
    int curCows =1;
    int curCoord = coords[0];
    for(int i=1; i<houses; i++){
        if(coords[i]-curCoord >=tmp){
            curCoord = coords[i];
            curCows = curCows+1;
            if(curCows==cows){

                return true;
            }
        }
    }
    if(curCows < cows){
        return false;
    }
}
int main() {
    int houses;
    int cows;
    cin >> houses;
    cin >> cows;
    int coords [houses];
    for(int i=0; i<houses; i++){
        cin >> coords[i];
    }

    int left = 0;
    int max = (coords[houses-1]-coords[0]);
    while (max>left+1){
        int tmp = (max+left)/2;
        cout << tmp << " ";
       if(check(tmp, coords, cows, houses)){
           left = tmp;
       }
       else {
           max = tmp;
       }
    }
    cout << left;
}
