#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
void Swap(int *, int *);
void InterchangeSort(int *, int);
void SelectionSort(int *, int);
void HeapSort(int *, int);
 
int main()
{
    srand(time(0));
    int *arr = (int *)calloc(10, sizeof(int));
    printf("Current Array: ");
    for (int i = 0; i < 10; ++i) {
        arr[i] = 1 + rand() % 100;
        printf("%4d", arr[i]);
    }
    printf("\nInterchange Sorted Array: ");
    InterchangeSort(arr, 10);
    for (int i = 0; i < 10; ++i) {
        printf("%4d", arr[i]);
    }
    printf("\nSelection Sorted Array: ");
    SelectionSort(arr, 10);
    for (int i = 0; i < 10; ++i) {
        printf("%4d", arr[i]);
    }
    free(arr);
    return 0;
}
 
void Swap(int *a, int *b)
{
    int Temp = *a;
    *a = *b;
    *b = Temp;
}
 
void InterchangeSort(int *arr, int n)
{
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[i] > arr[j])
                Swap(&arr[i], &arr[j]);
        }
    }
}
 
void SelectionSort(int *arr, int n)
{
    /* Idea: Mô phỏng cách sắp xếp tự nhiên nhất trong thực tế:
      - Chọn phần tử nhỏ nhất và đưa về vị trí đầu tiên trong mảng.
      - Sau đó xem mảng chỉ còn n-1 phần tử.
      - Lặp lại cho đến khi mảng chỉ còn 1 phần tử.
    */
    int index, value;
    for (int i = 0; i < n; ++i) {
        value = arr[i];
        index = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < value) {
                value = arr[j];
                index = j;
            }
        }
        Swap(&arr[i], &arr[index]);
    }
}
/*
void HeapSort(int *arr, int n)
{
 
}*/
