#include<stdio.h>
#define MAX 1000
enum shell_type{
    shell_original=1,
    shell_hibbard,
    shell_knuth,
    shell_sedgewick
};
void shellsort_original(int arr[],int n);
void shellsort_hibbard(int arr[],int n);
void shellsort_knuth(int arr[],int n);
void shellsort_sedgewick(int arr[],int n);
void shellsort(int arr[],int n,int type){
    switch(type){
        case shell_original:
        shellsort_original(arr,n);
        break;
        case shell_hibbard:
        shellsort_hibbard(arr,n);
        break;
        case shell_knuth:
        shellsort_knuth(arr,n);
        break;
        case shell_sedgewick:
        shellsort_sedgewick(arr,n);
        break;
        default:
        shellsort_original(arr,n);
        break;
    }
}
void shellsort_original(int arr[],int n){
    for(int gap=n/2;gap>0;gap/=2){
        for(int i=gap;i<n;i++){
            int tmp=arr[i];
            int j;
            for(j=i;j>=gap;j-=gap){
                if(arr[j-gap]>tmp){
                    arr[j]=arr[j-gap];
                }
                else{break;}
            }
            arr[j]=tmp;
        }
    }
}
void shellsort_hibbard(int arr[],int n){
    int count=1;
    while((1<<count)-1<n){
        count++;
    }
    count--;
    for(;count>0;count--){
        int gap=(1<<count)-1;
        for(int i=gap;i<n;i++){
            int tmp=arr[i];
            int j;
            for(j=i;j>=gap;j-=gap){
                if(arr[j-gap]>tmp){
                    arr[j]=arr[j-gap];
                }
                else{break;}
            }
            arr[j]=tmp;
        }
    }
}
void shellsort_knuth(int arr[],int n){
    int gap=1;
    while(gap<n/3){
        gap=gap*3+1;
    }
    for(;gap>0;gap=(gap-1)/3){
        for(int i=gap;i<n;i++){
            int tmp=arr[i];
            int j;
            for(j=i;j>=gap;j-=gap){
                if(arr[j-gap]>tmp){
                    arr[j]=arr[j-gap];
                }
                else{break;}
            }
            arr[j]=tmp;
        }
    }
}
void shellsort_sedgewick(int arr[],int n){
    int sedgewick_gaps[]={1,5,19,41,109,209,505,929,2161,3905,8929,16001,36289,64769,146305,260609};
    int count=0;
    while(sedgewick_gaps[count]<n){
        count++;
    }
    count--;
    for(;count>=0;count--){
        int gap=sedgewick_gaps[count];
        for(int i=gap;i<n;i++){
            int tmp=arr[i];
            int j;
            for(j=i;j>=gap;j-=gap){
                if(arr[j-gap]>tmp){
                    arr[j]=arr[j-gap];
                }
                else{break;}
            }
            arr[j]=tmp;
        }
    }
}

