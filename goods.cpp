#include <iostream>
using namespace std;

void mergeSort(int *a, int l, int r)
{
    if (l == r) return; // границы сомкнулись
    int mid = (l + r) / 2; // определяем середину последовательности
    // и рекурсивно вызываем функцию сортировки для каждой половины
    mergeSort(a, l, mid);
    mergeSort(a, mid + 1, r);
    int i = l;  // начало первого пути
    int j = mid + 1; // начало второго пути
    int tmp[r];
    for (int step = 0; step < r - l + 1; step++) // для всех элементов дополнительного массива
    {
        // записываем в формируемую последовательность меньший из элементов двух путей
        // или остаток первого пути если j > r
        if ((j > r) || ((i <= mid) && (a[i] < a[j])))
        {
            tmp[step] = a[i];
            i++;
        }
        else
        {
            tmp[step] = a[j];
            j++;
        }
    }
    // переписываем сформированную последовательность в исходный массив
    for (int step = 0; step < r - l + 1; step++)
        a[l + step] = tmp[step];
}

int main() {
 int count;
 int k;
 cin >> count;
 cin >> k;
 int goods [count];
 int bigSum = 0;
 for (int i=0; i<count; i++) {
    cin >> goods[i];
    bigSum = bigSum+ goods[i];
 }
 mergeSort(goods, 0, count-1);

 int tmp = count/k; //сколько товаров пройдет по акции
 int ind = 0; //индекс акционного товара


 for (int i=0; i<tmp; i ++) {
     ind = ind + k;
    bigSum = bigSum - goods[count - ind];
 }
cout << bigSum;

}
