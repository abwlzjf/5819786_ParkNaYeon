﻿#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

void GenerateArrayTree(int* tree) {
	int list[] = { -1,1,2,9,3,5,10,13,4,6,7,8,11,12,14,15 };

	for (int i = 0;i <= 15;i++) {
		tree[i] = list[i];
	}

	for (int i = 0;i <= 15;i++) {
		if (tree[i] != -1)
			printf("%d ", tree[i]);
	}
	printf("\n");
}

void ArrayPreOrder(int* tree, int index) {
	if (index > 15 || tree[index] == -1) {
		return;
	}
	printf("%d ", tree[index]);
	ArrayPreOrder(tree, 2 * index);
	ArrayPreOrder(tree, 2 * index + 1);
}

void ArrayInOrder(int* tree, int index) {
	if (index > 15 || tree[index] == -1) {
		return;
	}
	ArrayInOrder(tree, 2 * index);
	printf("%d ", tree[index]);
	ArrayInOrder(tree, 2 * index + 1);
}

void ArrayPostOrder(int* tree, int index) {
	if (index > 15 || tree[index] == -1) {
		return;
	}
	ArrayPostOrder(tree, 2 * index);
	ArrayPostOrder(tree, 2 * index + 1);
	printf("%d ", tree[index]);
}

void ArrayOrders(int* tree) {
	ArrayPreOrder(tree, 1);printf("\n");
	ArrayInOrder(tree, 1);printf("\n");
	ArrayPostOrder(tree, 1);printf("\n");
}

void PlaceNode(TreeNode* node, int direction, int data) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->data = data;
	newNode->left = newNode->right = NULL;

	if (direction == 0) {
		node->left = newNode;
	}
	else {
		node->right = newNode;
	}
}

void GenerateLinkTree(TreeNode* root) {
	PlaceNode(root, 0, 2);
	PlaceNode(root, 1, 9);

	PlaceNode(root->left, 0, 3);
	PlaceNode(root->left, 1, 5);
	PlaceNode(root->right, 0, 10);
	PlaceNode(root->right, 1, 13);

	PlaceNode(root->left->left, 0, 4);
	PlaceNode(root->left->left, 1, 6);
	PlaceNode(root->left->right, 0, 7);
	PlaceNode(root->left->right, 1, 8);
	PlaceNode(root->right->left, 0, 11);
	PlaceNode(root->right->left, 1, 12);
	PlaceNode(root->right->right, 0, 14);
	PlaceNode(root->right->right, 1, 15);
}

void LinkPreOrder(TreeNode* root) {
	if (root != NULL) {
		printf("%d ", root->data);
		LinkPreOrder(root->left);
		LinkPreOrder(root->right);
	}
}

void LinkInOrder(TreeNode* root) {
	if (root != NULL) {
		LinkInOrder(root->left);
		printf("%d ", root->data);
		LinkInOrder(root->right);
	}
}

void LinkPostOrder(TreeNode* root) {
	if (root != NULL) {
		LinkPostOrder(root->left);
		LinkPostOrder(root->right);
		printf("%d ", root->data);
	}
}

void LinkOrders(TreeNode* root) {
	LinkPreOrder(root);printf("\n");
	LinkInOrder(root);printf("\n");
	LinkPostOrder(root);
}

int main() {
	int arr[16];
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;

	GenerateArrayTree(arr);
	GenerateLinkTree(root);
	printf("\n");
	ArrayOrders(arr);
	printf("\n");
	LinkOrders(root);

	return 0;
}