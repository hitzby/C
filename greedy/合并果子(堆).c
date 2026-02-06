/*
题目描述：
某人已将果园中的所有的果子打下来，并且按照不同的品种分成了不同的堆，
该人决定将所有的果子合成一堆。
在合并果子时，他消耗的体力是两堆果子的重量之和，总消耗的体力是每次合并消耗体力之和。
假设每个果子的重量都为1，并且已知每种果子的品种数和每种的数目。
任务是设计合并的次序方案，使其消耗体力最小。
*/
/*
输入：
3----------------------------------表示果子的种类数
1 2 9------------------------------表示第i种果子的数目
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
	long long *arr;
	long long size;
	long long capacity;
} MinHeap;

// 交换两个元素
void swap(long long *a, long long *b) {
	long long temp = *a;
	*a = *b;
	*b = temp;
}

// 堆化（自顶向下）
void heapify(MinHeap *heap, long long i) {
	long long smallest = i;
	long long left = 2 * i + 1;
	long long right = 2 * i + 2;
	
	if (left < heap->size && heap->arr[left] < heap->arr[smallest])
		smallest = left;
	if (right < heap->size && heap->arr[right] < heap->arr[smallest])
		smallest = right;
	
	if (smallest != i) {
		swap(&heap->arr[i], &heap->arr[smallest]);
		heapify(heap, smallest);
	}
}

// 构建最小堆
void buildHeap(MinHeap *heap) {
	for (long long i = (heap->size / 2) - 1; i >= 0; i--)
		heapify(heap, i);
}

// 提取最小元素
long long extractMin(MinHeap *heap) {
	if (heap->size <= 0) return LLONG_MAX;
	if (heap->size == 1) {
		heap->size--;
		return heap->arr[0];
	}
	
	long long root = heap->arr[0];
	heap->arr[0] = heap->arr[heap->size - 1];
	heap->size--;
	heapify(heap, 0);
	return root;
}

// 插入新元素
void insert(MinHeap *heap, long long val) {
	if (heap->size == heap->capacity) {
		heap->capacity *= 2;
		heap->arr = realloc(heap->arr, heap->capacity * sizeof(long long));
	}
	
	long long i = heap->size++;
	heap->arr[i] = val;
	
	// 自底向上调整
	while (i != 0 && heap->arr[(i - 1) / 2] > heap->arr[i]) {
		swap(&heap->arr[i], &heap->arr[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

int main() {
	long long n;
	scanf("%lld", &n);
	
	// 处理边界情况
	if (n <= 1) {
		if (n == 1) {
			long long temp;
			scanf("%lld", &temp);
		}
		printf("0");
		return 0;
	}
	
	MinHeap heap;
	heap.capacity = n;
	heap.size = 0;
	heap.arr = malloc(n * sizeof(long long));
	
	// 读入数据并构建初始堆
	for (long long i = 0; i < n; i++) {
		scanf("%lld", &heap.arr[i]);
		heap.size++;
	}
	buildHeap(&heap);
	
	long long total_cost = 0;
	
	// 哈夫曼算法核心：每次取两个最小值合并
	while (heap.size > 1) {
		long long a = extractMin(&heap);
		long long b = extractMin(&heap);
		long long sum = a + b;
		total_cost += sum;
		insert(&heap, sum);
	}
	
	printf("%lld", total_cost);
	free(heap.arr);
	return 0;
}
