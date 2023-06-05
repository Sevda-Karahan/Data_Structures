#include <stdio.h>
#include <stdlib.h> // for rand() and abs() function
#include <time.h> // for srand(time(NULL));

typedef struct node{
	int x;
	struct node *next;
}node;

void display(node *root);
void add(node **root, int x);
void init_and_disp_comb_lock(int M, int N, node **root1, node **root2, node **root3);
void find_the_common(int M, node *root1, node *root2, node *root3 , int *comm, int *comm_index1, int *comm_index2, int *comm_index3);
void pos_of_unlock_comb_lock(int M, node **root1, node **root2, node **root3, int comm_index1, int comm_index2, int comm_index3);
void disp_final_stuation(node *root1, node *root2, node *root3);

int main(){
	int M, N;
	
	do{
		printf("Carkin uzerindeki sayi adedi (M): ");
		scanf("%d",&M);	
	}while(M<3); // M en az 3 olmal� ki ortak say� �� �arkta da birbirinden farkl� konumlarda olabilsin.
	
	do{
		printf("Carkin uzerindeki sayi araligi 1-N olacak sekilde N: ");
		scanf("%d",&N);
	}while(N<(3*M-2)); 
	/* Kodumda N ve M'e g�re �arklardaki elemanlar� random �retirken 
	�nce 1. �ark�n, sonra 2. �ark�n en son ise 3. �ark�n elemanlar�n� olu�turuyorum. */
	/* Bu durumda N'nin min degerini bulurken t�m olas� senaryolarda do�ru �al��an bir program olu�turmak ad�na
	en k�t� durum senaryosunu d���nd�m.
	Bu durum ortak elemanlar d���ndaki t�m elemanlar�n birbirinden farkl� olmas� durumudur. �rn:
	1. �ark�n 		1 2 3  elemanlar�n�
	2. �ark�n 		1 4 5 elemanlar�n�
	3. �ark�n ise 	1 6 7 elemanlar�n� bar�nd�rd��� �rne�ini d���nebiliriz. 
	1. , 2. ve 3. �arkta ortak 1 eleman, bunun d���nda her birinde farkl� M-1 eleman vard�r.
	Bu durumda  min N = 1 + 3*(M-1) olur. -> N = 3*M-2 olur.*/
		
	node *root1 = NULL, *root2 = NULL, *root3 = NULL; // Her bir �ark i�in ll root
	init_and_disp_comb_lock(M, N, &root1, &root2, &root3);  //initialize and display the three-number combination lock
	
	int comm, comm_index1, comm_index2, comm_index3;
	find_the_common(M, root1, root2, root3, &comm, &comm_index1, &comm_index2, &comm_index3);
	
	pos_of_unlock_comb_lock(M, &root1, &root2, &root3, comm_index1, comm_index2, comm_index3);
	disp_final_stuation(root1, root2, root3);
	return 0;
}	

void display(node *root){ // display the elements in a circular linked list
	node *iter = root;
	if(iter != NULL){
		printf("%3d ",iter->x);
		iter = iter->next;
		while(iter != root){
			printf("%3d ",iter->x);
			iter = iter->next;
		}
		printf("\n");
	}
}

void add(node **root, int x){
	if(*root == NULL){ // linked list bo�sa
		*root = (node *) malloc(sizeof(node));
		(*root)->x = x;
		(*root)->next = *root;
	}
	else{
		node *iter = *root;
		while(iter->next != *root){
			iter = iter->next;
		}
		iter->next = (node *) malloc(sizeof(node));
		iter->next->x = x;
		iter->next->next = *root;
	}
		
}

