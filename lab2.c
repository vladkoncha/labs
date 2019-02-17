#include<stdio.h>
#include<stdlib.h>

// Узел дерева
struct Node
{
	int key;
	struct Node *left;
	struct Node *right;
	int height;
};

void FreeTree(struct Node* root)
{
	if (root != NULL)
	{
		if (root->left != NULL) {
			FreeTree(root->left);
		}
		if (root->right != NULL) {
			FreeTree(root->right);
		}
	}
	free(root);
}

//Высота узла
int HeightNode(struct Node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

int MaxElement(int a, int b)
{
	return (a > b) ? a : b;
}

//Создаем новый узел
struct Node* NewNode(int key)
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return(node);
}

//Правый поворот дерева вокруг у
struct Node *RightRotate(struct Node *y)
{
	struct Node *leftSubtree = y->left;
	struct Node *rightSubtreeOfLeftSubtree = leftSubtree->right;

	leftSubtree->right = y;
	y->left = rightSubtreeOfLeftSubtree;

	y->height = 1 + MaxElement(HeightNode(y->left), HeightNode(y->right));
	leftSubtree->height = 1 + MaxElement(HeightNode(leftSubtree->left), HeightNode(leftSubtree->right));

	return leftSubtree;
}

//Левый поворот дерева вокруг х
struct Node *LeftRotate(struct Node *x)
{
	struct Node *y = x->right;
	struct Node *leftSubtreeOfRightSubtree = y->left;

	y->left = x;
	x->right = leftSubtreeOfRightSubtree;

	x->height = MaxElement(HeightNode(x->left), HeightNode(x->right)) + 1;
	y->height = MaxElement(HeightNode(y->left), HeightNode(y->right)) + 1;

	return y;
}

int GetBalance(struct Node *N)
{
	if (N == NULL)
		return 0;
	return HeightNode(N->left) - HeightNode(N->right);
}

struct Node* Insert(struct Node *node, int key)
{
	if (node == NULL)
		return(NewNode(key));

	if (key < node->key)
		node->left = Insert(node->left, key);
	else if (key > node->key)
		node->right = Insert(node->right, key);
	else
		return node;

	node->height = 1 + MaxElement(HeightNode(node->left), HeightNode(node->right));

	int balance = GetBalance(node);

	// Если узлы не сбалансированы, то балансируем
	if (balance > 1 && key < node->left->key)
		return RightRotate(node);

	if (balance < -1 && key > node->right->key)
		return LeftRotate(node);

	if (balance > 1 && key > node->left->key)
	{
		node->left = LeftRotate(node->left);
		return RightRotate(node);
	}

	if (balance < -1 && key < node->right->key)
	{
		node->right = RightRotate(node->right);
		return LeftRotate(node);
	}

	return node;
}

void TreeHeight(struct Node *root)
{
	if (root != NULL)
		printf("%d\n", root->height);
	else
		printf("0");
}

int main()
{
	struct Node *root = NULL;
	long long int N = 0;
	scanf_s("%lld", &N);
	int key = 0;

	for (int i = 0; i < N; i++)
	{
		key = 0;
		scanf_s("%d", &key);
		root = Insert(root, key);
	}
	TreeHeight(root);
	FreeTree(root);

	return 0;
}