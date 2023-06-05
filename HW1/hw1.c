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
	}while(M<3); // M en az 3 olmalý ki ortak sayý üç çarkta da birbirinden farklý konumlarda olabilsin.
	
	do{
		printf("Carkin uzerindeki sayi araligi 1-N olacak sekilde N: ");
		scanf("%d",&N);
	}while(N<(3*M-2)); 
	/* Kodumda N ve M'e göre çarklardaki elemanlarý random üretirken 
	önce 1. çarkýn, sonra 2. çarkýn en son ise 3. çarkýn elemanlarýný oluþturuyorum. */
	/* Bu durumda N'nin min degerini bulurken tüm olasý senaryolarda doðru çalýþan bir program oluþturmak adýna
	en kötü durum senaryosunu düþündüm.
	Bu durum ortak elemanlar dýþýndaki tüm elemanlarýn birbirinden farklý olmasý durumudur. Örn:
	1. çarkýn 		1 2 3  elemanlarýný
	2. çarkýn 		1 4 5 elemanlarýný
	3. çarkýn ise 	1 6 7 elemanlarýný barýndýrdýðý örneðini düþünebiliriz. 
	1. , 2. ve 3. çarkta ortak 1 eleman, bunun dýþýnda her birinde farklý M-1 eleman vardýr.
	Bu durumda  min N = 1 + 3*(M-1) olur. -> N = 3*M-2 olur.*/
		
	node *root1 = NULL, *root2 = NULL, *root3 = NULL; // Her bir çark için ll root
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
	if(*root == NULL){ // linked list boþsa
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
	int *arr = (int *) calloc(N+1,sizeof(int)); /* Bu diziyi random ürettiðim sayýlarýn bir linkli listede birbirinden farklý olmasý 
												   ortak eleman dýþýndaki üretilen baþka bir sayýnýn üç çarkta da bulunmamasý için kullanacaðým. */
												// dizi N+1 elemanlý çünkü kolaylýk saðlamasý açýsýndan 0. indexi kullanmayacaðým.
												// 1 ila N. indexleri kullanacaðým.
												
	int comm_val = rand()%N + 1; //Bu sayý 1. 2. ve 3. çarkta kullanýlacapýndan 
								// arr dizisinde comm_val indexine 1+2+3 = 6 			
	arr[comm_val] = 6; // 
	//Ortak sayýnýn çarklarda farklý konumlarda üretilmesi gerekmektedir.
	int r_indx1, r_indx2, r_indx3;
	r_indx1 = rand()%M + 1; 	// 1. çarkta ortak sayýnýn yerleþtireceði adres
	
	do{							
		r_indx2 = rand()%M + 1;	// 2. çarkta ortak sayýnýn yerleþtireceði adres
	}while(r_indx1 == r_indx2);
	
	do{
		r_indx3 = rand()%M + 1;	// 3. çarkta ortak sayýnýn yerleþtireceði adres
	}while(r_indx3 == r_indx1 || r_indx3 == r_indx2);
	
	int i;
	for(i=1; i<=M; i++){
		// 1. Çark için
		if(i == r_indx1)
			add(root1,comm_val);
		else {
			do{
				rand_val = rand()%N + 1;
			}while(arr[rand_val] != 0); /* veya arr[rand_val] >= 1
			ilk çarktaki her bir elemanýn farklý bir rand sayý olmasý saðlanýr. */
			arr[rand_val] += 1; // 1. çarkta kullandýðýmý ifade etmek için 1 arttýrdým.
			add(root1,rand_val);
		}
		
		// 2. Çark için
		if(i == r_indx2)
			add(root2,comm_val);
		else{
			do{
				rand_val = rand()%N + 1;
			}while(arr[rand_val] >= 2); /* arr[rand_val] == 2 || arr[rand_val] == 3 || arr[rand_val] == 5 || arr[rand_val] == 6
			ikinci çarktaki her bir elemanýn farklý bir rand sayý olmasý saðlanýr, 
			ilk çarkta kullanýlan bir sayýnýn burda tekrar kullanýlmasýnda bir sakýnca yoktur 
			(üç çarkýn sadece ikisinde ortak bir sayý olmasýnda sakýnca yoktur.) */
			arr[rand_val] += 2; // 2. çarkta kullandýðýmý ifade etmek için 2 arttýrdým.
			add(root2,rand_val);
		}
		
		// 3. Çark için
		if(i == r_indx3)
			add(root3,comm_val);
		else{
			do{
				rand_val = rand()%N + 1;
			}while(arr[rand_val] >= 3 ); /* arr[rand_val] == 3 || arr[rand_val] == 4 || arr[rand_val] == 5 || arr[rand_val] == 6 
			3. çarktaki her bir elemanýn birbirinden farklý bir rand sayý olmasý 
			ve ortak sayý dýþýnda önceki iki çarkta da kullanýlan bir sayýnýn burada 3. defa kullanýlmasý engellenir.
			sadece ilk çarkta veya sadece ikinci çarkta kullanýlan bir sayýnýn tekrar bu çarkta ikinci defa kullanýlmasýnda bir sakýnca yoktur.*/
			arr[rand_val] += 3; // 3. çarkta kullandýðýmý ifade etmek için 2 arttýrdým.
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
	/*bize verilen senaryoda her üç çarkta ortak bir sayýnýn olduðu kesin olduðundan
	while döngüsü koþulu olarak ll sonuna gelinip çarklarda herhangi ortak bir sayý 
	bulunmama durumunu gerekmeyen bazý noktalarda kontrol koþulu olarak eklemedim.
	*/
	
	/* Döngüden iter1->x == iter2->x && iter1->x == iter3->x çýkýlmalýdýr. 
	O halde koþulu while( !(iter1->x == iter2->x && iter1->x == iter3->x) ) þeklinde 
	veya aþaðýdaki gibi oluþturabiliriz.*/
	while(iter1->x != iter2->x || iter1->x != iter3->x){  
	/* (iter1->x != iter2->x || iter1->x != iter3->x) || i<=M kontrolü þeklinde yapýlýr normalde fakat burada en dýþ döngüde
	1.çark üzerinde döndüðümüz için i>M olmadan count=3 illaki olacaktýr. 
	çünkü her üç çarktada ortak bir eleman bulunduðu kesindir.*/
		iter2 = root2, iter3 = root3;
		j=1, k=1;
		while(iter1->x != iter2->x && j!=M){
			j++;
			iter2 = iter2->next;
		}
		
		if(iter1->x != iter2->x){ /* Burada 1. çarktaki current elamanýmýz, 2. çarkta yoksa 
		bu elaman ortak eleman olamayacaðý için 1. çarktaki bir sonraki elemana geçiyoruz. */
									
		/* Burada if(j==M) kontorlü yapýlmasý hata olurdu. 
		Çünkü çarktaki son elemanda aradaýðýmýz ortak eleman olabilir. 
		Yukardaki while döngüsünde son elemaný hesaba katmamýþtýk. Burda bunun kontrolünü de bu þekilde saðlama imkanýmýz var.*/
			i++;				  	
			iter1 = iter1->next;
		}
		else{
			while(iter1->x != iter3->x && k!=M){ /*Burada k!=M kontrolüne gerek vardýr.
			çünkü ilk iki çarkta ortak olup 3. çarkta ortak olmayan sayýlar olabilir.
			önemli olan ortak sayý dýþýnda her üç çarkta da ortak baþka bir sayýnýn bulunmamasýdýr.*/	
				k++;
				iter3 = iter3->next;
			}
			
			if(iter1->x != iter3->x){
				i++;
				iter1 = iter1->next;
			}
			/*else kýsmýnda bir þey yapmaya gerek yoktur. 
			Çünkü bu durumda ortak olan sayý bulunmuþtur. Ve ana döngüye dönülüp döngüden çýkýlacaktýr.*/
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
	/* saat yönüne çevirim ile saatin tersi yönüne çevirimin kaç adým alacaðýna bakarsak -> ikisinin toplamýnýn M yaptýðýný görürüz.
	Yani "clockwise + anticlockwise = M" dir. Bunu sorunun verdiði pdf dosyasýndaki örnekten de teyit edebiliriz. */
	
	/* 2. çarkýn saat yönünde dönmesi durumunda kaç adým çekeceðinin önce hesaplanmasý durumu
	-> saat yönünün tersine dönmesi durumu da zaten "anticlockwise = M-clockwise" eþitliðinden bulunur. */
	if(comm_index1 > comm_index2){
		clockwise = (comm_index1 - comm_index2);
		anticlockwise = M - clockwise;
		// 2.çarkýn elamanlarýnýn yeniden pozisyonlandýrýlmasý
		for(i=0;i<anticlockwise;i++){
			*root2 = ((*root2)->next);
		}
	}
	/* 2. çarkýn saat yönünün tersine dönmesi durumunda kaç adým çekeceðinin hesaplanmasý
	-> saat yönünde dönmesi durumu da zaten "clockwise = M-anticlockwise" eþitliðinden bulunur. */
	else //comm_index1 <= comm_index2 -> fakat zaten iki indis ayný yeri gösteremeyeceðinden (ortak elemanýn üç çarkta da farklý yerlerde olma þartý vardý.) -> comm_index1 < comm_index2
	{
		anticlockwise = (comm_index2 - comm_index1);
		clockwise = M - anticlockwise;
		// 2.çarkýn elamanlarýnýn yeniden pozisyonlandýrýlmasý
		for(i=0;i<anticlockwise;i++){
			*root2 = ((*root2)->next);
		}
	}
	
	if(clockwise <= anticlockwise)
		printf("\n2.cark saat yonunde %d adim cevrilmeli.\n",clockwise);
	else
		printf("\n2.cark saatin tersi yonde %d adim cevrilmeli.\n",anticlockwise);
	
	// 3. çark için ayný þekilde
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
