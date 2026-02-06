/*
问题描述：
给定N个活动，每个活动有开始时间，有结束时间
来选择最大的互不重叠的活动集合
*/
/*
贪心算法策略：
按结束时间排序，每次选择结束最早且不与已选活动冲突的活动
*/
#include<stdio.h>
typedef struct activity{
	int num;
	int begin;
	int end;
}activity;
int choose(activity*ac,int n){
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-i-1;j++){
			if(ac[j].end>ac[j+1].end){
				activity tmp;
				tmp=ac[j];
				ac[j]=ac[j+1];
				ac[j+1]=tmp;
				//冒泡排序进行升序排列
			}
		}
	}
	//开始选择
	activity last_find=ac[0];
	int count=1;
	for(int i=1;i<n;i++){
		if(ac[i].begin>=last_find.end){
			count++;
			last_find=ac[i];
		}
	}
	return count;
}
int main(void)
{
	activity ac[]={{1,1,4},{2,3,5},{3,0,6},{4,5,7},{5,3,9},{6,5,9},{7,6,10},{8,8,11},{9,8,12},{10,2,14},{11,12,16}};
	int n=sizeof(ac)/sizeof(ac[0]);
	int result=choose(ac,n);
	printf("%d",result);
	return 0;
}
