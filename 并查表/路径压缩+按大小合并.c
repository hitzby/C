#include<stdio.h>

#define MAX 100
void initialize(int arr[],int n){
    for(int i=0;i<n;i++){
        arr[i]=-1;//在这里进行初始化，负数代表该位置是root，包含一个元素
    }
}
int Find(int arr[],int x){
    if(arr[x]<0){
        return x;
    }
    else{
        arr[x]=Find(arr,arr[x]);//路径压缩
        return arr[x];
    }
}
void Union(int arr[],int a,int b){
    int rootA=Find(arr,a);
    int rootB=Find(arr,b);
    if(rootA==rootB){
        return;//已经在同一个集合中
    }
    else{
        if(arr[rootA]<arr[rootB]){
            arr[rootA]+=arr[rootB];
            arr[rootB]=rootA;
        }
        else{
            arr[rootB]+=arr[rootA];
            arr[rootA]=rootB;
        }
    }
}

int main(void){
    int arr[MAX];
    int n;
    scanf("%d",&n);
    initialize(arr,n);
    Union(arr,0,1);
    Union(arr,2,3);
    Union(arr,1,2);
    Union(arr,4,5);
    Union(arr,0,4);
    Union(arr,6,7);
    Union(arr,5,6);
    Union(arr,3,7);
    printf("1的集合的root是:%d\n",Find(arr,1));
    printf("4的集合的root是:%d\n",Find(arr,4));
    printf("6的集合的root是:%d\n",Find(arr,6));
    printf("5的集合的root是:%d\n",Find(arr,5));
    printf("7的集合的root是:%d\n",Find(arr,7));
    return 0;
}