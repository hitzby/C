#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 2^32 覆盖了所有 int 范围的节点数，足以应对任意大小
#define MAX_RANK 32 

typedef struct Binnode {
    int key;
    struct Binnode *child;
    struct Binnode *sibling;
} Binnode;

typedef struct Bintree {
    struct Binnode **trees; 
} Bintree;

typedef struct Binqueue {
    int current_size;
    struct Bintree **queue;
} Binqueue;

// 检查是否为2的幂
int isPowerOfTwo(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

// 核心：合并两个同秩的树
Binnode *combine(Binnode *b1, Binnode *b2) {
    if (b1->key > b2->key) {
        return combine(b2, b1);
    }
    b2->sibling = b1->child;
    b1->child = b2;
    return b1;
}

// 核心：合并两个队列 (二进制加法逻辑)
Bintree *merge(Bintree *b1, Bintree *b2) {
    Binnode *t1, *t2, *carry = NULL;
    int i;
    
    for (i = 0; i < MAX_RANK; i++) {
        t1 = b1->trees[i];
        t2 = b2->trees[i];

        // 优化：如果两者都为空且无进位，后续无需处理
        if(t1 == NULL && t2 == NULL && carry == NULL) continue;

        int state = ((t1 != NULL) ? 1 : 0) + ((t2 != NULL) ? 2 : 0) + ((carry != NULL) ? 4 : 0);

        switch (state) {
            case 0: break;
            case 1: break; // 只有t1，保留在b1
            case 2: // 只有t2，移入b1
                b1->trees[i] = t2;
                b2->trees[i] = NULL;
                break;
            case 3: // t1 + t2 -> 进位
                carry = combine(t1, t2);
                b1->trees[i] = NULL;
                b2->trees[i] = NULL;
                break;
            case 4: // 只有carry，落入b1
                b1->trees[i] = carry;
                carry = NULL;
                break;
            case 5: // t1 + carry -> 进位
                carry = combine(t1, carry);
                b1->trees[i] = NULL;
                break;
            case 6: // t2 + carry -> 进位
                carry = combine(t2, carry);
                b1->trees[i] = NULL;
                b2->trees[i] = NULL;
                break;
            case 7: { // <--- 修复点：加上花括号
                // t1 + t2 + carry -> t1保留, 新进位
                Binnode *tmp = carry;
                carry = combine(t1, t2);
                b1->trees[i] = tmp;
                b2->trees[i] = NULL;
                break;
            } // <--- 修复点：加上花括号
        }
    }
    return b1;
}

void printBinnode(Binnode *bn) {
    if (bn == NULL) return;
    printf("%d ", bn->key);
    printBinnode(bn->child);
    printBinnode(bn->sibling);
}

int main(void) {
    int n;
    // 如果是任意队列合并，建议把n改为循环
    if (scanf("%d", &n) != 1) return 0;
    
    Binqueue *bq = (Binqueue *)malloc(sizeof(Binqueue));
    bq->current_size = n;
    bq->queue = (Bintree **)malloc(sizeof(Bintree *) * n);
    
    int queue_idx = 0;
    
    // 读取 n 个队列
    while (queue_idx < n) {
        int m = 0;
        scanf("%d", &m); // 该队列有多少个二项树
        
        Bintree *bt = (Bintree *)malloc(sizeof(Bintree));
        bt->trees = (Binnode **)calloc(MAX_RANK, sizeof(Binnode *));
        
        for (int i = 0; i < m; i++) {
            int k, root_key;
            scanf("%d %d", &k, &root_key);
            
            // 安全检查：二项树的大小必须是 2 的幂
            if (!isPowerOfTwo(k)) {
                printf("Error: Tree size %d is not a power of 2. Invalid Binomial Tree.\n", k);
                return -1;
            }

            // 计算 Rank
            int rank = 0;
            int temp_k = k;
            while(temp_k > 1) {
                temp_k >>= 1;
                rank++;
            }

            Binnode *bn = (Binnode *)malloc(sizeof(Binnode));
            bn->key = root_key;
            bn->child = NULL;
            bn->sibling = NULL;
            
            // 保持你的输入构建逻辑
            int count = k;
            Binnode *cursor = bn;
            while (--count) {
                int child_key;
                scanf("%d", &child_key);
                Binnode *new_node = (Binnode *)malloc(sizeof(Binnode));
                new_node->key = child_key;
                new_node->child = NULL;
                new_node->sibling = NULL;
                
                if (cursor->child == NULL) {
                    cursor->child = new_node;
                } else {
                    cursor->child->sibling = new_node;
                    cursor = cursor->child;
                }
            }
            // 放入对应的 Rank 位置
            bt->trees[rank] = bn;
        }
        bq->queue[queue_idx++] = bt;
    }

    // 合并逻辑：将所有队列合并到第一个队列中
    // 这样支持任意 n 个队列的合并
    for (int i = 1; i < n; i++) {
        bq->queue[0] = merge(bq->queue[0], bq->queue[i]);
    }

    // 输出结果
    // 遍历所有可能的 Rank
    for (int i = 0; i < MAX_RANK; i++) {
        if (bq->queue[0]->trees[i] != NULL) {
            printf("-----------------\n");
            // 这里可以打印出Rank信息，方便调试
            // printf("Rank %d:\n", i); 
            printBinnode(bq->queue[0]->trees[i]);
            printf("\n");
        }
    }
    
    return 0;
}