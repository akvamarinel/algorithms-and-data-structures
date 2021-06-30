#include <iostream>
#include <string>
#include <cstring>
#include <map>

using namespace std;

void merge(char arr [], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    char L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++){
        R[j] = arr[m + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(char arr [],int l,int r){
    if(l>=r){
        return;
    }
    int m =l+ (r-l)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
}

int main() {
    int position;
    cin >> position;
    string last_column;
    cin >> last_column;

    int line_size = last_column.length();

    if (line_size == 1) {
        cout << last_column[0];
        exit(0);
    }

    char first_column[line_size];
    strcpy(first_column, last_column.c_str()); //c_str -- массив чаров
    mergeSort(first_column, 0, line_size - 1);

    map<char, map<int, int>> char_index_by_position_last; // индекс буквы по позиции в колонке, внутрнняя инт -- позиция среди подобных, индекс

    int char_position_by_index_first_column[line_size]; // позиция  в первой колонке среди подобных

    map<char,int> char_counter_last_column; // индекс (буква, позиция среди таких же)
    map<char,int> char_counter_first_column; //счетчики

    for (int i=0; i < line_size; i++) {
        char_counter_last_column[last_column[i]]++; //счетчики
        char_counter_first_column[first_column[i]]++;
        char_index_by_position_last[last_column[i]][char_counter_last_column[last_column[i]]] = i;
        char_position_by_index_first_column[i] = char_counter_first_column[first_column[i]];  //какая позиция среди таких же букв (дает по индексу)
    }

    cout << first_column[position - 1];
    int current_index= position - 1;
    for (int i=0; i <line_size-2; i++) {
        cout << first_column[char_index_by_position_last[first_column[current_index]][char_position_by_index_first_column[current_index]]]; //из мегамапы получим индекс, о
        current_index = char_index_by_position_last[first_column[current_index]][char_position_by_index_first_column[current_index]];
    }
    cout << last_column[position - 1];
}

