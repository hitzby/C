#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct tree{
	char data;
	struct tree*left;
	struct tree*right;
}tree;
typedef struct stack{
	tree*adress;
	struct stack*next;
	struct stack*top;
	
}stack;
void push_stack(stack*st,tree*tr){
	stack*current=st->top;
	stack*newnode=(stack*)malloc(sizeof(newnode));
	newnode->adress=tr;
	newnode->next=NULL;
	current->next=newnode;
	st->top=newnode;
}
stack*findprv(stack*st,stack*current){
	stack*prv=st;
	while(prv->next!=current){
		prv=prv->next;
	}
	return prv;
}
tree*pop(stack*st){
	stack*current=st->top;
	stack*prv=findprv(st,current);
	prv->next=NULL;
	st->top=prv;
	tree*data=current->adress;
	free(current);
	return data;
}
tree*peek(stack*st){
	return st->top->adress;
}
tree*new_tree(void){
	tree*current=(tree*)malloc(sizeof(tree));
	current->left=NULL;
	current->right=NULL;
	return current;
}
tree* create_tree(stack*st,char*index){
	int i=0;
	int len=strlen(index);
	for(i=0;i<len;i++){
		if(isdigit(index[i])){
			tree*tr=new_tree();
			tr->data=index[i];
			push_stack(st,tr);
		}
		else{
			tree*second=pop(st);
			tree*first=pop(st);
			tree*tr=new_tree();
			tr->left=first;
			tr->right=second;
			tr->data=index[i];
			push_stack(st,tr);
		}
	}
	tree*root=pop(st);
	return root;
}
int count(tree*root){
	if(root->left==NULL&&root->right==NULL){
		return (root->data-'0');
	}
	int left_count=count(root->left);
	int right_count=count(root->right);
	switch(root->data){
	case '+':
		return left_count+right_count;
	case '-':
		return left_count+right_count;
	case '*':
		return left_count*right_count;
	case '/':
		return left_count/right_count;
	}
	return 0;
}
int main(void)
{
	stack *st=(stack*)malloc(sizeof(stack));
	st->next=NULL;
	st->top=st;
	char index[100]={0};
	fgets(index,sizeof(index),stdin);
	index[strcspn(index,"\n")]='\0';
	tree*root= create_tree(st,index);
	int result=count(root);
	printf("%d",result);
	return 0;
}
