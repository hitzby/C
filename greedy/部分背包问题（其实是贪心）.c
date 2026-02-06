/*
题目描述：
一个人走进藏宝洞，藏宝洞中有N堆金币（N<=100）,第i堆金币的总重量和总价值分别是mi,vi（1<=mi,vi<=100）。
人有一个承重量为T(T<1000)的背包，但不一定能把所有的金币带回，任何金币都可以任意分割，单位价值比不变。
请问最多可以拿走多少价值的物品
*/
/*
输入：
4 50----------表示N，T
10 60---------表示mi,vi
20 100--------同上
25 100--------同上
15 45---------同上
*/
/*
输出：240.0
计算方式：60+100+80+240.0
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int weight;
	int value;
	double ratio;
} Item;

// 比较函数，用于 qsort，按 ratio 降序
int cmp(const void *a, const void *b) {
	Item *itemA = (Item *)a;
	Item *itemB = (Item *)b;
	if (itemA->ratio < itemB->ratio) return 1;
	if (itemA->ratio > itemB->ratio) return -1;
	return 0;
}

double fractionalKnapsack(int n, int capacity, Item items[]) {
	// 计算价值密度
	for (int i = 0; i < n; i++) {
		items[i].ratio = (double)items[i].value / items[i].weight;
	}
	
	// 按价值密度降序排序
	qsort(items, n, sizeof(Item), cmp);
	
	double totalValue = 0.0;
	int currentWeight = 0;
	
	for (int i = 0; i < n; i++) {
		if (currentWeight + items[i].weight <= capacity) {
			// 全部拿走
			currentWeight += items[i].weight;
			totalValue += items[i].value;
		} else {
			// 拿走一部分
			int remain = capacity - currentWeight;
			totalValue += items[i].ratio * remain;
			break; // 背包满了
		}
	}
	
	return totalValue;
}

int main() {
	int n, capacity;
	scanf("%d", &n);
	scanf("%d", &capacity);
	
	Item *items = (Item *)malloc(n * sizeof(Item));
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &items[i].weight, &items[i].value);
	}
	
	double result = fractionalKnapsack(n, capacity, items);
	printf("%.2f\n", result);
	
	free(items);
	return 0;
}
