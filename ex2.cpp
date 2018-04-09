
/* [0..n-1] и массив целых чисел B[0..m-1].
 * Для каждого элемента массива B[i] найдите минимальный индекс k
 * минимального элемента массива A, равного или превосходящего B[i]: A[k] >= B[i].
 * Если такого элемента нет, выведите n. 
 * Время работы поиска k для каждого элемента B[i]: O(log(k)). n, m ≤ 10000.
*/

#include<cassert>
#include<iostream>

using namespace std;

void readArray(int * const src, const int length){
    assert(src != nullptr && length >= 0);

    for(int i = 0; i < length; i++)
        cin >> src[i];

}

int binarySearch(const int * const array,const int leftLimit, const int rightLimit,
        const int key){
    assert(array != nullptr && leftLimit >= 0 && rightLimit >= 0);

    int left = leftLimit, right = rightLimit;

    while(left < right){
        int mid = left + (right - left)/2;

        if (key <= array[mid])
            right = mid;
        else
            left = mid+1;
    }
    return (right < rightLimit ? right: rightLimit);
}


int findMinIndexA(const int * const arrA, const int length, 
        const int val){
    assert(arrA != nullptr && length >= 0);

    int rightLimit = 1, leftLimit = 0;

    while(rightLimit < length && arrA[rightLimit] < val){
        leftLimit = rightLimit;
        rightLimit <<= 1;
    }

    if (rightLimit >= length)
        rightLimit = length;

    int indexK = binarySearch(arrA, leftLimit, rightLimit, val);

    // Так как изначально binarySearch возвращает rightLimit
    // если последний символ равен key

    if (indexK == rightLimit && arrA[indexK - 1] == val)
        indexK--;

    return indexK;    
}

int main(){
    int lengthA, lengthB;
    cin >> lengthA >> lengthB;

    assert(lengthA >= 0 && lengthB >= 0);

    int *arrA = new int[lengthA];
    int *arrB = new int[lengthB];

    readArray(arrA, lengthA);
    readArray(arrB, lengthB);
    
    for(int i = 0; i < lengthB; i++)
        cout << findMinIndexA(arrA, lengthA, arrB[i]) << " ";
    

    
    delete[] arrA;
    delete[] arrB;

    return 0;
}
