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