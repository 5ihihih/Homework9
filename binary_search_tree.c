#include <stdio.h>
#include <stdlib.h>

/*����, �����ڽĳ���� �ּ�, �������ڽĳ���� �ּҸ� ���� ��屸��ü�� ����*/
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
	printf("[----- [����ȭ] [2022078036] -----]");

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

/*��带 �ʱ�ȭ �ϴ� �Լ�*/
int initializeBST(Node** h) {

	/*�� Ʈ���� �ƴ϶�� ��� ����� �޸𸮸� �����Ѵ�*/
	if(*h != NULL)
		freeBST(*h);

	/*����� ����*/
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

/*inorder������� Ʈ���� Ž���� ����ϴ� �Լ�*/
void inorderTraversal(Node* ptr)
{
    /*left�� NULL�� ������ ���� ���� �̵��ϰ� 
    ������ ���� ����� ��쿡 ��� �� �θ��带 ����ϰ� ������ ��带 ����Ѵ�*/
	if(ptr) {
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

/*preorder������� Ʈ���� Ž���� ����ϴ� �Լ�*/
void preorderTraversal(Node* ptr)
{
    /*���� ����� ���� ����ϰ� ���ʳ��� �ϳ��� �̵��ϸ� ����Ѵ�.
    ������ ���ʳ����� ������� ��� ������ ��带 �ϳ��� ����Ѵ�.*/
	if(ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

/*postorder������� Ʈ���� Ž���� ����ϴ� �Լ�*/
void postorderTraversal(Node* ptr)
{
    /*������ ���� ��带 ����ϰ� �θ��� ������ ���, �θ� ��� ������ �ö󰡸� ����Ѵ�*/
	if(ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}

/*��带 �����ϴ� �Լ�*/
int insert(Node* head, int key)
{
    /*������ ��� ����*/
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

    /*�� Ʈ���� ��� ����� ���� ��� ����*/
	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/*ptr�� ������� �����ڽĳ�带 ����Ų��*/
	Node* ptr = head->left;

	Node* parentNode = NULL;

    /*������ ������ �ݺ�*/
	while(ptr != NULL) {

		/*���� ���� ���� ��尡 ���� ��� �Լ� ����*/
		if(ptr->key == key) return 1;

		/*ptr�� ����Ű�� ��带 �θ���� ����*/
		parentNode = ptr;

		/*ptr�� ����Ű�� ����� ������ Ŭ ��� �������ڽĳ��� �̵�*/
		if(ptr->key < key)
			ptr = ptr->right;
        /*ptr�� ����Ű�� ����� ������ ���� ��� �����ڽĳ��� �̵�*/
		else
			ptr = ptr->left;
	}

	/*�θ����� ���� Ŭ ���, ���ο� ��带 ���� �ڽ� ���� ����*/
	if(parentNode->key > key)
		parentNode->left = newNode;
    /*�θ����� ���� ���� ���, ���ο� ��带 ������ �ڽ� ���� ����*/
	else
		parentNode->right = newNode;
	return 1;
}

/*leaf��带 �����ϴ� �Լ�*/
int deleteLeafNode(Node* head, int key)
{
    /*�� Ʈ���� ���, �Լ� ����*/
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

    /*������� ���� �ڽĳ�尡 ���� ��� �Լ� ����*/
	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	Node* ptr = head->left;
	Node* parentNode = head;

	while(ptr != NULL) {
        /*������ ��带 ã���� ���*/
		if(ptr->key == key) {
            /*leaf����� ���*/
			if(ptr->left == NULL && ptr->right == NULL) {

				/*�θ��尡 ������� ���, ������ �����ڽĳ���� ������ ���´�*/
				if(parentNode == head)
					head->left = NULL;

				/*�θ����� �����ʳ�尡 ptr�� ���*/
				if(parentNode->left == ptr)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;

				free(ptr);
			}
            /*leaf��尡 �ƴ� ���, leaf��尡 �ƴ϶�� �޼��� ���*/
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

        /*�θ��带 ptr�� ����Ű�� ���� ����*/
		parentNode = ptr;

        /*ptr�� ����Ű�� ����� ���� ������ ����� ������ ���� ���, ptr�� �������ڽĳ�带 ����Ų��*/
		if(ptr->key < key)
			ptr = ptr->right;
        /*ptr�� ����Ű�� ����� ���� ������ ����� ������ Ŭ ���, ptr�� �����ڽĳ�带 ����Ų��*/
		else
			ptr = ptr->left;


	}

    /*������ ��尡 ���� ��� ã�� �� ���ٴ� �޼��� ���*/
	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

/*recursive������� ��带 ã�� �Լ�*/
Node* searchRecursive(Node* ptr, int key)
{
	/*�� Ʈ���� ��� NULL ��ȯ*/
	if(ptr == NULL)
		return NULL;

	/*ptr�� ����Ű�� ����� ���� key���� ���� ��� ptr�� ������ ��� Ž��*/
	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	/*ptr�� ����Ű�� ����� ���� key���� Ŭ ��� ptr�� ���� ��� Ž��*/
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	/*key���� ���� ��带 ã���� ��� ������ ��ȯ*/
	return ptr;

}

/*interative������� ��带 ã�� �Լ�*/
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;

	/*leaf��忡 ������ ������ �ݺ�*/
	while(ptr != NULL)
	{
		/*key�� ã���� ��� �� ����� �ּ� ��ȯ*/
		if(ptr->key == key)
			return ptr;
		/*ptr�� ����Ű�� ����� ���� key���� ���� ��� ������ ��� Ž��*/
		if(ptr->key < key) ptr = ptr->right;
		/*ptr�� ����Ű�� ����� ���� key���� Ŭ ��� ���� ��� Ž��*/
		else
			ptr = ptr->left;
	}

	return ptr;
}

/*����� �޸𸮸� �����ϴ� �Լ�*/
void freeNode(Node* ptr)
{
	/*leaf��尡 ���ö����� ���ָ� recursive�ϰ� 
	���� ������ ������ ����� �̿��� ��� ����� �޸𸮸� �����Ѵ�*/
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

/*Ʈ���� �޸𸮸� �����ϴ� �Լ�*/
int freeBST(Node* head)
{

	/*����常 �ִ� Ʈ���� ���, ������� �޸𸮸� �����ϰ� �Լ� ����*/
	if(head->left == head)
	{
		free(head);
		return 1;
	}

	/*�����ڽĳ����� Ž���ϸ� �޸𸮸� �����Ѵ�*/
	Node* p = head->left;
	freeNode(p);

	/*������� �޸� ����*/
	free(head);
	
	return 1;
}

