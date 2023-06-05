#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LENGTH 10

struct Keypad {
    char digit;
    char letters[5];
} Keypad;

typedef struct TrieNode{
	char *word;
	char digit;
	int isEndOfWord;
	struct TrieNode *child[10]; // 0-9 arası 10 düğüm
} TrieNode;

TrieNode* createNode();
void insertWords(TrieNode *root, const char *word, struct Keypad *keypad);
void searchWords(TrieNode* root, const char* number);
void freeTrie(TrieNode* root);

int main() {
	
	// Keypad yapısını tanımlama
	struct Keypad keypad[] = {
        {'0', "#"},
        {'1', "ÇĐÜŢ"},
        {'2', "ABC"},
        {'3', "DEF"},
        {'4', "GHI"},
        {'5', "JKL"},
        {'6', "MNO"},
        {'7', "PQRS"},
        {'8', "TUV"},
        {'9', "WXYZ"}
    };
    
	// Sözlüğe ait dosyayı oku ve Trie'ye kelime ekle
    TrieNode *root = createNode();

    FILE* dictionaryFile = fopen("dictionary.txt", "r");
    if (dictionaryFile == NULL) {
        printf("Dosya acilamadi.\n");
        return 1;
    }
    char word[MAX_WORD_LENGTH];
    while (fscanf(dictionaryFile, "%s", word) != EOF) {
    	insertWords(root, word, keypad);
    }
    fclose(dictionaryFile);
	
	// Sorgu için sayıyı al ve kelime karakterlerini yazdır
	printf("\n> Sayi girin veya cikmak icin 'q' yaziniz.\n");
	char input[MAX_WORD_LENGTH];
	do{
		printf("> ");
		scanf("%s", input);
		if(strcmp(input, "q"))
			searchWords(root, input);
	}while(strcmp(input, "q")); // if input==q, then strcmp(input, "q")=0 -> breaks the loop
	
	printf("Cikis yaptiniz...\n");
	freeTrie(root);
	return 0;
}

TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->word = NULL;
    node->isEndOfWord = 0;
    int i;
    for (i = 0; i < 10; i++) {
        node->child[i] = NULL;
    }
    return node;
}

void insertWords(TrieNode *root, const char *word, struct Keypad *keypad) {
	int i, j, k, found;
	char currentLetter, currentDigit;
	//printf("\n%s : ",word);
	int length = strlen(word);
	TrieNode *currentNode = root;
	
	//Kelimenin uzunluğunda dönerek, sırasıyla her bir harfe karşılık gelen sayıyı buluyoruz.
	for (i = 0; i < length; i++) {
	    currentLetter = word[i];
	    found = 0;
	    
	    // Harfin hangi sayıya karşılık geldiğini bulma
	    j = 0;
	    while (j < 10 && found == 0) {
	        int lettersLength = strlen(keypad[j].letters);
	        
	        k = 0;
	        while ((k < lettersLength) && (keypad[j].letters[k] != toupper(currentLetter)))
	            k++;
	        //Burada keypad'deki harfler büyük harf ţeklinde yazıldığından, sözlükteki küçük veya büyük harfin keypad'deki sayı karşılıkları bulurken sıkıntı olmaması için:
            if (k < lettersLength) {
                currentDigit = keypad[j].digit;
                found = 1;
            }
	        j++;
	    }
	    //printf("%c", currentDigit);
	    // INSERTION
	    // Yeni düğüm oluşturma gerekiyorsa
        if (currentNode->child[currentDigit - '0'] == NULL) {
            currentNode->child[currentDigit - '0'] = createNode();
        }
        
        // Düğümü güncelle
        currentNode = currentNode->child[currentDigit - '0'];
        
        currentNode->digit = currentDigit;
	}
	
	// Kelime sonunu iţaretle ve kelimeyi düğüme ata
    if(currentNode->word == NULL) {
    	currentNode->isEndOfWord = 1;
    	currentNode->word = malloc((strlen(word) + 1) * sizeof(char));
    	strcpy(currentNode->word, word);
	} 
	else {
        // Aynı sayıya denk gelen diğer kelimeler için için '#' değerinde bir düğüm ekle
        while (currentNode->child[0] != NULL) {
            currentNode = currentNode->child[0];
        }

        currentNode->child[0] = createNode(); //child['#' - '0']
        currentNode->child[0]->digit = '#';
        currentNode->child[0]->isEndOfWord = 1;
        currentNode->child[0]->word = malloc((strlen(word) + 1) * sizeof(char));
        strcpy(currentNode->child[0]->word, word);
    }
}

void searchWords(TrieNode* root, const char* number) {
	int i;
    TrieNode* currentNode = root;
    int length = strlen(number);
    for (i = 0; i < length; i++) {
        int digit = number[i] - '0'; 
        if (currentNode->child[digit] == NULL) { 
            printf("Sozlukte bu sayinin karsiligi bir kelime yoktur.\n");
            return;
        }
        currentNode = currentNode->child[digit];
    }
	// tur ve turk örneği
    if (currentNode->isEndOfWord) {
        printf("%s\n", currentNode->word);
        TrieNode* zeroNode = currentNode->child[0];
        while (zeroNode != NULL) {
            printf("%s\n", zeroNode->word);
            zeroNode = zeroNode->child[0];
        }
    } 
	else {
        printf("Sozlukte bu sayinin karsiligi bir kelime yoktur.\n");
    }
}

void freeTrie(TrieNode* root) { 
	int i;
    if (root == NULL) {
        return;
    }

    for (i = 0; i < 10; i++) {
        freeTrie(root->child[i]); // recursive
    }

	free(root->word);
    free(root);
}

