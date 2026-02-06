/*
问题描述：
给定N个会议，每个会议的开始时间和结束时间。
最少需要多少个会议室
*/
/*
方法：
按开始时间排序，用最小堆管理结束时间
*/
/*
在这个题目中我了解了“堆”
堆我认为是一颗二叉树，且是有一定顺序排列的树
如这个题目中：堆是一个最小堆实现法，对这个二叉树有如下操作
上浮：由于最小堆是逐渐变大的（从上到下），当push时，是先插入到树叶再一一和父节点比较
下浮：删除元素时，是删去root之后将树叶放入，再一一和子节点比较
这个题采用的是malloc了一个数组，有哦与数组是从零开始，所以有i,2i+1,2i+2
*/
/*
但堆必须是一棵完全二叉树。
它的结构非常规整：除了最后一层，其他层都是满的，且最后一层的节点都靠左排列。
结论：这种规整的结构，天然就和数组是一一对应的。
*/
#include<stdio.h>
#include<stdlib.h>
typedef struct meeting{
	int id;
	int start;
	int end;
}meeting;
//最小堆的实现
typedef struct minheap{
	int *heap;
	int size;
	int capacity;
}minheap;
minheap*create(int capcity){
	minheap*heap=(minheap*)malloc(sizeof(minheap));
	heap->heap=(int*)malloc(sizeof(int)*capcity);
	heap->capacity=capcity;
	heap->size=0;
	return heap;
}
void push_heap(minheap*heap,int end){
	if(heap->size==0){
		heap->heap[heap->size++]=end;
	}
	else{
		heap->heap[heap->size++]=end;
		//进行上浮操作
		int i=heap->size-1;
		while(i>0&&heap->heap[i]<heap->heap[(i-1)/2]){
			int tmp=heap->heap[i];
			heap->heap[i]=heap->heap[(i-1)/2];
			heap->heap[(i-1)/2]=tmp;
			i=(i-1)/2;
		}
	}
	return ;
}
void pop_heap(minheap*heap){
	if(heap->size==0){
		return ;
	}
	heap->heap[0]=heap->heap[--heap->size];
	//进行下浮操作
	int i=0;
	while(i*2+1<heap->size){
		int child=i*2+1;
		if(child+1<heap->size&&heap->heap[child]>heap->heap[child+1]){
			child++;
		}
		if(heap->heap[i]<=heap->heap[child]){
			break;
		}
		else{
			int tmp=heap->heap[i];
			heap->heap[i]=heap->heap[child];
			heap->heap[child]=tmp;
			i=child;
		}
	}
	return ;
}
int peek_heap(minheap*heap){
	return heap->size>0?heap->heap[0]:-1;
}
int schedule(int capcity,meeting *mt){
	//先进行按开始时间的升序排序
	for(int i=0;i<capcity-1;i++){
		for(int j=0;j<capcity-i-1;j++){
			if(mt[j].start>mt[j+1].start){
				meeting tmp=mt[j];
				mt[j]=mt[j+1];
				mt[j+1]=tmp;
			}
		}
	}
	minheap*heap=create(capcity);
	push_heap(heap,mt[0].end);
	for(int i=1;i<capcity;i++){
		if(mt[i].start>=peek_heap(heap)){
			pop_heap(heap);
			push_heap(heap,mt[i].end);
		}
		else{
			push_heap(heap,mt[i].end);
		}
	}
	int rooms=heap->size;
	free(heap->heap);
	free(heap);
	return rooms;
}
int main(void)
{
	meeting mt[]={{1,0,30},{2,5,10},{3,15,20},{4,10,15},{5,20,25},{6,25,35}};
	int capcity=sizeof(mt)/sizeof(mt[0]);
	int result=schedule(capcity,mt);
	printf("%d",result);
	return 0;
}
