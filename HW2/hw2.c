#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 50 // stack max 50 elemanli -> BST'yi de max 50 elemanli olusturmaliyim.
// struct for BST
typedef struct node{
	int data;
	struct node *left;
	struct node *right;
}node;

// struct for stack
typedef struct{
	int item[MAX];
	int top;
}STACK;

// BST
node *insert(node *tree, int x);
void traverse(node *tree);
void BSTtoArray(node *tree, int *arr);
int search(node *tree, int x);
int max(node *tree);
int min(node *tree);
node *deletion(node *tree, int x);
node *createBST(node *tree, int M, int N);

// STACK
int push(int x, STACK *s);
int pop(STACK *s, int *x);
void initStack(STACK *s);
int isEmpty(STACK *s);
int isFull(STACK *s);


int main(){
	int N, M, k, p, i;
		
	do{
		printf("Meyve adedi (M) : ");
		scanf("%d",&M);
	}while(M<=0);
	
	do{
		printf("Max meyve agiriligi (N) : ");
		scanf("%d",&N);
	}while(N<M); /* BST'de elemanlar unique olmalý bu nedenle N en az meyve adedi kadar olmalý
	örn: M=3 iken -> N en az 3 olmalý ki -> 1-2-3 elemanlarýný içeren bir aðaç oluþturabilelim. */
	
	node *tree = NULL;
	printf("\nBinary Search Tree\n");
	tree = createBST(tree, M, N);
	traverse(tree);
	
	// Meyvelerin tutunma gucunu tutacagim dizi, ilk deger = 0
	int *arr = (int *) calloc( (max(tree) + 1) , sizeof(int));
	// inorder traversal yaparak BST elemanlarýný geziyorum. Current node'daki meyve degerini, o degerdeki indise atiyorum.
	BSTtoArray(tree, arr);
	
//	printf("\n");
//	for(i=0;i<=max(tree);i++)
//		printf("%d ",arr[i]);

	STACK s1, s2;
	initStack(&s1); 
	initStack(&s2);
	
	printf("\n\nAtislara basliyoruz...");
	
	i=0;
	do{
		i++;
		printf("\n\n%d. Atis:\n", i);
		do{
			printf("Vurmak istediginiz meyvenin degeri (k) : ");
			scanf("%d",&k);
		}while( search(tree, k) == -1); //Vurulmak istenen meyvenin, aðaçta olan bir meyve olduðu garanti edilir.
		
		do{
			printf("Atis gucu (p) : ");
			scanf("%d",&p);
		}while(p<0);
		
		arr[k] -= p; //meyvenin tutunma gucunun, atis gucu kadar azaltilmasi
		if(arr[k] <= 0){
			tree = deletion(tree,k);
			// push(k, &s1) -> Bu degerin stack'e atilmasi (Meyvenin kovaya düþmesi)
			if(!push(k, &s1)) 
				printf("\nKova dolu (MAX kapasite = %d)\nKovaya eklenemeyen meyve: %d\n", MAX, k);
		}
			
		printf("\nAtistan sonra agacin yeni durumu:\n");
		traverse(tree);	
		printf("\n");
		
	}while(tree!=NULL);
	
	int x;
	while(pop(&s1, &x) !=  0)
		push(x, &s2);
	
	printf("\nKova: "); 
	while(pop(&s2, &x) != 0)
		printf("%d ", x);
		
	// free the dynamically allocated memory
    free(arr);
    
	return 0;
}

node *insert(node *tree, int x){
	if(tree == NULL){ // Aðaçta henüz hiç eleman yoksa
		node *root = (node *) malloc(sizeof(node));
		root->left = NULL;
		root->right = NULL;
		root->data = x;
		return root;
	}
	// Aðaçta eleman varsa 
	if(tree->data < x){
		tree->right = insert(tree->right,x);
		return tree;	
	}
	//else
	tree->left = insert(tree->left,x);
	return tree;
}

void traverse(node *tree){ /* inorder traversal tercih ettim. 
-> Binary searc tree'de inorder traversal tüm elamanlarý küçükten büyüðe yazdýrýr. */
	if(tree == NULL)
		return;
	traverse(tree->left);
	printf("%3d ",tree->data);
	traverse(tree->right);
}

void BSTtoArray(node *tree, int *arr){
	if(tree == NULL)
		return;
	BSTtoArray(tree->left, arr);
	arr[tree->data] = tree->data;
	BSTtoArray(tree->right, arr);	
}

int search(node *tree, int x){
	if(tree == NULL)
		return -1;
	if(tree->data == x)
		return 1;
	if( search(tree->left, x) == 1 )
		return 1;
	if( search(tree->right, x) == 1 )
		return 1;
	return -1;
}

int max(node *tree){
	if(tree!=NULL){
		while(tree->right != NULL)
			tree =  tree->right;
		return tree->data;
	}	
}

int min(node *tree){
	if(tree != NULL){
		while(tree->left != NULL)
			tree =  tree->left;
		return tree->data;
	}
}

node *deletion(node *tree, int x){
	if(tree == NULL) //agac null ise
		return NULL;
	else if(tree->data == x){ //aradigim degeri bulduysam o node'da
		if(tree->left == NULL && tree->right == NULL){ //leaf node deletion
	 		return NULL;
		}
		//internal node deletion -> Agacin saginda eleman varsa -> buradaki min, silinmek istenen degerin yerine getirilir. 
		else if(tree->right != NULL){ 
			tree->data = min(tree->right);
			tree->right = deletion(tree->right,min(tree->right)); 
			return tree;
		}
		//internal node deletion -> Agacin saginda eleman olmayýp solunda varsa -> buradaki max, silinmek istenen degerin yerine getirilir.
		//else(tree->left != NULL) 
		tree->data = max(tree->left);
		tree->left = deletion(tree->left,max(tree->left)); 
		return tree;
	}
	else if(tree->data < x){ //aradigim degeri henuz bulamadiysam ve aradigim deger current node'dan büyükse
		tree->right = deletion(tree->right, x);
		return tree;
	}
	//aradigim degeri henuz bulamadiysam ve aradigim deger current node'dan küçükse
	//else(tree->data > x)
	tree->left = deletion(tree->left, x);
	return tree;
}

node *createBST(node *tree, int M, int N){
	srand(time(NULL));
	int i, rand_val;
	for(i=0;i<M;i++){
		do{
			rand_val = rand()%N + 1;
		}while( search(tree, rand_val) == 1 ); //Aðaçta zaten olan bir deðerin yeniden aðaca eklenmemsi garanti edilir.
		tree = insert(tree,rand_val);
	}
	return tree;
}

int push(int x, STACK *s){
	if(isFull(s))
		return 0;
	else{
		s->item[s->top] = x;
		++s->top;
		return 1;
	}
}

int pop(STACK *s, int *x){
	if(isEmpty(s))
		return 0;
	else{
		--s->top;
		*x = s->item[s->top];
		return 1;
	}
}

void initStack(STACK *s){
	s->top=0;
}

int isEmpty(STACK *s){
	if(s->top == 0)
		return 1;
	else
		return 0;
}

int isFull(STACK *s){
	if(s->top == MAX)
		return 1;	
	else
		return 0;
}
