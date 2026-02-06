#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
//定义字符的储存链?
typedef struct CharNode{
	char data;
	struct CharNode*Next;
}CharNode;
//定义数字的储存链?
typedef struct IntNode{
	int data;
	struct IntNode*next;
}IntNode;
//定义字符?
typedef struct CharStack{
	CharNode*top;
	int size;
}CharStack;
//定义数字?
typedef struct IntStack{
	IntNode*top;
	int size;
}IntStack;
void push_charstack(char data,CharStack*stack,CharNode*head){
	CharNode*newnode=(CharNode*)malloc(sizeof(CharNode));
	newnode->data=data;
	newnode->Next=NULL;
	stack->top->Next=newnode;
	stack->top=newnode;
	stack->size++;
}
void push_intstack(int data,IntStack*stack,IntNode*head){
	IntNode*newnode=(IntNode*)malloc(sizeof(IntNode));
	newnode->next=NULL;
	newnode->data=data;
	stack->top->next=newnode;
	stack->top=newnode;
	stack->size++;
}
char pop_charstack(CharStack*stack,CharNode*head){
	char ch;
	CharNode*current=stack->top;
	CharNode*prv=head;
	while(prv->Next!=current){
		prv=prv->Next;
	}
	stack->top=prv;
	stack->size--;
	ch=current->data;
	free(current);
	return ch;
}
int pop_intstack(IntStack*stack,IntNode*head){
	int ch;
	IntNode*current=stack->top;
	IntNode*prv=head;
	while(prv->next!=current){
		prv=prv->next;
	}
	stack->top=prv;
	stack->size--;
	ch=current->data;
	free(current);
	return ch;
}
char peek_charstack(CharStack*stack){
	char ch;
	ch=stack->top->data;
	return ch;
}
int peek_intstack(IntStack*stack){
	int ch;
	ch=stack->top->data;
	return ch;
}
int is_op(char ch){
	if(ch=='+'||ch=='-'||ch=='*'||ch=='/'){
		return 1;
	}
	return 0;
}
int find_adv(char ch){
	switch(ch){
	case '+':
		return 1;
	case '-':
		return 1;
	case '*':
		return 2;
	case '/':
		return 2;
	default:
		return -1;
	}
	return 0;
}
void post(char *inputs,char*post_inputs,CharStack*stack,CharNode*head){
	int i,k=0;
	int len=strlen(inputs);
	for(i=0;i<len;i++){
		if(isdigit(inputs[i])){
			while(isdigit(inputs[i])){
				post_inputs[k]=inputs[i];
				k++;
				i++;
			}
			post_inputs[k]=' ';
			k++;
			i--;
		}
		else if(is_op(inputs[i])){
			if(stack->size==0){
				push_charstack(inputs[i],stack,head);
			}
			else{
				if(find_adv(inputs[i])<=find_adv(peek_charstack(stack))){
					while(find_adv(inputs[i])<=find_adv(peek_charstack(stack))){
						post_inputs[k]=pop_charstack(stack,head);
						k++;
						post_inputs[k]=' ';
						k++;
					}

					push_charstack(inputs[i],stack,head);
				}
				else{
					push_charstack(inputs[i],stack,head);
				}
			}
		}
		else if(inputs[i]=='('){
			push_charstack(inputs[i],stack,head);
		}
		else if(inputs[i]==')'){
			while(peek_charstack(stack)!='('){
				post_inputs[k]=pop_charstack(stack,head);
				k++;
				post_inputs[k]=' ';
				k++;
			}
			pop_charstack(stack,head);
		}
	}
	while(stack->size!=0){
		post_inputs[k]=pop_charstack(stack,head);
		k++;
		post_inputs[k]=' ';
		k++;
	}
	post_inputs[k]='\0';
}
int count(char*post_inputs,IntStack*stack,IntNode*head){
	int i,k=0;
	int num;
	int len=strlen(post_inputs);
	for(i=0;i<len;i++){
		if(isdigit(post_inputs[i])){
			char buffer[10];
			while(isdigit(post_inputs[i])){
				buffer[k]=post_inputs[i];
				k++;
				i++;
			}
			buffer[k]='\0';
			k=0;
			num=atoi(buffer);
			push_intstack(num,stack,head);
			i--;
		}
		else if(is_op(post_inputs[i])){
			int num_1=pop_intstack(stack,head);
			int num_2=pop_intstack(stack,head);
			int result;
			switch(post_inputs[i]){
			case '+':
				result=num_1+num_2;
				break;
			case '-':
				result=num_2-num_1;
				break;
			case '*':
				result=num_1*num_2;
				break;
			case '/':
				result=num_2/num_1;
				break;
			default:
				break;
			}
			push_intstack(result,stack,head);
		}
		else if(post_inputs[i]==' '){
			continue;
		}
	}
	int result=pop_intstack(stack,head);
	return result;
}
int main(void)
{
	char inputs[100];
	fgets(inputs,sizeof(inputs),stdin);
	inputs[strcspn(inputs,"\n")]='\0';
	//始转?
	CharNode*head=(CharNode*)malloc(sizeof(CharNode));
	head->Next=NULL;
	CharStack stack;
	stack.top=head;
	stack.size=0;
	char post_inputs[100];
	post(inputs,post_inputs,&stack,head);
	printf("%s\n",post_inputs);
	//接下来就是对后缀数进行计?
	IntNode*head_1=(IntNode*)malloc(sizeof(IntNode));
	head_1->next=NULL;
	IntStack stack_1;
	stack_1.top=head_1;
	stack_1.size=0;
	int result=count(post_inputs,&stack_1,head_1);
	printf("%d",result);
	return 0;
}
