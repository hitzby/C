#include<stdio.h>
#include<stdlib.h>
#define MAX 100
//个人感觉归并排序和快速排序一个操作思想，就是分治法
//归并排序是先分后合，快速排序是先合后分
void merge(int arr[],int Lpos,int Rpos,int rightEnd,int temp[]){
    int i,Leftend,NumElements,tmpPos;
    Leftend=Rpos-1;
    NumElements=rightEnd-Lpos+1;
    tmpPos=Lpos;
    while(Lpos<=Leftend && Rpos<=rightEnd){
        if(arr[Lpos]<=arr[Rpos]){
            temp[tmpPos++]=arr[Lpos++];
        }
        else{
            temp[tmpPos++]=arr[Rpos++];
        }
    }
    while(Lpos<=Leftend){
        temp[tmpPos++]=arr[Lpos++];
    }
    while(Rpos<=rightEnd){
        temp[tmpPos++]=arr[Rpos++];
    }
    for(i=0;i<NumElements;i++,rightEnd--){
        arr[rightEnd]=temp[rightEnd];
    }
}
void Msort(int arr[],int left,int right,int temp[]){
    int center;
    if(left<right){
        center=left+(right-left)/2;
        Msort(arr,left,center,temp);
        Msort(arr,center+1,right,temp);
        merge(arr,left,center+1,right,temp);
    }
}
void mergesort(int arr[],int n){
    int *temp=(int *)malloc(sizeof(int )*n);
    if(temp!=NULL){
        Msort(arr,0,n-1,temp);
        free(temp);
    }
    else{
        printf("memory allocation failed\n");
    }
}
int main(void){
    int arr[MAX];
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
       scanf("%d",&arr[i]); 
    }
    // Merge Sort Implementation
    mergesort(arr,n);
    // Print Sorted Array
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}
