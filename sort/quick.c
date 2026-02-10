#include<stdio.h>
int findpos(int arr[],int left,int right){
    int pivot=arr[left];
    int i=left;
    int j=right;
    while(i<j){
        while(i<j && arr[j]>=pivot){
            j--;
        }
        if(i<j){
            arr[i++]=arr[j];
        }
        while(i<j && arr[i]<=pivot){
            i++;
        }
        if(i<j){
            arr[j--]=arr[i];
        }
    }
    arr[i]=pivot;
    return i;
}
void quicksort(int arr[],int left,int right){
    if(left<right){
        int pos=findpos(arr,left,right);
        quicksort(arr,left,pos-1);
        quicksort(arr,pos+1,right);
    }
}
#define MAX 100
int main(void){
    int arr[MAX];
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    // Quick Sort Implementation
    quicksort(arr,0,n-1);
    // Print Sorted Array
    for(int j=0;j<n;j++){
        printf("%d ",arr[j]);
    }
    return 0;
}
// Enhanced Quick Sort with Median-of-Three Pivot Selection
/*
#include <stdio.h>

// 交换两个数
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 三数取中法找基准
int medianOfThree(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    
    // 三步排序，让 arr[low] <= arr[mid] <= arr[high]
    if (arr[mid] < arr[low])
        swap(&arr[low], &arr[mid]);
    if (arr[high] < arr[low])
        swap(&arr[low], &arr[high]);
    if (arr[high] < arr[mid])
        swap(&arr[mid], &arr[high]);
    
    // 现在 arr[mid] 是中间值
    return mid;  // 返回中间值的索引
}

// 分区函数（用三数取中的基准）
int partition(int arr[], int low, int high) {//作用是将数组分成两部分，一部分小于基准值，另一部分大于基准值，并返回基准值的最终位置
    // 1. 用三数取中找到基准索引
    int pivotIndex = medianOfThree(arr, low, high);
    
    // 2. 把基准值放到最右边（方便后续操作）
    swap(&arr[pivotIndex], &arr[high]);
    
    // 3. 基准值
    int pivot = arr[high];
    
    // 4. i 指向小于基准的区域边界
    int i = low - 1;
    
    // 5. 遍历数组
    for (int j = low; j < high; j++) {
        // 如果当前元素小于基准
        if (arr[j] < pivot) {
            i++;  // 扩大小于基准的区域
            swap(&arr[i], &arr[j]);
        }
    }
    
    // 6. 把基准放到正确位置
    swap(&arr[i + 1], &arr[high]);
    
    // 7. 返回基准的最终位置
    return i + 1;
}

// 快速排序主函数
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // 分区，得到基准位置
        int pi = partition(arr, low, high);
        
        // 递归排序左右两边
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 打印数组
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// 测试
int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("原数组: ");
    printArray(arr, n);
    
    quickSort(arr, 0, n - 1);
    
    printf("排序后: ");
    printArray(arr, n);
    
    return 0;
}*/