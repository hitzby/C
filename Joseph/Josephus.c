#include<stdio.h>
#include<stdlib.h>
typedef struct student{
	int data;
	struct student*next;
}student;
void create_node(student*head,int N){
	student*current=head;
	for(int i=1;i<=N;i++){
		student*new_node=(student*)malloc(sizeof(student));
		new_node->data=i;
		new_node->next=NULL;
		current->next=new_node;
		current=new_node;
	}
	current->next=head->next;
}
student*find_prv(student*current,student*head){
	student*prv=head;
	while(prv->next!=current){
		prv=prv->next;
	}
	return prv;
}
student*find_the_last(student*current){
	int count=0;
	student*last=current;
	student*sign=current->next;
	while(sign!=current){
		sign=sign->next;
		count++;
	}
	for(int i=1;i<=count;i++){
		last=last->next;
	}
	return last;
}
void delete_node(student*current,student*head){
	student*prv=find_prv(current,head);
	prv->next=current->next;
	if(prv==head){
	student*last=find_the_last(current);
	last->next=current->next;
	}
	free(current);
}
int play_game(int* buffer,student*head,int M){
	int i,k=0;
	student*current=head->next;
	while(head->next!=head->next->next){
		for(i=0;i<M;i++){
			current=current->next;
		}
		buffer[k++]=current->data;
		student*tmp=current;
		current=current->next;
		delete_node(tmp,head);
	}
	return head->next->data;
}
int main(void)
{
	int M,N;
	int buffer[10]={0};
	scanf("%d %d",&M,&N);
	student*head=(student*)malloc(sizeof(student));
	create_node(head,N);
	int win=play_game(buffer,head,M);
	for(int i=0;i<N-1;i++)
	printf("%d->",buffer[i]);
	printf("½áÊø\n");
	printf("%d",win);
	free(head->next);
	free(head);
	return 0;
}
