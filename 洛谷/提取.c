/*
题目描述：
假设有N*N的方格，在这些方格中填入正整数，而其他方格填入0.
某人从左上角出发，直到右下角结束，他可以取走方格中的数。
此人从A到B总共走了两次，试找出2条这样的路径，使得他取走的数之和最大。
输入：
8--------------------意思是方格的大小为8*8
2 3 13--------------------表示在(2,3)位置填入13
2 6  6  --------------------表示在(2,6)位置填入6
3 5  7  --------------------表示在(3,5)位置填入7
4 4 14 --------------------表示在(4,4)位置填入14
5 2 21 --------------------表示在(5,2)位置填入21
5 6  4   --------------------表示在(5,6)位置填入4
6 3 15 --------------------表示在(6,3)位置填入15
7 2 14 --------------------表示在(7,2)位置填入14 
0 0  0 --------------------表示输入结束 
输出：
67-----------------------表示最大值为67
*/
#include<stdio.h>
#include<string.h>
#define MAX_N 10
int main(void){
    int N;
    int grid[MAX_N][MAX_N]={0};
    int dp[2*MAX_N][MAX_N][MAX_N]={0};
    scanf("%d",&N);
    int x,y,value;
    while(1){
        scanf("%d %d %d",&x,&y,&value);
        if(x==0&&y==0&&value==0) break;
        grid[x][y]=value;
    }
    dp[2][1][1]=grid[1][1];
    for(int i=3;i<=2*N;i++){
        for(int j=1;j<=N;j++){
            for(int k=1;k<=N;k++){
                int l=i-j;
                int m=i-k;
                if(l<1||l>N||m<1||m>N) continue;
                int current_value=grid[j][l];
                if(j!=k) current_value+=grid[k][m];
                int max_value=0;
                if(j>1&&k>1) {
                    int val=dp[i-1][j-1][k-1];
                    if(val>max_value) max_value=val;
                }
                if(j>1&&m>1) {
                    int val=dp[i-1][j-1][k];
                    if(val>max_value) max_value=val;
                }
                if(l>1&&k>1) {
                    int val=dp[i-1][j][k-1];
                    if(val>max_value) max_value=val;
                }
                if(l>1&&m>1) {
                    int val=dp[i-1][j][k];
                    if(val>max_value) max_value=val;
                }
                dp[i][j][k]=max_value+current_value;
            }
        }
    }
    printf("%d\n",dp[2*N][N][N]);
    return 0;
}