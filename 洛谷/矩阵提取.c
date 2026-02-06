#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_M 85
#define MAX_LEN 100 // 大整数的最大位数，100位足够

// 大整数结构
typedef struct {
    int digits[MAX_LEN];
    int len;
} BigInt;

// 初始化大整数
void initBigInt(BigInt* num, int value) {
    memset(num->digits, 0, sizeof(num->digits));
    num->len = 0;
    
    if (value == 0) {
        num->len = 1;
        return;
    }
    
    while (value > 0) {
        num->digits[num->len++] = value % 10;
        value /= 10;
    }
}

// 复制大整数
void copyBigInt(const BigInt* src, BigInt* dst) {
    dst->len = src->len;
    memcpy(dst->digits, src->digits, sizeof(int) * src->len);
}

// 大整数加法
void addBigInt(const BigInt* a, const BigInt* b, BigInt* result) {
    int carry = 0;
    int maxLen = a->len > b->len ? a->len : b->len;
    int i;
    
    memset(result->digits, 0, sizeof(result->digits));
    
    for (i = 0; i < maxLen; i++) {
        int digitA = i < a->len ? a->digits[i] : 0;
        int digitB = i < b->len ? b->digits[i] : 0;
        int sum = digitA + digitB + carry;
        result->digits[i] = sum % 10;
        carry = sum / 10;
    }
    
    if (carry > 0) {
        result->digits[maxLen] = carry;
        result->len = maxLen + 1;
    } else {
        result->len = maxLen;
    }
}

// 大整数乘以整数
void mulBigIntInt(const BigInt* a, int b, BigInt* result) {
    if (b == 0) {
        initBigInt(result, 0);
        return;
    }
    
    long long carry = 0;
    int i;
    
    memset(result->digits, 0, sizeof(result->digits));
    
    for (i = 0; i < a->len; i++) {
        long long product = (long long)a->digits[i] * b + carry;
        result->digits[i] = product % 10;
        carry = product / 10;
    }
    
    result->len = a->len;
    
    while (carry > 0) {
        result->digits[result->len++] = carry % 10;
        carry /= 10;
    }
}

// 比较两个大整数
int compareBigInt(const BigInt* a, const BigInt* b) {
    if (a->len != b->len) {
        return a->len > b->len ? 1 : -1;
    }
    
    for (int i = a->len - 1; i >= 0; i--) {
        if (a->digits[i] != b->digits[i]) {
            return a->digits[i] > b->digits[i] ? 1 : -1;
        }
    }
    
    return 0;
}

// 打印大整数
void printBigInt(const BigInt* num) {
    for (int i = num->len - 1; i >= 0; i--) {
        printf("%d", num->digits[i]);
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    // 预计算2的幂
    BigInt pow2[MAX_M + 1];
    initBigInt(&pow2[0], 1);  // 2^0 = 1
    
    for (int i = 1; i <= m; i++) {
        mulBigIntInt(&pow2[i-1], 2, &pow2[i]);
    }
    
    // 总得分
    BigInt total;
    initBigInt(&total, 0);
    
    // 处理每一行
    for (int row = 0; row < n; row++) {
        int rowNums[MAX_M + 1];
        for (int i = 1; i <= m; i++) {
            scanf("%d", &rowNums[i]);
        }
        
        // DP数组，dp[l][r]表示取完区间[l,r]能获得的最大得分
        BigInt dp[MAX_M + 2][MAX_M + 2];
        
        // 初始化DP数组
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= m; j++) {
                initBigInt(&dp[i][j], 0);
            }
        }
        
        // 初始化长度为1的区间
        for (int i = 1; i <= m; i++) {
            // 只有一个元素时，是第m次取数，乘数为2^m
            mulBigIntInt(&pow2[m], rowNums[i], &dp[i][i]);
        }
        
        // 区间DP
        for (int len = 2; len <= m; len++) {
            for (int l = 1; l + len - 1 <= m; l++) {
                int r = l + len - 1;
                int step = m - len + 1;  // 当前是第几次取数
                
                // 取左端点
                BigInt leftOption, leftMul;
                mulBigIntInt(&pow2[step], rowNums[l], &leftMul);
                addBigInt(&leftMul, &dp[l+1][r], &leftOption);
                
                // 取右端点
                BigInt rightOption, rightMul;
                mulBigIntInt(&pow2[step], rowNums[r], &rightMul);
                addBigInt(&rightMul, &dp[l][r-1], &rightOption);
                
                // 选择较大的方案
                if (compareBigInt(&leftOption, &rightOption) >= 0) {
                    copyBigInt(&leftOption, &dp[l][r]);
                } else {
                    copyBigInt(&rightOption, &dp[l][r]);
                }
            }
        }
        
        // 将当前行的最大得分加到总得分
        BigInt newTotal;
        addBigInt(&total, &dp[1][m], &newTotal);
        copyBigInt(&newTotal, &total);
    }
    
    // 输出结果
    printBigInt(&total);
    printf("\n");
    
    return 0;
}
