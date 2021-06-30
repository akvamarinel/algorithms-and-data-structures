#include <iostream>
#include <string>
#include <map>
using namespace std;

void merge(int arr [][2], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1][2], R[n2][2];

    for (int i = 0; i < n1; i++) {
        L[i][0] = arr[l + i][0];
        L[i][1] = arr[l + i][1];
    }
    for (int j = 0; j < n2; j++){
        R[j][0] = arr[m + 1 + j][0];
        R[j][1] = arr[m + 1 + j][1];
    }
    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (L[i][0] <= R[j][0]) {
            arr[k][0] = L[i][0];
            arr[k][1] = L[i][1];
            i++;
        }
        else {
            arr[k][0] = R[j][0];
            arr[k][1] = R[j][1];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k][0] = L[i][0];
        arr[k][1] = L[i][1];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k][0] = R[j][0];
        arr[k][1] = R[j][1];
        j++;
        k++;
    }
}

void mergeSort(int arr [][2],int l,int r){
    if(l>=r){
        return;
    }
    int m =l+ (r-l)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
}

int main() {
    string castle;
    cin >> castle;
    int power [26];
    int curr;
    for(int i=0; i<26; i++){
        cin >> curr;
        power[i] = curr; //веса
    }
    int size = castle.length();
    int castleMass[size][2]; //0-вес и 1-буква

    map<int, int> gg; //буква и ее индекс в строке
    int weight;

    for (int i = 0; i < size; i++) {
        if (gg.find(((int) castle[i])) != gg.end()) {
            if (castleMass[gg[(int) castle[i]]][0] != 0) {
                castleMass[i][0] = 0; // для всех, которые больше раза
                castleMass[i][1] = (int) castle[i];
            } else{
                weight = power[(int) castle[i] - 97];
                castleMass[i][0] = -weight; //
                castleMass[gg[(int) castle[i]]][0] = weight;
                castleMass[i][1] = (int) castle[i];
            }
        }
        else {
            castleMass[i][0] = 0; // меняем вес на ноль
            castleMass[i][1] = (int) castle[i]; // кладем буквы
            gg[(int) castle[i]] = i; // кладем в гг
        }
    }
    int n = sizeof(castleMass) / sizeof(castleMass[0]);
    mergeSort(castleMass, 0, n - 1);

    for(int i=0; i<size; i++){
        cout << static_cast <char>(castleMass[i][1]);
    }
}


