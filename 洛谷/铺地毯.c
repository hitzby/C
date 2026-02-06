/*
题目描述：
会议的组织者在会场的一片矩形区域铺上一些地毯。
假设一共是有n张地毯，编号是从1到n。想在将标号从小到大铺设
后铺设的地毯会在之前铺设的上面
组织者想要知道覆盖某些点的最上面地毯的编号
（在矩形的边界或者在四个顶点处的点也算被地毯覆盖）
*/
/*
输入样例：
3----------------表示有多少地毯
1 0 2 3----------第一个地毯，前两个表示地毯左下角的坐标，第三个表示地毯在X轴上的长度，第四个数表示地毯在Y轴上的长度
0 2 3 3 ---------同上
2 1 3 3 ---------同上
2 2 -------------表示想要知道的那个点
*/
#include<stdio.h>
#include<stdlib.h>

typedef struct carpet{
	long long a; // 左下角x坐标
	long long b; // 左下角y坐标
	long long g; // x方向长度
	long long k; // y方向长度
} carpet;

// 从后往前查找覆盖点(x,y)的最上面地毯
void find_top(long long x, long long y, carpet* cp, long long num) {
	// 从最后一张（最上面）地毯开始检查
	for (long long i = num - 1; i >= 0; i--) {
		// 检查点(x,y)是否在地毯i的范围内
		// 地毯右上角坐标为 (a+g, b+k)，边界也算覆盖
		if ((x >= cp[i].a && x <= cp[i].a + cp[i].g) && 
			(y >= cp[i].b && y <= cp[i].b + cp[i].k)) {
			printf("%lld", i + 1); // 输出地毯编号（从1开始）
			return;
		}
	}
	// 没有地毯覆盖该点
	printf("-1");
}

int main(void) {
	long long num;
	scanf("%lld", &num);
	
	carpet* cp = (carpet*)malloc(sizeof(carpet) * num);
	for (long long i = 0; i < num; i++) {
		scanf("%lld %lld %lld %lld", &cp[i].a, &cp[i].b, &cp[i].g, &cp[i].k);
	}
	
	long long x, y;
	scanf("%lld %lld", &x, &y);
	
	find_top(x, y, cp, num);
	
	free(cp);
	return 0;
}
