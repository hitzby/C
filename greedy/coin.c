/*假设我们与不同面额的硬币，要求用最少的硬币错处给定的金额*/
/*
贪心算法的策略
1.排序：将硬币按面额从小到大排序
2.贪心选择：每次选择不超过剩余金额的最大面额
3.重复：直到凑够总金额
*/
//一下代码解决硬币系统{25，10,5,1}
#include<stdio.h>
#include<string.h>
int find_max(int total,int *arr){
	int sign=0;
	for(int i=0;i<4;i++){
		if(total>=arr[i]){
			sign=arr[i];
		}
	}
	return sign;
}
void greedy_count(int total,int *arr,int result[][4]){
	while(total!=0){
		int coin=find_max(total,arr);
		total=total-coin;
		for(int i=0;i<4;i++){
			if(arr[i]==coin){
				result[0][i]+=1;
				break;
			}
		}
	}
}
int main(void)
{
	int arr[4]={1,5,10,25};
	int total=0;
	scanf("%d",&total);
	int result[1][4];
	memset(result,0,sizeof(result));
	greedy_count(total,arr,result);
	for(int i=0;i<4;i++){
		printf("%d",result[0][i]);
	}
	return 0;
}/*
但贪心算法拥有局限性：硬币的面额只能是都是前一个的倍数

*/
