#include<stdio.h>
#include<stdlib.h>
typedef struct date{
	long long begin;
	long long end;
}date;
int main(void){
	long long n;
	scanf("%lld",&n);
	date*test=(date*)malloc(sizeof(date)*n);
	int i=0;
	long long result=0;
	while(i<n){
		scanf("%lld",&test[i].begin);
		long long skip;
		scanf("%lld",&skip);
		long long*arr=malloc(sizeof(long long)*skip);
		for(long long j=0;j<skip;j++){
			scanf("%lld",&arr[j]);
		}
		scanf("%lld",&test[i].end);
		result=test[i].end-test[i].begin+1;
		for(long long k=0;k<skip;k++){
			if(arr[k]>=test[i].begin && arr[k]<=test[i].end)
				result--;
		}
		printf("%lld\n",result);
		free(arr);
		i++;
	}
	free(test);
	return 0;
}
