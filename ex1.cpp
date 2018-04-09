#include<iostream>
#include<cassert>

/*
 * Ограничение времени	0.1 секунда
 * Ограничение памяти	10Mb
 * Ввод	стандартный ввод или input.txt
 * Вывод	стандартный вывод или output.txt

 * Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1].
 * Необходимо найти первую пару индексов i0 и j0, , такую что A[i0] + B[j0] = max {A[i] + B[j],
 * где 0 <= i < n, 0 <= j < n, i <= j}.
 * Время работы - O(n). n ≤ 100000.
 *
 */
using namespace std;

void printArray(const int* arr, const int length){
    assert(length >= 0);
    assert(arr != nullptr);

    for(int i = 0; i < length; i++)
        cout << arr[i] << " ";

    cout << "\n";
}

void readArray(int *const src, const int length){
    
    assert(src != nullptr && length >= 0);

    for( int i = 0; i < length; i++)
        cin >> src[i];
}

void findMaxPair(const int * const arrA, const int * arrB, const int length, int& maxIndexA,
      int& maxIndexB){
    assert(arrA != nullptr && arrB != nullptr && length >= 0 );

    int tmpIndex = 0;

    for (int i = 0; i < length; i++){
        if (arrA[tmpIndex] < arrA[i])
            tmpIndex = i;

        if (arrA[maxIndexA] + arrB[maxIndexB] < arrA[tmpIndex] + arrB[i]){
            maxIndexB = i;
            maxIndexA = tmpIndex;
        }
    }
}

int main(){
    int n;
    cin >> n;

    assert(n >= 0);

    int *arrA = new int[n];
    int *arrB = new int[n];

    readArray(arrA, n);
    readArray(arrB, n);

    int maxIndexA = 0, maxIndexB = 0;

    findMaxPair(arrA, arrB, n, maxIndexA, maxIndexB);

    cout << maxIndexA << " " << maxIndexB;
    delete[] arrA;
    delete[] arrB;

    return 0;
}
