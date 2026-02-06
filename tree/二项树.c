/*
二项树是一个通过堆来实现的数据结构，来实现优先队列。
以下代码展示的是二项树的合并操作
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct Binnode{
    int key;
    struct Binnode *child;
    struct Binnode *sibling;
}Binnode;
typedef struct Binqueue{
    int current_size;
    struct Bintree **queue;
}Binqueue;
typedef struct Bintree{
    struct Binnode **trees;
    int size;
}Bintree;
Binnode *combine(Binnode *b1,Binnode *b2){
    if(b1->key>b2->key){
        return combine(b2,b1);
    }
    b2->sibling=b1->child;
    b1->child=b2;
    return b1;
}
Bintree *merge(Bintree *b1,Bintree *b2){
    Binnode *t1,*t2,*carry=NULL;
    int i,j;
    b1->size+=b2->size;
    for(i=0,j=1;j<=b1->size;i++,j*=2){
        t1=(i<b1->size&&b1->trees[i]!=NULL)?b1->trees[i]:NULL;
        t2=(i<b2->size&&b2->trees[i]!=NULL)?b2->trees[i]:NULL;
        switch(((t1!=NULL)?1:0)+((t2!=NULL)?2:0)+((carry!=NULL)?4:0)){
            case 0:
            case 1:
                break;
            case 2:
                b1->trees[i]=t2;
                b2->trees[i]=NULL;
                break;
            case 4:
                b1->trees[i]=carry;
                carry=NULL;
                break;
            case 3:
                carry=combine(t1,t2);
                b1->trees[i]=b2->trees[i]=NULL;
                break;
            case 5:
                carry=combine(t1,carry);
                b1->trees[i]=NULL;
                break;
            case 6:
                carry=combine(t2,carry);
                b2->trees[i]=NULL;
                break;
            case 7:
                b1->trees[i]=carry;
                carry=combine(t1,t2);
                b2->trees[i]=NULL;
                break;
        }
    }
    return b1;
}
void printBinnode(Binnode *bn){
    if(bn==NULL) return;
    printf("%d ",bn->key);
    printBinnode(bn->child);
    printBinnode(bn->sibling);
}
int main(void){
    int n;
    scanf("%d",&n);
    Binqueue *bq=(Binqueue *)malloc(sizeof(Binqueue));
    bq->current_size=n;
    bq->queue=(Bintree **)malloc(sizeof(Bintree *)*n);
    while(n--){ 
		int m=0;
		static int idx=0;
        scanf("%d",&m);
        Bintree *bt=(Bintree *)malloc(sizeof(Bintree));
        bt->size=m;
        bt->trees=(Binnode **)malloc(sizeof(Binnode *)*m);
        for(int i=0;i<m;i++){
            int k,key;
            scanf("%d %d",&k,&key);
            Binnode *bn=(Binnode *)malloc(sizeof(Binnode));
            bn->key=key;
            bn->child=NULL;
            bn->sibling=NULL;
            while(--k){
                Binnode *tmp=bn;
                Binnode *new=(Binnode *)malloc(sizeof(Binnode));
                int key;
                scanf("%d",&key);
                new->key=key;
                new->child=NULL;
                new->sibling=NULL;
                if(tmp->child==NULL){
                    tmp->child=new;
                }
                else{
                    tmp->child->sibling=new;
                    tmp=tmp->child;
                }
            }
            bt->trees[i]=bn;
        }
        bq->queue[idx++]=bt;
    }
    //开始合并
    bq->queue[0]=merge(bq->queue[0],bq->queue[1]);
    bq->current_size--;
    for(int i=0;i<bq->queue[0]->size;i++){
        printf("-----------------\n");
        printBinnode(bq->queue[0]->trees[i]);
        printf("\n");
        }
    return 0;
}
