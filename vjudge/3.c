#include<stdio.h>
#include<stdlib.h>

typedef struct product{
	long long buy;
	long long number;
}product;

int cmp(const void*a,const void*b){
	product*a_1=(product*)a;
	product*b_1=(product*)b;
	if(a_1->buy > b_1->buy) return 1;
	if(a_1->buy < b_1->buy) return -1;
	return 0;
}

int main(void){
	long long n;
	scanf("%lld",&n);
	long long i=0;
	
	while(i<n){
		long long m;
		scanf("%lld",&m);
		product *products=(product*)malloc(sizeof(product)*m);
		
		for(long long j=0;j<m;j++){
			scanf("%lld %lld",&products[j].buy,&products[j].number);
		}
		
		long long front=0;
		long long rear=m-1;
		qsort(products,m,sizeof(product),cmp);
		
		long long profit=0;
		while(front < rear){
			if(products[front].number > products[rear].number){
				profit += (products[rear].buy - products[front].buy) * products[rear].number;
				products[front].number -= products[rear].number;
				rear--;
			}
			else if(products[front].number < products[rear].number){
				profit += (products[rear].buy - products[front].buy) * products[front].number;
				products[rear].number -= products[front].number;
				front++;
			}
			else { // 这里改为 else 即可，不需要再判断 ==
				profit += (products[rear].buy - products[front].buy) * products[front].number;
				front++;
				rear--;
			}
		}
		
		printf("%lld\n", profit); // 这里添加了 \n 换行符
		
		free(products);
		i++;
	}
	return 0;
}
