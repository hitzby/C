/*
题目描述：
有n个人在一个水龙头前排队接水。
假设每个人接水的时间为Ti
请编程实现这n个人排队的一种顺序，使得n个人的平均等待时间最小
一个人的等待时间不包括他的接水时间
如果两个人的接水时间相同，编号更小的排在前面
*/
/*
输入：
10----------------------------------------------------------表示整数n
56 12 1 99 1000 234 33 55 99 812----------------------------第i个表示第i个人的接水时间Ti
*/
/*
输出：
3 2 7 8 1 4 9 6 10 5----------------------------------------平均时间最短的排序
291.90------------------------------------------------------平均等待时间
*/
//注意用long long 测试点整数溢出了（悲）
#include<stdio.h>
#include<stdlib.h>
typedef struct number{
	int id;
	int time;
}number;
//升序排列
int cmp(const void*a,const void*b){
	number*num_a=(number*)a;
	number*num_b=(number*)b;
	if(num_a->time>num_b->time) return 1;
	if(num_a->time<num_b->time) return -1;
	return 0;
}
double arrange(number*nums,int num){
	qsort(nums,num,sizeof(number),cmp);
	long long waiting_time=0;//此处用long long
	int i=0;
	while(i<num){
		waiting_time+=(num-(i+1))*nums[i].time;
		i++;
	}
	double result=waiting_time*1.0/num;
	return result;
}
int main(void){
	int num;
	scanf("%d",&num);
	number*nums=(number*)malloc(sizeof(number)*num);
	for(int i=0;i<num;i++){
		nums[i].id=i+1;
		scanf("%d",&nums[i].time);
	}
	double result=arrange(nums,num);
	for(int i=0;i<num;i++){
		printf("%d",nums[i].id);
		if(i!=num-1) printf(" ");
	}
	printf("\n");
	printf("%.2f\n",result);
	free(nums);
	return 0;
}
