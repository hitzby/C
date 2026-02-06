/*
问题简介：
这是一个环形路线加油站问题
环形路线有N个加油站，每个加油站的油量是gas[i],到下一站消耗的油量是cost[i]
判断能否绕环路一周
*/
/*
贪心策略：
如果总油量是大于等于总消耗量，则可能是有解的
*/
#include<stdio.h>
int begain(int *gas,int *cost,int n){
	int total_gas=0;
	int total_cost=0;
	for(int i=0;i<n;i++){
		total_cost+=cost[i];
		total_gas+=gas[i];
	}
	if(total_cost<=total_gas){
		printf("有可能存在解!\n");
		int current_gas=0;
		int start=0;
		for(int i=0;i<n;i++){
			current_gas=gas[i]-cost[i];
			if(current_gas<0){
				current_gas=0;
				start++;
			}
		}
		return start;
	}
	return -1;
}
void confirm(int start,int *cost,int *gas,int n){
	if(start==-1){
		return ;
	}
	int current_gas=0;
	for(int i=0;i<n;i++){
		int index=(start+i)%n;
		current_gas+=gas[index]-cost[index];
		if(current_gas<0){
			return ;
		}
	}
	printf("确认可以完成！\n");
}
int main(void){
	int gas[]={1,2,3,4,5};
	int cost[]={3,4,5,2,1};
	int n=sizeof(gas)/sizeof(gas[0]);
	int start=begain(gas,cost,n);
	confirm(start,cost,gas,n);
	return 0;
}
