/*
    This topic design a binary search tree
	This program use different inorder, preorder, and postorder travelsal
	Users have 5 options, include print travelsal, insert node, 
	delete node, Search node, and leave

	*** This program can show the tree by diagram in cmd ***
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEIGHT 1000
#define NONLIMIT (1 << 20)
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))

typedef struct Binary_Search_Tree
{
	struct Binary_Search_Tree *left;
	int data;
	struct Binary_Search_Tree *right;
} BST;

typedef struct asciinode_struct
{
	struct asciinode_struct *left, *right;

	// length of the edge from this node to its children
	int edge_length;
	int height;
	int lablen;

	// -1=I am left, 0=I am root, 1=right
	int parent_dir;

	// max supported unit32 in dec, 10 digits max
	char label[11];
} asciinode;

int lprofile[MAX_HEIGHT] = {0};
int rprofile[MAX_HEIGHT] = {0};

// adjust gap between left and right nodes
int gap = 3;

// used for printing next node in the same level,
// this is the x coordinate of the next char printed
int print_next = 0;

// printing tree in ascii
asciinode *build_ascii_tree_recursive(BST *);
asciinode *build_ascii_tree(BST *);
void free_ascii_tree(asciinode *);
void compute_lprofile(asciinode *, int, int);
void compute_rprofile(asciinode *, int, int);
void compute_edge_lengths(asciinode *);
void print_level(asciinode *, int, int);
void print_ascii_tree(BST *);

void Preorder(BST *);
void Inorder(BST *);
void Postorder(BST *);
BST *Multiple_Case(BST *, int);
BST *BST_Insert(BST *, BST *);
BST *BST_Delete(BST *, int);
void *BST_Search_Path(BST *, int);

int main(void)
{
	int num = 0;
	char error[100] = {0};
	BST *root = NULL;

	while (1)
	{
		printf("Please choose options: (1) Print Travelsal  (2) Search Node  (3) Delete Node  (4) Search Node  (5)Leave :");

		while (scanf("%d", &num) == 0)
			scanf("%s", error);

		if (num == 5)
		{
			printf("See You Next Time!!!\n");
			break;
		}
		root = Multiple_Case(root, num);
	}
	system("pause");
	return 0;
}

void Inorder(BST *ptr)
{
	if (ptr != NULL)
	{
		Inorder(ptr->left);
		printf("%d ", ptr->data);
		Inorder(ptr->right);
	}
}

void Preorder(BST *ptr)
{
	if (ptr != NULL)
	{
		printf("%d ", ptr->data);
		Preorder(ptr->left);
		Preorder(ptr->right);
	}
}

void Postorder(BST *ptr)
{
	if (ptr != NULL)
	{
		Postorder(ptr->left);
		Postorder(ptr->right);
		printf("%d ", ptr->data);
	}
}

BST *BST_Insert(BST *root, BST *newnode)
{
	BST *r = NULL, *q = NULL;
	int direction = 0;

	newnode->left = NULL;
	newnode->right = NULL;

	if (root == NULL)
		root = newnode;
	else
	{
		q = root;
		while (q != NULL)
		{
			if (newnode->data < q->data)
			{
				direction = 1;
				r = q;
				q = q->left;
			}
			else if (newnode->data > q->data)
			{
				direction = 0;
				r = q;
				q = q->right;
			}
			else
			{
				printf("The value is in the tree, Insert Failed\n");
				return (root);
			}
		}
		if (direction == 1)
			r->left = newnode;
		else
			r->right = newnode;
	}
	printf("Insert Success!!!\n\n");
	printf("Show Tree:\n");
	print_ascii_tree(root);
	return (root);
}

BST *BST_Delete(BST *root, int key)
{
	int found = 0, direction = 0;
	BST *r = NULL, *q = NULL, *s = NULL, *p = NULL;

	p = root;
	while (p != NULL && !found)
	{
		if (key == p->data)
			found = 1;
		else if (key < p->data)
		{
			direction = 1;
			r = p;
			p = p->left;
		}
		else
		{
			direction = 0;
			r = p;
			p = p->right;
		}
	}

	if (p == NULL)
	{
		printf("The value is not in the tree, Delete Failed\n");
		return (root);
	}

	if (p == root)
	{
		if (p->right == NULL)
		{
			printf("Delete Success!!!\n\n");
			printf("Show Tree:\n");
			print_ascii_tree(p->left);
			printf("\n");
			return (p->left);
		}
		else if (p->left == NULL)
		{
			printf("Delete Success!!!\n\n");
			printf("Show Tree:\n");
			print_ascii_tree(p->right);
			printf("\n");
			return (p->right);
		}
	}

	if (p->right == NULL)
	{
		if (direction == 1)
			r->left = p->left;
		else
			r->right = p->left;
	}
	else if (p->left == NULL)
	{
		if (direction == 1)
			r->left = p->right;
		else
			r->right = p->right;
	}
	else
	{
		s = p;
		q = p->left;

		while (q->right != NULL)
		{
			s = q;
			q = q->right;
		}

		p->data = q->data;
		if (p == s)
			s->left = q->left;
		else
			s->right = q->left;
	}
	printf("Delete Success!!!\n\n");
	printf("Show Tree:\n");
	print_ascii_tree(root);
	printf("\n");
	return (root);
}

void *BST_Search_Path(BST *root, int key)
{
	int i = 0, j = 0;
	int temp[1000] = {0};
	BST *ptr = NULL;

	ptr = root;

	while (root != NULL)
	{
		if (key == root->data)
		{
			temp[i] = root->data;
			printf("\nPath:");
			for (j = 0; j <= i; j++)
				printf("%d ", temp[j]);
			printf("\n\nShow Tree:\n");
			print_ascii_tree(ptr);
			printf("\n");
			return 0;
		}
		else if (key < root->data)
		{
			temp[i] = root->data;
			root = root->left;
			i++;
		}
		else
		{
			temp[i] = root->data;
			root = root->right;
			i++;
		}
	}
	if (root == NULL)
	{
		printf("The value is not in the Tree\n\n");
		return 0;
	}
}

BST *Multiple_Case(BST *root, int num)
{
	char error[100] = {0};
	BST *newnode = NULL;

	switch (num)
	{
	case 1:
		if (root == NULL)
		{
			printf("The Tree is empty now\n\n");
			break;
		}
		printf("\nPreorder Travelsal: ");
		Preorder(root);
		printf("\nInorder Travelsal: ");
		Inorder(root);
		printf("\nPostorder Tracelsal: ");
		Postorder(root);
		printf("\n\nShow Tree:\n");
		print_ascii_tree(root);
		printf("\n");
		break;
	case 2:
		printf("Enter Node: ");
		while (scanf("%d", &num) == 0)
			scanf("%s", error);
		newnode = (BST *)malloc(sizeof(BST));
		newnode->data = num;
		root = BST_Insert(root, newnode);
		printf("\n");
		break;
	case 3:
		printf("Enter Node: ");
		while (scanf("%d", &num) == 0)
			scanf("%s", error);
		root = BST_Delete(root, num);
		printf("\n");
		break;
	case 4:
		printf("Enter Node: ");
		while (scanf("%d", &num) == 0)
			scanf("%s", error);
		BST_Search_Path(root, num);
		break;
	default:
		printf("Please Enter The Correct Value!!!\n\n");
		break;
	}
	return (root);
}

/*----------printing tree in ascii (functional area)----------*/