void init_and_disp_comb_lock(int M, int N, node **root1, node **root2, node **root3){
	// INITIALIZE
	srand(time(NULL));
	int rand_val;
	int *arr = (int *) calloc(N+1,sizeof(int)); /* Bu diziyi random �retti�im say�lar�n bir linkli listede birbirinden farkl� olmas� 
												   ortak eleman d���ndaki �retilen ba�ka bir say�n�n �� �arkta da bulunmamas� i�in kullanaca��m. */
												// dizi N+1 elemanl� ��nk� kolayl�k sa�lamas� a��s�ndan 0. indexi kullanmayaca��m.
												// 1 ila N. indexleri kullanaca��m.
												
	int comm_val = rand()%N + 1; //Bu say� 1. 2. ve 3. �arkta kullan�lacap�ndan 
								// arr dizisinde comm_val indexine 1+2+3 = 6 			
	arr[comm_val] = 6; // 
	//Ortak say�n�n �arklarda farkl� konumlarda �retilmesi gerekmektedir.
	int r_indx1, r_indx2, r_indx3;
	r_indx1 = rand()%M + 1; 	// 1. �arkta ortak say�n�n yerle�tirece�i adres
	
	do{							
		r_indx2 = rand()%M + 1;	// 2. �arkta ortak say�n�n yerle�tirece�i adres
	}while(r_indx1 == r_indx2);
	
	do{
		r_indx3 = rand()%M + 1;	// 3. �arkta ortak say�n�n yerle�tirece�i adres
	}while(r_indx3 == r_indx1 || r_indx3 == r_indx2);
	
	int i;
	for(i=1; i<=M; i++){
		// 1. �ark i�in
		if(i == r_indx1)
			add(root1,comm_val);
		else {
			do{
				rand_val = rand()%N + 1;
			}while(arr[rand_val] != 0); /* veya arr[rand_val] >= 1
			ilk �arktaki her bir eleman�n farkl� bir rand say� olmas� sa�lan�r. */
			arr[rand_val] += 1; // 1. �arkta kulland���m� ifade etmek i�in 1 artt�rd�m.
			add(root1,rand_val);
		}
		
		// 2. �ark i�in
		if(i == r_indx2)
			add(root2,comm_val);
		else{
			do{
				rand_val = rand()%N + 1;
			}while(arr[rand_val] >= 2); /* arr[rand_val] == 2 || arr[rand_val] == 3 || arr[rand_val] == 5 || arr[rand_val] == 6
			ikinci �arktaki her bir eleman�n farkl� bir rand say� olmas� sa�lan�r, 
			ilk �arkta kullan�lan bir say�n�n burda tekrar kullan�lmas�nda bir sak�nca yoktur 
			(�� �ark�n sadece ikisinde ortak bir say� olmas�nda sak�nca yoktur.) */
			arr[rand_val] += 2; // 2. �arkta kulland���m� ifade etmek i�in 2 artt�rd�m.
			add(root2,rand_val);
		}
		
		// 3. �ark i�in
		if(i == r_indx3)
			add(root3,comm_val);
		else{
			do{
				rand_val = rand()%N + 1;
			}while(arr[rand_val] >= 3 ); /* arr[rand_val] == 3 || arr[rand_val] == 4 || arr[rand_val] == 5 || arr[rand_val] == 6 
			3. �arktaki her bir eleman�n birbirinden farkl� bir rand say� olmas� 
			ve ortak say� d���nda �nceki iki �arkta da kullan�lan bir say�n�n burada 3. defa kullan�lmas� engellenir.
			sadece ilk �arkta veya sadece ikinci �arkta kullan�lan bir say�n�n tekrar bu �arkta ikinci defa kullan�lmas�nda bir sak�nca yoktur.*/
			arr[rand_val] += 3; // 3. �arkta kulland���m� ifade etmek i�in 2 artt�rd�m.
			add(root3,rand_val);
		}
	}
	
	free(arr);
	
	// DISPLAY
	display(*root1);
	display(*root2);
	display(*root3);
}

void find_the_common(int M, node *root1, node *root2, node *root3 , int *comm, int *comm_index1, int *comm_index2, int *comm_index3){
	if (root1 == NULL || root2 == NULL || root3 == NULL)
	{
		printf("Hata!\nCarklardan en az birinin elemanlarinin olusturulmasinda bir hata meydana gelmis olabilir.!\n");
		return;
	}

	node *iter1 = root1, *iter2 = root2, *iter3 = root3;
	int i=1, j=1, k=1;
	/*bize verilen senaryoda her �� �arkta ortak bir say�n�n oldu�u kesin oldu�undan
	while d�ng�s� ko�ulu olarak ll sonuna gelinip �arklarda herhangi ortak bir say� 
	bulunmama durumunu gerekmeyen baz� noktalarda kontrol ko�ulu olarak eklemedim.
	*/
	
	/* D�ng�den iter1->x == iter2->x && iter1->x == iter3->x ��k�lmal�d�r. 
	O halde ko�ulu while( !(iter1->x == iter2->x && iter1->x == iter3->x) ) �eklinde 
	veya a�a��daki gibi olu�turabiliriz.*/
	while(iter1->x != iter2->x || iter1->x != iter3->x){  
	/* (iter1->x != iter2->x || iter1->x != iter3->x) || i<=M kontrol� �eklinde yap�l�r normalde fakat burada en d�� d�ng�de
	1.�ark �zerinde d�nd���m�z i�in i>M olmadan count=3 illaki olacakt�r. 
	��nk� her �� �arktada ortak bir eleman bulundu�u kesindir.*/
		iter2 = root2, iter3 = root3;
		j=1, k=1;
		while(iter1->x != iter2->x && j!=M){
			j++;
			iter2 = iter2->next;
		}
		
		if(iter1->x != iter2->x){ /* Burada 1. �arktaki current elaman�m�z, 2. �arkta yoksa 
		bu elaman ortak eleman olamayaca�� i�in 1. �arktaki bir sonraki elemana ge�iyoruz. */
									
		/* Burada if(j==M) kontorl� yap�lmas� hata olurdu. 
		��nk� �arktaki son elemanda arada���m�z ortak eleman olabilir. 
		Yukardaki while d�ng�s�nde son eleman� hesaba katmam��t�k. Burda bunun kontrol�n� de bu �ekilde sa�lama imkan�m�z var.*/
			i++;				  	
			iter1 = iter1->next;
		}
		else{
			while(iter1->x != iter3->x && k!=M){ /*Burada k!=M kontrol�ne gerek vard�r.
			��nk� ilk iki �arkta ortak olup 3. �arkta ortak olmayan say�lar olabilir.
			�nemli olan ortak say� d���nda her �� �arkta da ortak ba�ka bir say�n�n bulunmamas�d�r.*/	
				k++;
				iter3 = iter3->next;
			}
			
			if(iter1->x != iter3->x){
				i++;
				iter1 = iter1->next;
			}
			/*else k�sm�nda bir �ey yapmaya gerek yoktur. 
			��nk� bu durumda ortak olan say� bulunmu�tur. Ve ana d�ng�ye d�n�l�p d�ng�den ��k�lacakt�r.*/
		}
		
	}
	printf("\nHer uc carkta da bulunan ortak sayi : %d\n",iter1->x);
	printf("1. carktaki konumu : %d\n",i);
	printf("2. carktaki konumu : %d\n",j);
	printf("3. carktaki konumu : %d\n",k);
	
	*comm = iter1->x;
	*comm_index1 = i;
	*comm_index2 = j;
	*comm_index3 = k;
	
}

