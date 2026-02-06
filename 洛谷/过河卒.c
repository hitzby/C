/*
## 题目描述
棋盘上 $A$ 点有一个过河卒，需要走到目标 $B$ 点。
卒行走的规则：可以向下、或者向右。
同时在棋盘上 $C$ 点有一个对方的马，该马所在的点和所有跳跃一步可达的点称为对方马的控制点。
因此称之为“马拦过河卒”。
棋盘用坐标表示，$A$ 点 $(0, 0)$、$B$ 点 $(n, m)$，同样马的位置坐标是需要给出的。
现在要求你计算出卒从 $A$ 点能够到达 $B$ 点的路径的条数，假设马的位置是固定不动的，并不是卒走一步马走一步。
*/
#include <stdio.h>
#include <stdlib.h>

void create_dp(int B_x, int B_y, int horse_x, int horse_y) {
	// 使用 long long 防止溢出
	long long **dp = (long long **)malloc(sizeof(long long *) * (B_x + 1));
	for (int i = 0; i <= B_x; i++) {
		dp[i] = (long long *)malloc(sizeof(long long) * (B_y + 1));
		// 初始化为 0，确保未计算的点是 0
		for (int j = 0; j <= B_y; j++) {
			dp[i][j] = 0;
		}
	}
	
	// 核心循环
	for (int i = 0; i <= B_x; i++) {
		for (int j = 0; j <= B_y; j++) {
			
			// 判断当前点 (i, j) 是否是禁区
			// 注意：这里必须用 || 连接坐标对，用 && 连接不同的点
			int isBlocked = 0;
			// 马的8个“日”字点 + 马本身
			if ((i == horse_x - 2 && j == horse_y - 1) ||
				(i == horse_x - 2 && j == horse_y + 1) ||
				(i == horse_x - 1 && j == horse_y - 2) ||
				(i == horse_x - 1 && j == horse_y + 2) ||
				(i == horse_x + 1 && j == horse_y - 2) ||
				(i == horse_x + 1 && j == horse_y + 2) ||
				(i == horse_x + 2 && j == horse_y - 1) ||
				(i == horse_x + 2 && j == horse_y + 1) ||
				(i == horse_x     && j == horse_y)) {
				isBlocked = 1;
			}
			
			if (isBlocked) {
				dp[i][j] = 0; // 禁区，不可达
			} 
			else {
				// 不是禁区，计算路径数
				if (i == 0 && j == 0) {
					dp[i][j] = 1; // 起点
				} 
				else if (i == 0) {
					dp[i][j] = dp[i][j - 1]; // 第一行
				} 
				else if (j == 0) {
					dp[i][j] = dp[i - 1][j]; // 第一列
				} 
				else {
					dp[i][j] = dp[i - 1][j] + dp[i][j - 1]; // 通用状态转移
				}
			}
		}
	}
	
	printf("%lld", dp[B_x][B_y]);
	
	// 释放内存
	for (int i = 0; i <= B_x; i++) {
		free(dp[i]);
	}
	free(dp);
}

int main(void) {
	int B_x, B_y, horse_x, horse_y;
	scanf("%d %d %d %d", &B_x, &B_y, &horse_x, &horse_y);
	create_dp(B_x, B_y, horse_x, horse_y);
	return 0;
}