asciinode *build_ascii_tree_recursive(BST *t)
{
	asciinode *node = NULL;

	if (t == NULL)
		return NULL;

	node = malloc(sizeof(asciinode));
	node->left = build_ascii_tree_recursive(t->left);
	node->right = build_ascii_tree_recursive(t->right);

	if (node->left != NULL)
	{
		node->left->parent_dir = -1;
	}

	if (node->right != NULL)
	{
		node->right->parent_dir = 1;
	}

	sprintf(node->label, "%d", t->data);
	node->lablen = strlen(node->label);

	return node;
}

// Copy the tree into the ascii node structre
asciinode *build_ascii_tree(BST *t)
{
	asciinode *node = NULL;

	if (t == NULL)
		return NULL;
	node = build_ascii_tree_recursive(t);
	node->parent_dir = 0;
	return node;
}

// Free all the nodes of the given tree
void free_ascii_tree(asciinode *node)
{
	if (node == NULL)
		return;
	free_ascii_tree(node->left);
	free_ascii_tree(node->right);
	free(node);
}

// The following function fills in the lprofile array for the given tree.
// It assumes that the center of the label of the root of this tree
// is located at a position (x,y).  It assumes that the edge_length
// fields have been computed for this tree.
void compute_lprofile(asciinode *node, int x, int y)
{
	int i = 0, isleft = 0;

	if (node == NULL)
		return;
	isleft = (node->parent_dir == -1);
	lprofile[y] = MIN(lprofile[y], x - ((node->lablen - isleft) / 2));
	if (node->left != NULL)
	{
		for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++)
		{
			lprofile[y + i] = MIN(lprofile[y + i], x - i);
		}
	}
	compute_lprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
	compute_lprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}

