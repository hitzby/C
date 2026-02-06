/*
题目描述：
在各大oj平台上有n个比赛，每个比赛的开始结束时间是知道的
我想知道最多可以参加几个比赛
如果要参加一个比赛必须善始善终，而且不可以同时参加多个比赛
*/
/*
输入:
3-----------------一个整数，表示有多少个比赛
0 2---------------表示比赛的开始时间，和结束时间
2 4---------------同上
1 3---------------同上
*/
/*
输出：
2-----------------表示最多可以参加的比赛数
*/
/*
贪心策略：
对比赛的开始时间进行升序排列，
*/
#include<stdio.h>
#include<stdlib.h>
typedef struct contest{
	int start;
	int end;
}contest;
// 修改比较函数：按结束时间排序
int cmp(const void*a,const void*b){
	contest*test_a=(contest*)a;
	contest*test_b=(contest*)b;
	if(test_a->end > test_b->end) return 1;
	else if(test_a->end < test_b->end) return -1;
	else return 0; // 结束时间相同时，可以考虑按开始时间排序
}

// 修正选择逻辑
int choose_contest(contest*test,int number){
	qsort(test,number,sizeof(contest),cmp);
	if(number == 0) return 0;
	
	int count = 1; // 至少可以选择第一个活动
	int last_end = test[0].end; // 上一个选中活动的结束时间
	
	for(int i=1; i<number; i++){
		if(test[i].start >= last_end){
			count++; // 选择这个活动
			last_end = test[i].end; // 更新最后结束时间
		}
	}
	return count;
}
int main(void){
	int number;
	scanf("%d",&number);
	contest*test=(contest*)malloc(sizeof(contest)*number);
	for(int i=0;i<number;i++){
		scanf("%d %d",&test[i].start,&test[i].end);
	}
	int result=choose_contest(test,number);
	printf("%d",result);
	free(test);
	return 0;
}
