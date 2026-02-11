/*2026年1月27日11:25:44---------------我终于搞明白了*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef long long ll;

// 需求区间结构体
typedef struct {
	int l, r;  // 左端点和右端点
} Requirement;

// 单调队列结构体
typedef struct {
	int *indices;  // 存储位置索引
	ll *values;    // 存储对应的dp值
	int front, rear;  // 队首和队尾指针
} MonotonicQueue;

// 初始化队列
void init_queue(MonotonicQueue *q, int size) {
	q->indices = (int *)malloc(size * sizeof(int));
	q->values = (ll *)malloc(size * sizeof(ll));
	q->front = 0;
	q->rear = 0;
}

// 向队列尾部添加元素，维护单调递增性
void push_back(MonotonicQueue *q, int idx, ll val) {
	// 维护单调递增性：如果队尾的值 >= 当前值，弹出队尾
	while (q->front < q->rear && q->values[q->rear - 1] >= val) {
		q->rear--;
	}
	q->indices[q->rear] = idx;
	q->values[q->rear] = val;
	q->rear++;
}

// 从队首弹出元素
void pop_front(MonotonicQueue *q) {
	q->front++;
}

// 获取队首元素的索引
int get_front_index(MonotonicQueue *q) {
	return q->indices[q->front];
}

// 获取队首元素的值
ll get_front_value(MonotonicQueue *q) {
	return q->values[q->front];
}

// 判断队列是否为空
int is_empty(MonotonicQueue *q) {
	return q->front == q->rear;
}

// 释放队列内存
void free_queue(MonotonicQueue *q) {
	free(q->indices);
	free(q->values);
}

// 比较函数：按右端点升序排序，右端点相同时按左端点升序排序
int compare_requirements(const void *a, const void *b) {
	Requirement *req1 = (Requirement *)a;
	Requirement *req2 = (Requirement *)b;
	if (req1->r != req2->r) {
		return req1->r - req2->r;
	}
	return req1->l - req2->l;
}

int main() {
	int T;  // 测试用例数量
	scanf("%d", &T);
	
	while (T--) {
		int n;  // 位置数量（1到n）
		scanf("%d", &n);
		
		// 分配成本数组，索引从1到n，并添加虚拟终点n+1
		ll *cost = (ll *)malloc((n + 2) * sizeof(ll));
		for (int i = 1; i <= n; i++) {
			scanf("%lld", &cost[i]);  // 读取每个位置的成本
		}
		cost[n + 1] = 0;  // 虚拟终点，成本为0
		
		int m;  // 需求区间数量
		scanf("%d", &m);
		
		// 分配需求数组
		Requirement *reqs = (Requirement *)malloc((m + 1) * sizeof(Requirement));
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &reqs[i].l, &reqs[i].r);  // 读取需求区间
		}
		
		// 按右端点排序需求区间
		qsort(reqs, m, sizeof(Requirement), compare_requirements);
		
		/* 动态规划：
		* dp[i] 表示在位置 i 放一个点，并且所有右端点 < i 的需求都已被覆盖的最小总成本
		* 最终答案是 dp[n+1]，因为 n+1 是虚拟终点
		*/
		ll *dp = (ll *)malloc((n + 2) * sizeof(ll));
		for (int i = 0; i <= n + 1; i++) {
			dp[i] = LLONG_MAX;  // 初始化为无穷大
		}
		dp[0] = 0;  // 虚拟起点，位置0，成本0
		
		// 初始化单调队列
		MonotonicQueue mq;
		init_queue(&mq, n + 2);
		push_back(&mq, 0, dp[0]);  // 将起始状态加入队列
		
		// req_index: 当前正在处理的需求索引
		// last_required: 当前必须覆盖的最左位置
		int req_index = 0;
		int last_required = 0;
		
		// 动态规划主循环：处理每个位置 i
		for (int i = 1; i <= n + 1; i++) {
			/* 步骤1: 更新必须覆盖的左边界
			* 处理所有右端点 < i 的需求，更新 last_required
			* last_required 是所有右端点 < i 的需求的左端点的最大值
			* 这意味着：前一个点必须 ≥ last_required
			*/
			while (req_index < m && reqs[req_index].r < i) {
				last_required = max(last_required, reqs[req_index].l);
				req_index++;
			}
			
			/* 步骤2: 清理队列中的过期状态
			* 队列中存储的是可能作为前驱状态的位置 j
			* 由于前一个点必须 ≥ last_required，所以移除所有索引 < last_required 的状态
			*/
			while (!is_empty(&mq) && get_front_index(&mq) < last_required) {
				pop_front(&mq);
			}
			
			/* 步骤3: 状态转移
			* 如果队列非空，队首就是最小的 dp[j]
			* dp[i] = min{dp[j]} + cost[i]，其中 j 是队列中的位置
			*/
			if (!is_empty(&mq)) {
				dp[i] = get_front_value(&mq) + cost[i];
			}
			
			/* 步骤4: 将当前状态加入队列，供后面的位置使用
			* 如果 dp[i] 有效（不是无穷大），将其加入队列
			* 加入时维护队列的单调递增性
			*/
			if (dp[i] != LLONG_MAX) {
				push_back(&mq, i, dp[i]);
			}
		}
		
		// 输出结果：dp[n+1] 就是覆盖所有需求的最小成本
		printf("%lld\n", dp[n + 1]);
		
		// 释放所有分配的内存
		free(cost);
		free(reqs);
		free(dp);
		free_queue(&mq);
	}
	
	return 0;
}
