#include<stdio.h>
#include<stdlib.h>
#define MAX 100
void heapify(int arr[],int n,int i){
    int largest=i;
    int left=2*i+1;
    int right=2*i+2;
    if(left<n&&arr[left]>arr[largest]){
        largest=left;
    }
    if(right<n&&arr[right]>arr[largest]){
        largest=right;
    }
    if(largest!=i){
        int temp=arr[i];
        arr[i]=arr[largest];
        arr[largest]=temp;
        heapify(arr,n,largest);
    }
}
void heapsort(int arr[],int n){
    //首先构建最大堆
    for(int i=n/2-1;i>=0;i--){
        heapify(arr,n,i);
    }
        for(int i=n-1;i>0;i--){
            //交换堆顶元素和最后一个元素
            int temp=arr[0];
            arr[0]=arr[i];
            arr[i]=temp;
            //重新调整堆
            heapify(arr,i,0);
        }
}
int main(void){
    int arr[MAX]={0};
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    heapsort(arr,n);
    for(int j=0;j<n;j++){
        printf("%d ",arr[j]);
    }
    return 0;
}