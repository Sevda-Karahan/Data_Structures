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
	struct TrieNode *child[10]; // 0-9 aras� 10 d���m
} TrieNode;

TrieNode* createNode();
void insertWords(TrieNode *root, const char *word, struct Keypad *keypad);
void searchWords(TrieNode* root, const char* number);
void freeTrie(TrieNode* root);

int main() {
	
	// Keypad yap�s�n� tan�mlama
	struct Keypad keypad[] = {
        {'0', "#"},
        {'1', "����"},
        {'2', "ABC"},
        {'3', "DEF"},
        {'4', "GHI"},
        {'5', "JKL"},
        {'6', "MNO"},
        {'7', "PQRS"},
        {'8', "TUV"},
        {'9', "WXYZ"}
    };
    
	// S�zl��e ait dosyay� oku ve Trie'ye kelime ekle
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
	
	// Sorgu i�in say�y� al ve kelime kar��l�klar�n� yazd�r
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
	
	//Kelimenin uzunlu�unda d�nerek, s�ras�yla her bir harfe kar��l�k gelen say�y� buluyoruz.
	for (i = 0; i < length; i++) {
	    currentLetter = word[i];
	    found = 0;
	    
	    // Harfin hangi say�ya kar��l�k geldi�ini bulma
	    j = 0;
	    while (j < 10 && found == 0) {
	        int lettersLength = strlen(keypad[j].letters);
	        
	        k = 0;
	        while ((k < lettersLength) && (keypad[j].letters[k] != toupper(currentLetter)))
	            k++;
	        //Burada keypad'deki harfler b�y�k harf �eklinde yaz�ld���ndan, s�zl�kteki k���k veya b�y�k harfin keypad'deki say� kar��l���n� bulurken s�k�nt� olmamas� i�in:
            if (k < lettersLength) {
                currentDigit = keypad[j].digit;
                found = 1;
            }
	        j++;
	    }
	    //printf("%c", currentDigit);
	    // INSERTION
	    // Yeni d���m olu�turma gerekiyorsa
        if (currentNode->child[currentDigit - '0'] == NULL) {
            currentNode->child[currentDigit - '0'] = createNode();
        }
        
        // D���m� g�ncelle
        currentNode = currentNode->child[currentDigit - '0'];
        
        currentNode->digit = currentDigit;
	}
	
	// Kelime sonunu i�aretle ve kelimeyi d���me ata
    if(currentNode->word == NULL) {
    	currentNode->isEndOfWord = 1;
    	currentNode->word = malloc((strlen(word) + 1) * sizeof(char));
    	strcpy(currentNode->word, word);
	} 
	else {
        // Ayn� say�ya denk gelen di�er kelimeler i�in oldu�u i�in '#' de�erinde bir d���m ekle
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
	// tur ve turk �rne�i
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