void pos_of_unlock_comb_lock(int M, node **root1, node **root2, node **root3, int comm_index1, int comm_index2, int comm_index3){
	int clockwise, anticlockwise, i;
	/* saat y�n�ne �evirim ile saatin tersi y�n�ne �evirimin ka� ad�m alaca��na bakarsak -> ikisinin toplam�n�n M yapt���n� g�r�r�z.
	Yani "clockwise + anticlockwise = M" dir. Bunu sorunun verdi�i pdf dosyas�ndaki �rnekten de teyit edebiliriz. */
	
	/* 2. �ark�n saat y�n�nde d�nmesi durumunda ka� ad�m �ekece�inin �nce hesaplanmas� durumu
	-> saat y�n�n�n tersine d�nmesi durumu da zaten "anticlockwise = M-clockwise" e�itli�inden bulunur. */
	if(comm_index1 > comm_index2){
		clockwise = (comm_index1 - comm_index2);
		anticlockwise = M - clockwise;
		// 2.�ark�n elamanlar�n�n yeniden pozisyonland�r�lmas�
		for(i=0;i<anticlockwise;i++){
			*root2 = ((*root2)->next);
		}
	}
	/* 2. �ark�n saat y�n�n�n tersine d�nmesi durumunda ka� ad�m �ekece�inin hesaplanmas�
	-> saat y�n�nde d�nmesi durumu da zaten "clockwise = M-anticlockwise" e�itli�inden bulunur. */
	else //comm_index1 <= comm_index2 -> fakat zaten iki indis ayn� yeri g�steremeyece�inden (ortak eleman�n �� �arkta da farkl� yerlerde olma �art� vard�.) -> comm_index1 < comm_index2
	{
		anticlockwise = (comm_index2 - comm_index1);
		clockwise = M - anticlockwise;
		// 2.�ark�n elamanlar�n�n yeniden pozisyonland�r�lmas�
		for(i=0;i<anticlockwise;i++){
			*root2 = ((*root2)->next);
		}
	}
	
	if(clockwise <= anticlockwise)
		printf("\n2.cark saat yonunde %d adim cevrilmeli.\n",clockwise);
	else
		printf("\n2.cark saatin tersi yonde %d adim cevrilmeli.\n",anticlockwise);
	
	// 3. �ark i�in ayn� �ekilde
	if(comm_index1 > comm_index3){
		clockwise = (comm_index1 - comm_index3);
		anticlockwise = M - clockwise;
		for(i=0;i<anticlockwise;i++){
			*root3 = ((*root3)->next);
		}
	}
	else
	{
		anticlockwise = (comm_index3 - comm_index1);
		clockwise = M - anticlockwise;
		for(i=0;i<anticlockwise;i++){
			*root3 = ((*root3)->next);
		}
	}
	
	if(clockwise <= anticlockwise)
		printf("3.cark saat yonunde %d adim cevrilmeli.\n",clockwise);
	else
		printf("3.cark saatin tersi yonde %d adim cevrilmeli.\n",anticlockwise);

}

void disp_final_stuation(node *root1, node *root2, node *root3){
	printf("\nCarklarin son hali:\n");
	display(root1);
	display(root2);
	display(root3);
}
