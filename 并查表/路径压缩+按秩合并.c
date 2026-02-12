#include<stdio.h>

#define MAX 100
void initialize(int n,int parent[],int rank[]){
    for(int i=0;i<n;i++){
        parent[i]=i;
        rank[i]=1;//0和1背后的逻辑是一样的
    }
}
int find(int parent[],int x){
    if(parent[x]!=x){
        parent[x]=find(parent,parent[x]);//路径压缩
    }
    return parent[x];
}
void Union(int parent[],int rank[],int x,int y){
    int rootX=find(parent,x);
    int rootY=find(parent,y);
    if(rootX==rootY){
        return;
    }
    if(rank[rootX]<rank[rootY]){
        parent[rootX]=rootY;//rootY的高度不变，因为rootY吞并的是比它矮的树
    }
    else if(rank[rootX]>rank[rootY]){
        parent[rootY]=rootX;//rootX的高度不变，因为rootX吞并的是比它矮的树
    }
    else{
        parent[rootX]=rootY;//rootX和rootY的高度相同，任意一个当做新的根都行
        rank[rootY]++;//因为rootX和rootY的高度相同，所以当它们合并成一棵树时，新的树的高度就比原来高1了
    }
}
int main(void){
    int parent[MAX];
    int rank[MAX];//这里的rank表示树高度的上限
    int n;
    scanf("%d",&n);
    initialize(n,parent,rank);
    Union(parent,rank,0,1);
    Union(parent,rank,2,3);
    Union(parent,rank,1,2);
    Union(parent,rank,4,5);
    Union(parent,rank,0,4);
    Union(parent,rank,6,7);
    Union(parent,rank,5,6);
    Union(parent,rank,3,7);
    printf("1的集合的root是:%d\n",find(parent,1));
    printf("4的集合的root是:%d\n",find(parent,4));
    printf("6的集合的root是:%d\n",find(parent,6));
    printf("5的集合的root是:%d\n",find(parent,5));
    printf("7的集合的root是:%d\n",find(parent,7));
    return 0;
}