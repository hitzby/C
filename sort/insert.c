/*
≤Â»Î≈≈–Ú
*/
#include<stdio.h>
#define MAX 100
void insert_sort(int arr[],int n){
    int i,j;
    for(i=1;i<n;i++){
        int key=arr[i];
        for(j=i;j>0&&arr[j-1]>key;j--){
            arr[j]=arr[j-1];
        }
        arr[j]=key;
    }
}
int main(void){
    int arr[MAX]={0};
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    insert_sort(arr,n);
    for(int i=0;i<n;i++){
        printf(" %d ",arr[i]);
    }
    return 0;
}
