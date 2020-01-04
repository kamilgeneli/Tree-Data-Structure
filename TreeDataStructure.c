#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Tree{
	int num;
	int heath;
	int AVL;
	struct Tree *left;
	struct Tree *right;
}tree;

tree *root=NULL;

void getNumbers();
void addToTree(int);
void heathMeasure(tree*);
void AVLMeasure(tree*);
void writeTheTree(tree*);
void roamForCorrection(tree*);
void AVLCorrect(tree*);

int main()
{
	getNumbers();
	heathMeasure(root);
	AVLMeasure(root);
	printf("\t\tThe Final Tree\n\n");
	printf("Sayi\tHealth\tAVL\tLeft\tRight\n");
	writeTheTree(root);
}

void getNumbers()
{
	FILE *fp = fopen("Numbers.txt","r");
	if(fp==NULL){
		printf("An error occurred while opening the file\n");
		printf("Closing program\n");
		exit(1);
	}
	while(!feof(fp)){
		int a;
		fscanf(fp,"%d ", &a);
		addToTree(a);
		heathMeasure(root);
		AVLMeasure(root);
		printf("\t\Added\n\n");
		printf("Sayi\tHealth\tAVL\tLeft\tRight\n");
		writeTheTree(root);
		printf("\n\n\n");
		roamForCorrection(root);
		printf("\t\tCoreccted\n\n");
		printf("Sayi\tHealth\tAVL\tLeft\tRight\n");
		writeTheTree(root);
		printf("\n\n------------------------------------------\n\n");
	}
}

void addToTree(int number)
{
	tree *data = root;
	if(data == NULL){
		data = (tree*)malloc(sizeof(tree));
		data->num = number;
		root = data;
	}
	else
	while(data!=NULL){
		if(data->num < number){
			if(data->right == NULL){
				data->right = (tree*)malloc(sizeof(tree));
				data->right->num = number;
				data = data->right;
				break;
			}
			else
				data = data->right;
		}
		if(data->num >= number){
			if(data->left == NULL){
				data->left = (tree*)malloc(sizeof(tree));
				data->left->num = number;
				data = data->left;
				break;
			}
			else
				data = data->left;
		}
		
	}
	data->heath = 0;
	data->AVL = 0;
	data->left = NULL;
	data->right = NULL;
}

void heathMeasure(tree *data)
{
	if(data==NULL)
		return;
	heathMeasure(data->left);
	heathMeasure(data->right);
	if(data->left == NULL){
		if(data->right == NULL){
			data->heath = 0;
			return;
		}
		data->heath = data->right->heath + 1 ;
		return;
	}
	else if(data->right == NULL){
		data->heath = data->left->heath + 1 ;
		return;
	}
	else{
		if(data->right->heath >= data->left->heath){
			data->heath = data->right->heath + 1;
			return;
		}
		else{
			data->heath = data->left->heath + 1;
			return;
		}
	}
}

void AVLMeasure(tree *data)
{
	if(data==NULL)
		return;
	AVLMeasure(data->left);
	AVLMeasure(data->right);
	if(data->left == NULL){
		if(data->right == NULL){
			data->AVL = 0;
			return;
		}
		data->AVL = (-1) - data->right->heath;
		return;
	}
	else if(data->right == NULL){
		data->AVL = data->left->heath - (-1);
		return;
	}
	else{
		data->AVL = data->left->heath - data->right->heath;
		return;
	}
}

void writeTheTree(tree* data)
{
	if(data==NULL) return;
	if(data->left != NULL || data->right != NULL || data == root ){
		printf("%3d\t%2d\t%2d\t", data->num, data->heath, data->AVL);
		if(data->left==NULL){
			printf("NULL\t");
		}
		else{
			printf("%d\t", data->left->num);
		}
		if(data->right==NULL){
			printf("NULL\n");
		}
		else{
			printf("%d\n", data->right->num);
		}
	}
	writeTheTree(data->left);
	writeTheTree(data->right);
}

void roamForCorrection(tree *data)
{
	if(data == NULL)	return;
	roamForCorrection(data->left);
	roamForCorrection(data->right);
	if(data->AVL >= 2 || data->AVL <= -2){
		AVLCorrect(data);
		heathMeasure(root);
		AVLMeasure(root);
	}
}

void AVLCorrect(tree *data)
{
	if(data->AVL >= 2){
		if(data->left->AVL > 0){
			int temp;
			temp = data->num;
			data->num = data->left->num;
			data->left->num = temp;
			
			tree *tempTree;
			tempTree = data->left;
			data->left = data->left->left;
			tempTree->left = tempTree->right;
			tempTree->right = data->right;
			data->right = tempTree;
			return;
		}
		else{
			int temp;
			temp = data->num;
			data->num = data->left->right->num;
			data->left->right->num = temp;
			
			tree *tempTree;
			tempTree = data->left->right;
			data->left->right = tempTree->left;
			tempTree->left = tempTree->right;
			tempTree->right = data->right;
			data->right = tempTree;
			return;
		}
	}
	if(data->AVL <= -2){
		if(data->right->AVL < 0){
			int temp;
			temp = data->num;
			data->num = data->right->num;
			data->right->num = temp;
			
			tree *tempTree;
			tempTree = data->right;
			data->right = data->right->right;
			tempTree->right = tempTree->left;
			tempTree->left = data->left;
			data->left = tempTree;
			return;
		}
		else{
			int temp;
			temp = data->num;
			data->num = data->right->left->num;
			data->right->left->num = temp;
			
			tree *tempTree;
			tempTree = data->right->left;
			data->right->left = tempTree->right;
			tempTree->right = tempTree->left;
			tempTree->left = data->left;
			data->left = tempTree;
			return;
		}
	}
}
