#include <stdio.h>
#include <stdlib.h>

typedef struct Dequeue {
	struct ListNode * front;
	struct ListNode * rear;
	int length;
} Dequeue;

typedef struct ListNode {
	int value;
	struct ListNode * next;
	struct ListNode * prev;
} ListNode;

Dequeue * Init();
ListNode * AllocNewNode(int);
void insert_before(Dequeue *, int, int);
void insert_after(Dequeue *, int, int);
void add_front(Dequeue *, int);
void add_rear(Dequeue *, int);
int is_empty(Dequeue *);
void delete_front(Dequeue *);
void delete_rear(Dequeue *);
void delete_item(Dequeue *, int);
void print_list(Dequeue *);
void free_list(Dequeue *);

Dequeue * Init(){
	Dequeue * dequeue = (Dequeue *)malloc(sizeof(Dequeue));
	dequeue->front = NULL;
	dequeue->rear = NULL;
	dequeue->length = 0;
	return dequeue;
}

ListNode * AllocNewNode(int value){
	ListNode * newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->value = value;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

void insert_before(Dequeue * dequeue, int targetNum, int num){
	ListNode * node = dequeue->front;
	ListNode * newNode = AllocNewNode(num);

	while(1){
		if(node->value == targetNum){
			if(node->prev == NULL){ //맨 앞에 추가할시
				add_front(dequeue, num);
				break;
			}
			//새로운 노드 참조 설정
			newNode->prev = node->prev;
			newNode->next = node;

			//기존노드의 prev노드의 참조 설정
			node->prev->next = newNode;

			//기존노드의 prev 참조  설정
			node->prev = newNode;
			break;
		}
		if(node->next==NULL){
			printf("Insert Failed (%d does not exist)\n", targetNum);
			break;
		}

		node = node->next;
	}	


}

void insert_after(Dequeue * dequeue, int targetNum, int num){
	ListNode * node = dequeue->front;
	ListNode * newNode = AllocNewNode(num);

	while(1){
		if(node->value == targetNum){
			if(node->next == NULL){ //맨 앞에 추가할시
				add_rear(dequeue, num);
				break;
			}
			//새로운 노드 참조 설정
			newNode->next = node->next;
			newNode->prev = node;

			//기존노드의 next노드의 참조 설정
			node->next->prev = newNode;

			//기존노드의 next 참조 설정
			node->next = newNode;
			break;

		}
		if(node->next==NULL){
			printf("Insert Failed (%d does not exist)\n", targetNum);
			break;
		}

		node = node->next;
	}	

}

void delete_item(Dequeue * dequeue, int num){
	if(is_empty(dequeue)){
		printf("empty\n");
		return;
	}

	ListNode * node = dequeue->front;
	ListNode * tmpNode;

	while(1){
		if(node->value == num){
			if(node->next == NULL){ //맨 뒤에 요소 
				delete_rear(dequeue);
				break;
			}
			else if(node->prev == NULL){ //맨 앞에 요소 
				delete_front(dequeue);
				break;
			}
			
			ListNode * nextNode = node->next;
			ListNode * prevNode = node->prev;

			prevNode->next = nextNode;
			nextNode->prev = prevNode;

			free(node);
			dequeue->length--;
			break;

		}
		if(node->next==NULL){
			printf("Delete Failed (%d does not exist)\n", num);
			break;
		}

		node = node->next;
	}	
}

void add_front(Dequeue * dequeue, int num){
	ListNode * newNode = AllocNewNode(num);
	if(dequeue->front == NULL) {
		dequeue->front = newNode;
		dequeue->rear = newNode;
		dequeue->length++;
		return;
	}
	newNode->next = dequeue->front;
	dequeue->front->prev = newNode;
	dequeue->front = newNode;
	dequeue->length++;
	return;
}

void add_rear(Dequeue * dequeue, int num){
	ListNode * newNode = AllocNewNode(num);
	if(dequeue->rear == NULL) {
		dequeue->front = newNode;
		dequeue->rear = newNode;
		dequeue->length++;
		return;
	}
	newNode->prev = dequeue->rear;
	dequeue->rear->next = newNode;
	dequeue->rear = newNode;
	dequeue->length++;
	return;
}

int is_empty(Dequeue * dequeue){
	return (dequeue->length == 0);
}

void delete_front(Dequeue * dequeue){
	if(is_empty(dequeue)){
		printf("empty\n");
		return;
	}

	if(dequeue->front->next == NULL){//리스트가 하나밖에없는 경우
		free(dequeue->front);
		dequeue->front = NULL;
		dequeue->rear = NULL;
		dequeue->length--;
		return;
	}
	
	ListNode * tmp = dequeue->front->next;//참조를 위해 임시저장
	dequeue->front->next->prev = NULL;
	free(dequeue->front);
	dequeue->front = tmp;
	dequeue->length--;
}


void delete_rear(Dequeue * dequeue){
	if(is_empty(dequeue)){
		printf("empty\n");
		return;
	}

	if(dequeue->rear->prev == NULL){//리스트가 하나밖에없는 경우
		free(dequeue->rear);
		dequeue->rear = NULL;
		dequeue->front = NULL;
		dequeue->length--;
		return;
	}
	ListNode * tmp = dequeue->rear->prev;//참조를 위해 임시저장
	dequeue->rear->prev->next = NULL;
	free(dequeue->rear);
	dequeue->rear = tmp;
	dequeue->length--;
}

void print_list(Dequeue * dequeue){
	if(is_empty(dequeue)){
		printf("empty\n\n");
		return;
	}
	
	ListNode * node;
	for(node=dequeue->front;node!=NULL;node = node -> next){
		printf(" %d ", node->value);
		if(node->next!=NULL) printf("-");
	}
	printf("\n\n");
}

void free_list(Dequeue * dequeue){
	ListNode * tmp = dequeue->front;
	ListNode * cur;
	while(1){
		if(tmp==NULL) break;
		cur = tmp;
		tmp = cur->next;
		printf("freed %d\n", cur->value);
		free(cur);
	}
	free(dequeue);
}




int main(){
	Dequeue * dequeue = Init();
	int running = 1;
	while(running){

		printf("1. add_front\n");
		printf("2. add_rear\n");
		printf("3. delete_front\n");
		printf("4. delete_rear\n");
		printf("5. insert_after\n");
		printf("6. insert_before\n");
		printf("7. delete_item\n");
		printf("8. exit\n");
		printf("Input > ");
		int selection;
		scanf("%d", &selection);
		getchar();

		switch(selection){
			
			case 1:
				{
					int num;
					printf("num : ");
					scanf("%d", &num); getchar();
					add_front(dequeue, num);
				}
				break;

			case 2:
				{
					int num;
					printf("num : ");
					scanf("%d", &num); getchar();
					add_rear(dequeue, num);
				}
	
				break;

			case 3:
				delete_front(dequeue);
				break;

			case 4:
				delete_rear(dequeue);
				break;

			case 5:
				{
					int target, num;
					printf("input target, num : ");
					scanf("%d %d", &target, &num); getchar();
					insert_after(dequeue, target, num);
				}
				break;

			case 6:
				{
					int target, num;
					printf("input target, num : ");
					scanf("%d %d", &target, &num); getchar();
					insert_before(dequeue, target, num);

				}
				break;

			case 7:
				{
					int num;
					printf("num : ");
					scanf("%d", &num); getchar();
					delete_item(dequeue, num);

				}
				break;

			case 8:
				running = 0;
				break;

			default:

				return 0;
		}
		print_list(dequeue);
	}	
		
	free_list(dequeue);

	return 0;
}