int main(void){
    int arr[MAX]={0};
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    int type;
    scanf("%d",&type);
    shellsort(arr,n,type);
    for(int i=0;i<n;i++){
        printf("%d",arr[i]);
        if(i!=n-1){
            printf(" ");
        }
    }
    printf("\n");
    return 0;
}
/*如果想满足健壮性参考以下代码*/
/*
#include<stdio.h>
#include<stdlib.h>  // 用于exit()
#define MAX 1000

enum shell_type {
    shell_original = 1,
    shell_hibbard,
    shell_knuth,
    shell_sedgewick
};

// 函数声明
void shellsort_original(int arr[], int n);
void shellsort_hibbard(int arr[], int n);
void shellsort_knuth(int arr[], int n);
void shellsort_sedgewick(int arr[], int n);
void shellsort(int arr[], int n, int type);

void shellsort(int arr[], int n, int type) {
    // 检查数组大小
    if (n <= 1) return;
    
    switch(type) {
        case shell_original:
            shellsort_original(arr, n);
            break;
        case shell_hibbard:
            shellsort_hibbard(arr, n);
            break;
        case shell_knuth:
            shellsort_knuth(arr, n);
            break;
        case shell_sedgewick:
            shellsort_sedgewick(arr, n);
            break;
        default:
            printf("Warning: Unknown shell type %d, using original shell sort.\n", type);
            shellsort_original(arr, n);
            break;
    }
}

void shellsort_original(int arr[], int n) {
    if (n <= 1) return;
    
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int tmp = arr[i];
            int j = i;
            while (j >= gap && arr[j-gap] > tmp) {
                arr[j] = arr[j-gap];
                j -= gap;
            }
            arr[j] = tmp;
        }
    }
}

void shellsort_hibbard(int arr[], int n) {
    if (n <= 1) return;
    
    int k = 1;
    // 找到满足 2^k - 1 < n 的最大k
    while ((1 << k) - 1 < n) {
        k++;
    }
    k--; // 最大的 k 满足 2^k - 1 < n
    
    // 特殊情况处理
    if (k < 1) {
        k = 1; // 至少使用gap=1
    }
    
    while (k >= 1) {
        int gap = (1 << k) - 1;
        // 确保gap有效且小于n
        if (gap <= 0 || gap >= n) {
            k--;
            continue;
        }
        
        for (int i = gap; i < n; i++) {
            int tmp = arr[i];
            int j = i;
            while (j >= gap && arr[j-gap] > tmp) {
                arr[j] = arr[j-gap];
                j -= gap;
            }
            arr[j] = tmp;
        }
        k--;
    }
}

void shellsort_knuth(int arr[], int n) {
    if (n <= 1) return;
    
    int gap = 1;
    while (gap < n / 3) {
        gap = gap * 3 + 1;
    }
    
    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            int tmp = arr[i];
            int j = i;
            while (j >= gap && arr[j-gap] > tmp) {
                arr[j] = arr[j-gap];
                j -= gap;
            }
            arr[j] = tmp;
        }
        gap = (gap - 1) / 3;
    }
}

void shellsort_sedgewick(int arr[], int n) {
    if (n <= 1) return;
    
    int sedgewick_gaps[] = {1,5,19,41,109,209,505,929,2161,3905,
                           8929,16001,36289,64769,146305,260609};
    int num_gaps = sizeof(sedgewick_gaps) / sizeof(sedgewick_gaps[0]);
    
    // 找到第一个小于n的gap
    int k = 0;
    while (k < num_gaps && sedgewick_gaps[k] < n) {
        k++;
    }
    
    // 调整k为小于n的最大gap索引
    if (k > 0) {
        k--;
    } else {
        // 所有gap都>=n，使用最小的gap（1）
        k = 0;
        // 但如果最小的gap（1）>=n，说明n=0或1，直接返回
        if (sedgewick_gaps[k] >= n) {
            return; // 数组已经有序
        }
    }
    
    // 使用找到的gap进行排序
    for (; k >= 0; k--) {
        int gap = sedgewick_gaps[k];
        // 安全检查
        if (gap <= 0 || gap >= n) continue;
        
        for (int i = gap; i < n; i++) {
            int tmp = arr[i];
            int j = i;
            while (j >= gap && arr[j-gap] > tmp) {
                arr[j] = arr[j-gap];
                j -= gap;
            }
            arr[j] = tmp;
        }
    }
}

// 安全的输入函数
int safe_input_int(int *value, const char *prompt) {
    printf("%s", prompt);
    if (scanf("%d", value) != 1) {
        printf("Input error!\n");
        return 0; // 失败
    }
    return 1; // 成功
}

int main(void) {
    int arr[MAX] = {0};
    int n, type;
    
    // 安全地读取数组大小
    if (!safe_input_int(&n, "Enter array size (1-1000): ")) {
        return 1;
    }
    
    // 验证数组大小
    if (n <= 0 || n > MAX) {
        printf("Error: Array size must be between 1 and %d.\n", MAX);
        return 1;
    }
    
    // 读取数组元素
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Error reading element %d.\n", i);
            return 1;
        }
    }
    
    // 读取排序类型
    printf("Select sort type:\n");
    printf("1. Original Shell Sort\n");
    printf("2. Hibbard Sequence\n");
    printf("3. Knuth Sequence\n");
    printf("4. Sedgewick Sequence\n");
    printf("Enter choice (1-4): ");
    
    if (scanf("%d", &type) != 1) {
        printf("Error reading sort type.\n");
        return 1;
    }
    
    // 执行排序
    shellsort(arr, n, type);
    
    // 输出结果
    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i != n-1) printf(" ");
    }
    printf("\n");
    
    return 0;
}
*/