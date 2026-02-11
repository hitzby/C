#include <stdio.h>

#define MAX 100

// 获取数组中的最大值
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// 对数组按指定位数（exp）进行计数排序
void countSort(int arr[], int n, int exp) {
    int count[10] = {0};  // 0-9 的计数桶
    int output[n];        // 临时输出数组

    // 统计当前位上各数字出现次数
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // 将 count 转为累积计数（表示该位数字在输出数组中的位置）
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // 倒序遍历原数组，保证稳定性
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // 将排序结果复制回原数组
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// 基数排序主函数
void radixSort(int arr[], int n) {
    int max = getMax(arr, n);
    // 从个位开始，逐位排序
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSort(arr, n, exp);
    }
}

int main() {
    int arr[MAX];
    int n;

    printf("请输入元素个数: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("输入数量无效！\n");
        return 1;
    }

    printf("请输入 %d 个非负整数: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        if (arr[i] < 0) {
            printf("警告：检测到负数 %d，基数排序不支持负数！\n", arr[i]);
            return 1;
        }
    }

    radixSort(arr, n);

    printf("排序结果: ");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(" ");
    }
    printf("\n");

    return 0;
}