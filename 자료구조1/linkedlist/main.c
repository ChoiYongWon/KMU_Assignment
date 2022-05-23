#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
	char * value;
	struct ListNode * next;
} ListNode;

ListNode * AllocNewNode(char * value){
	ListNode * newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->value = (char *)malloc(strlen(value));
	strcpy(newNode->value, value);
	newNode->next = NULL;
	return newNode;
}

void InsertLast(ListNode ** head, char *fruit){
	if(*head == NULL){
		*head = AllocNewNode(fruit);
		printf("할당함 %s\n", (*head)->value);
		return;
	}
	ListNode * node = (*head);	
	while(1){
		if(node->next == NULL){
			node->next = AllocNewNode(fruit);
			break;
		}
		node = node->next;
	}
}

void InsertAfter(ListNode ** head, char *targetFruit, char *fruit){
	ListNode * node = (*head);
	ListNode * newNode = AllocNewNode(fruit);

	while(1){
		if(strcmp(node->value, targetFruit) == 0){
			newNode->next = node->next;
			node->next = newNode;
			break;
		}
		if(node->next==NULL){
			printf("Insert Failed (%s does not exist)\n", targetFruit);
			break;
		}

		node = node->next;
	}	

}

void PrintList(ListNode ** head){
	ListNode * node;
	for(node=*head;node!=NULL;node = node -> next){
		printf("%s ", node->value);
		if(node->next!=NULL) printf("-");
	}
	printf("\n");
}

void FreeList(ListNode ** head){
	ListNode * tmp = (*head);
	ListNode * cur;
	while(1){
		if(tmp==NULL) break;
		cur = tmp;
		tmp = cur->next;
		printf("freed %s\n", cur->value);
		free(cur->value);
		free(cur);
	}
}

int main(){
	ListNode * head = NULL;

	InsertLast(&head, "Apple"); PrintList(&head);
	InsertLast(&head, "Durian"); PrintList(&head);
	InsertAfter(&head, "Apple", "Banana"); PrintList(&head);
	InsertAfter(&head, "Tomato", "Grape"); PrintList(&head);
	InsertAfter(&head, "Banana", "Carrot"); PrintList(&head);
	
	FreeList(&head);

	return 0;
}
