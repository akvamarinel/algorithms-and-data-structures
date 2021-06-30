#include <iostream>
#include <math.h>
#include <string>
#include <vector>

using namespace std;
vector<int> dec2bin(int num, int s)
{
    vector<int> binaryNum(s, 0);

    int i = 0;
    while (num > 0) {
        binaryNum[i] = num % 2;
        num = num / 2;
        i++;
    }
    return binaryNum;
}

int main() {
    int size;
    cin >> size;
    int bigSumm = 0;
    int massive[size];
    for (int i =0; i < size; i++) {
        cin >> massive[i];
        bigSumm = bigSumm + massive[i];
    }

    int min = bigSumm;
    int currSum = pow(2, size);
    for (int i = 0; i < currSum; i++) {
        int curr = 0;
        vector<int> mask = dec2bin(i, size);
        for(int j=0; j<size; j++){
            if(mask[j]){
                curr = curr+massive[j];
            }
        }
        if(abs(bigSumm - (curr + curr))<min){
            min = abs(bigSumm-(curr+curr));
        }
    }
    cout << min;
}