void compute_rprofile(asciinode *node, int x, int y)
{
	int i = 0, notleft = 0;

	if (node == NULL)
		return;
	notleft = (node->parent_dir != -1);
	rprofile[y] = MAX(rprofile[y], x + ((node->lablen - notleft) / 2));
	if (node->right != NULL)
	{
		for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++)
		{
			rprofile[y + i] = MAX(rprofile[y + i], x + i);
		}
	}
	compute_rprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
	compute_rprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}

// This function fills in the edge_length and
// height fields of the specified tree
void compute_edge_lengths(asciinode *node)
{
	int h = 0, hmin = 0, i = 0, delta = 0;

	if (node == NULL)
		return;
	compute_edge_lengths(node->left);
	compute_edge_lengths(node->right);

	// first fill in the edge_length of node
	if (node->right == NULL && node->left == NULL)
	{
		node->edge_length = 0;
	}
	else
	{
		if (node->left != NULL)
		{
			for (i = 0; i < node->left->height && i < MAX_HEIGHT; i++)
			{
				rprofile[i] = -NONLIMIT;
			}
			compute_rprofile(node->left, 0, 0);
			hmin = node->left->height;
		}
		else
		{
			hmin = 0;
		}
		if (node->right != NULL)
		{
			for (i = 0; i < node->right->height && i < MAX_HEIGHT; i++)
			{
				lprofile[i] = NONLIMIT;
			}
			compute_lprofile(node->right, 0, 0);
			hmin = MIN(node->right->height, hmin);
		}
		else
		{
			hmin = 0;
		}
		delta = 4;
		for (i = 0; i < hmin; i++)
		{
			delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
		}

		// If the node has two children of height 1, then we allow the
		// two leaves to be within 1, instead of 2
		if (((node->left != NULL && node->left->height == 1) ||
			 (node->right != NULL && node->right->height == 1)) &&
			delta > 4)
		{
			delta--;
		}

		node->edge_length = ((delta + 1) / 2) - 1;
	}

	// now fill in the height of node
	h = 1;
	if (node->left != NULL)
	{
		h = MAX(node->left->height + node->edge_length + 1, h);
	}
	if (node->right != NULL)
	{
		h = MAX(node->right->height + node->edge_length + 1, h);
	}
	node->height = h;
}

// This function prints the given level of the given tree, assuming
// that the node has the given x cordinate.
void print_level(asciinode *node, int x, int level)
{
	int i = 0, isleft = 0;

	if (node == NULL)
		return;
	isleft = (node->parent_dir == -1);
	if (level == 0)
	{
		for (i = 0; i < (x - print_next - ((node->lablen - isleft) / 2)); i++)
		{
			printf(" ");
		}
		print_next += i;
		printf("%s", node->label);
		print_next += node->lablen;
	}
	else if (node->edge_length >= level)
	{
		if (node->left != NULL)
		{
			for (i = 0; i < (x - print_next - (level)); i++)
			{
				printf(" ");
			}
			print_next += i;
			printf("/");
			print_next++;
		}
		if (node->right != NULL)
		{
			for (i = 0; i < (x - print_next + (level)); i++)
			{
				printf(" ");
			}
			print_next += i;
			printf("\\");
			print_next++;
		}
	}
	else
	{
		print_level(node->left,
					x - node->edge_length - 1,
					level - node->edge_length - 1);
		print_level(node->right,
					x + node->edge_length + 1,
					level - node->edge_length - 1);
	}
}

// prints ascii tree for given Tree structure
void print_ascii_tree(BST *t)
{
	asciinode *proot = NULL;
	int xmin = 0, i = 0;

	if (t == NULL)
		return;
	proot = build_ascii_tree(t);
	compute_edge_lengths(proot);
	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
	{
		lprofile[i] = NONLIMIT;
	}
	compute_lprofile(proot, 0, 0);
	xmin = 0;
	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
	{
		xmin = MIN(xmin, lprofile[i]);
	}
	for (i = 0; i < proot->height; i++)
	{
		print_next = 0;
		print_level(proot, -xmin, i);
		printf("\n");
	}
	if (proot->height >= MAX_HEIGHT)
	{
		printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
	}
	free_ascii_tree(proot);
}
