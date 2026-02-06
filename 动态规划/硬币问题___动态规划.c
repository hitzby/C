#include<stdio.h>
#include<string.h>
#include<limits.h>
void find(int *dp,int *coin,int amount){
	dp[0]=0;
	//我认为动态规划的本质是状态的转移，将现在考虑的状态转化为之前求解过的状态。
	for(int i=1;i<=amount;i++){
		for(int j=0;j<4;j++){
			if(coin[j]<=i){
				if(dp[i]>dp[i-coin[j]]+1){
					dp[i]=dp[i-coin[j]]+1;
				}
			}
		}
	}
}
int main(void)
{
	int amount=0;
	scanf("%d",&amount);
	int coin[4]={1,5,6,9};
	int dp[amount+1];
	for(int i=0;i<amount+1;i++){
		dp[i]=INT_MAX;
	}
	//dp[i]表示完成i所需要的面额数
	find(dp,coin,amount);
		printf("%d",dp[amount]);
	return 0;
}
