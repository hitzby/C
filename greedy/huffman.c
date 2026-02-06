/*
问题描述：
已知需要的表示的字符，要通过编码实现
如:a表示0,b表示1.....
每个字符都有相应的表示频率。要求是要事表示全部的代码所需要的总位数最小
*/
/*
解决方法是：创建一个完整的二叉树
现将要表示的字符都用根节点来表示，并且附有他的出现频率
之后进行循环，每一次挑选其中的最小的两个出现频率组合，形成一个新树，以此类推
最后将形成一个完整的树
怎么确定他的编码？对于这棵树，向左进行为零，向右进行为一。
最终得到总位数
*/
#include<stdio.h>
#include<stdlib.h>
typedef struct node{
	char data;
	int freq;
	struct node*left;
	struct node*right;
}node;
typedef struct minheap{
	node**heap;
	int size;
	int capacity;
}minheap;
//创建单个节点
node*create_node(char data,int freq){
	node*newnode=(node*)malloc(sizeof(node));
	newnode->data=data;
	newnode->freq=freq;
	newnode->left=NULL;
	newnode->right=NULL;
	return newnode;
}
//创建最小堆
minheap*create_minheap(int capacity){
	minheap*heap=(minheap*)malloc(sizeof(minheap));
	heap->heap=(node**)malloc(sizeof(node*)*capacity);
	heap->size=0;
	heap->capacity=capacity;
	return heap;
}
//在比较频率是进行互换位置
void change_position(node**left,node**right){
	node*tmp;
	tmp=*right;
	*right=*left;
	*left=tmp;
}
void minheapty(minheap*heap,int i){
	int index=i;
	int left=index*2+1;
	int right=index*2+2;
	if(left<heap->size&&heap->heap[left]->freq<heap->heap[index]->freq){
		index=left;
	}
	if(right<heap->size&&heap->heap[right]->freq<heap->heap[index]->freq){
		index=right;
	}
	if(i!=index){
		change_position(&heap->heap[i],&heap->heap[index]);
		minheapty(heap,index);
	}
}
void build_heap(minheap*heap){
	int n=heap->size-1;
	for(int i=(n-1)/2;i>=0;i--){
		minheapty(heap,i);
	}
}
node*extain(minheap*heap){
	node*min=heap->heap[0];
	heap->heap[0]=heap->heap[--heap->size];
	minheapty(heap,0);
	return min;
}
void insert(minheap*heap,node*newnode){
	heap->size++;
	int i=heap->size-1;
	while(i>0&&heap->heap[(i-1)/2]->freq>newnode->freq){
		heap->heap[i]=heap->heap[(i-1)/2];
		i=(i-1)/2;
	}
	heap->heap[i]=newnode;
}
//创建霍夫曼树
node*huffman_tree(int size,char data[],int freq[]){
	minheap*heap=create_minheap(size);
	for(int i=0;i<size;i++){
		heap->heap[i]=create_node(data[i],freq[i]);
	}
	heap->size=size;
	build_heap(heap);
	while(heap->size>1){
		node*left=extain(heap);
		node*right=extain(heap);
		node*internal=create_node('$',left->freq+right->freq);
		internal->left=left;
		internal->right=right;
		insert(heap,internal);
	}
	node*result=extain(heap);
	free(heap->heap);
	free(heap);
	return result;
}
void printf_codes(node*root,int*arr,int top){
	if(root->left){
		arr[top]=0;
		printf_codes(root->left,arr,top+1);
	}
	if(root->right){
		arr[top]=1;
		printf_codes(root->right,arr,top+1);
	}
	if(!root->left&&!root->right){
		printf("%c------",root->data);
		for(int i=0;i<top;i++){
			printf("------%d",arr[i]);
		}
		printf("\n");
	}
}
int main(void){
	char data[]={'a','b','c','d','e','f'};
	int freq[]={45,13,12,16,9,5};
	int size=sizeof(data)/sizeof(data[0]);
	node*root=huffman_tree(size,data,freq);
	int arr[100],top=0;
	printf_codes(root,arr,top);
	free(root);
	return 0;
}
