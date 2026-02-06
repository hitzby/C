/*
冒泡排序 （O（N^2））平均情况，是稳定排序
*/
#include<stdio.h>
#define MAX 100
void bubble_sort(int arr[],int n){
    int i,j;
    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                int tmp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=tmp;
            }
        }
    }
}
int main(void){
    int arr[MAX]={0};
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    bubble_sort(arr,n);
    for(int i=0;i<n;i++){
        printf(" %d ",arr[i]);
    }
    return 0;
}
