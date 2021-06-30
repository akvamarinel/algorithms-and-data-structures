#include <iostream>
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
    int kinds;
    cin >> kinds;
    int znak [kinds][2];
    int sum = 0;
    for(int i=0; i<kinds; i++){
        cin >> znak[i][0];
        sum = sum+znak[i][0];
        znak[i][1]=i+1;
    }

    mergeSort(znak, 0, kinds-1);
    int tmp=0;
    int opora_ind = kinds-1;
    int indx, maxx;
    while (true) {
        cout << znak[opora_ind][1] << " ";
        znak[opora_ind][0]--;
        tmp++;

        if (tmp == sum) break;
        while (znak[opora_ind][0]==0)opora_ind--;

        indx = 0;
        maxx = 0;
        for (int i=opora_ind-1; i >= 0; i--) {
            if (znak[i][0] > maxx) {
                maxx = znak[i][0];
                indx = i;
            }
        }
        if (maxx > 0) {
            cout << znak[indx][1] << " ";
            znak[indx][0]--;
            tmp++;
        }
        if (tmp == sum) break;
    }
}
