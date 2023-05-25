#include <stdio.h>
#include <stdlib.h>

/*정수, 왼쪽자식노드의 주소, 오른쪽자식노드의 주소를 갖는 노드구조체를 선언*/
typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);
void inorderTraversal(Node* ptr);	  
void preorderTraversal(Node* ptr);   
void postorderTraversal(Node* ptr);	  
int insert(Node* head, int key);  
int deleteLeafNode(Node* head, int key);  
Node* searchRecursive(Node* ptr, int key);  
Node* searchIterative(Node* head, int key); 
int freeBST(Node* head); 


int main()
{
	printf("[----- [오인화] [2022078036] -----]");

	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/*노드를 초기화 하는 함수*/
int initializeBST(Node** h) {

	/*빈 트리가 아니라면 모든 노드의 메모리를 해제한다*/
	if(*h != NULL)
		freeBST(*h);

	/*헤드노드 선언*/
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

/*inorder방식으로 트리를 탐색해 출력하는 함수*/
void inorderTraversal(Node* ptr)
{
    /*left가 NULL일 때까지 왼쪽 노드로 이동하고 
    마지막 왼쪽 노드일 경우에 출력 후 부모노드를 출력하고 오른쪽 노드를 출력한다*/
	if(ptr) {
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

/*preorder방식으로 트리를 탐색해 출력하는 함수*/
void preorderTraversal(Node* ptr)
{
    /*먼저 노드의 값을 출력하고 왼쪽노드로 하나씩 이동하며 출력한다.
    마지막 왼쪽노드까지 출력했을 경우 오른쪽 노드를 하나씩 출력한다.*/
	if(ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

/*postorder방식으로 트리를 탐색해 출력하는 함수*/
void postorderTraversal(Node* ptr)
{
    /*마지막 왼쪽 노드를 출력하고 부모의 오른쪽 노드, 부모 노드 순으로 올라가며 출력한다*/
	if(ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}

/*노드를 삽입하는 함수*/
int insert(Node* head, int key)
{
    /*삽입할 노드 선언*/
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

    /*빈 트리인 경우 헤드노드 옆에 노드 삽입*/
	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/*ptr이 헤드노드의 왼쪽자식노드를 가리킨다*/
	Node* ptr = head->left;

	Node* parentNode = NULL;

    /*마지막 노드까지 반복*/
	while(ptr != NULL) {

		/*같은 값을 가진 노드가 있을 경우 함수 종료*/
		if(ptr->key == key) return 1;

		/*ptr이 가리키는 노드를 부모노드로 설정*/
		parentNode = ptr;

		/*ptr이 가리키는 노드의 값보다 클 경우 오른쪽자식노드로 이동*/
		if(ptr->key < key)
			ptr = ptr->right;
        /*ptr이 가리키는 노드의 갑보다 작을 경우 왼쪽자식노드로 이동*/
		else
			ptr = ptr->left;
	}

	/*부모노드의 값이 클 경우, 새로운 노드를 왼쪽 자식 노드로 설정*/
	if(parentNode->key > key)
		parentNode->left = newNode;
    /*부모노드의 값이 작을 경우, 새로운 노드를 오른쪽 자식 노드로 설정*/
	else
		parentNode->right = newNode;
	return 1;
}

/*leaf노드를 제거하는 함수*/
int deleteLeafNode(Node* head, int key)
{
    /*빈 트리일 경우, 함수 종료*/
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

    /*헤드노드의 왼쪽 자식노드가 없을 경우 함수 종료*/
	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	Node* ptr = head->left;
	Node* parentNode = head;

	while(ptr != NULL) {
        /*삭제할 노드를 찾았을 경우*/
		if(ptr->key == key) {
            /*leaf노드일 경우*/
			if(ptr->left == NULL && ptr->right == NULL) {

				/*부모노드가 헤드노드일 경우, 헤드노드와 왼쪽자식노드의 연결을 끊는다*/
				if(parentNode == head)
					head->left = NULL;

				/*부모노드의 오른쪽노드가 ptr일 경우*/
				if(parentNode->left == ptr)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;

				free(ptr);
			}
            /*leaf노드가 아닐 경우, leaf노드가 아니라는 메세지 출력*/
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

        /*부모노드를 ptr이 가리키는 노드로 변경*/
		parentNode = ptr;

        /*ptr이 가리키는 노드의 값이 제거할 노드의 값보다 작을 경우, ptr이 오른쪽자식노드를 가리킨다*/
		if(ptr->key < key)
			ptr = ptr->right;
        /*ptr이 가리키는 노드의 값이 제거할 노드의 값보다 클 경우, ptr이 왼쪽자식노드를 가리킨다*/
		else
			ptr = ptr->left;


	}

    /*제거할 노드가 없을 경우 찾을 수 없다는 메세지 출력*/
	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

/*recursive방식으로 노드를 찾는 함수*/
Node* searchRecursive(Node* ptr, int key)
{
	/*빈 트리일 경우 NULL 반환*/
	if(ptr == NULL)
		return NULL;

	/*ptr이 가리키는 노드의 값이 key보다 작을 경우 ptr의 오른쪽 노드 탐색*/
	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	/*ptr이 가리키는 노드의 값이 key보다 클 경우 ptr의 왼쪽 노드 탐색*/
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	/*key값을 갖는 노드를 찾았을 경우 포인터 반환*/
	return ptr;

}

/*interative방식으로 노드를 찾는 함수*/
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;

	/*leaf노드에 도달할 때까지 반복*/
	while(ptr != NULL)
	{
		/*key를 찾았을 경우 그 노드의 주소 반환*/
		if(ptr->key == key)
			return ptr;
		/*ptr이 가리키는 노드의 값이 key보다 작을 경우 오른쪽 노드 탐색*/
		if(ptr->key < key) ptr = ptr->right;
		/*ptr이 가리키는 노드의 값이 key보다 클 경우 왼쪽 노드 탐색*/
		else
			ptr = ptr->left;
	}

	return ptr;
}

/*노드의 메모리를 해제하는 함수*/
void freeNode(Node* ptr)
{
	/*leaf노드가 나올때까지 함주를 recursive하고 
	왼쪽 오른쪽 순서로 헤드노드 이외의 모든 노드의 메모리를 해제한다*/
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

/*트리의 메모리를 해제하는 함수*/
int freeBST(Node* head)
{

	/*헤드노드만 있는 트리일 경우, 헤드노드의 메모리를 해제하고 함수 종료*/
	if(head->left == head)
	{
		free(head);
		return 1;
	}

	/*왼쪽자식노드부터 탐색하며 메모리를 해제한다*/
	Node* p = head->left;
	freeNode(p);

	/*헤드노드의 메모리 해제*/
	free(head);
	
	return 1;
}

