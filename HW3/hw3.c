#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 50

// Structure for a node in the adjacency list
struct Node {
    int data;
    struct Node* next;
};

// Structure for the adjacency list
struct Graph {
    int numVertices;
    struct Node** adjacencyList;
};

void getN(int *numVertices);
void readAdjMatrix(int **matrix);
void printAdjMatrix(int **matrix, int N);

struct Node* createNode(int value);
struct Graph* createGraph(int vertices);
void addEdge(struct Graph* graph, int src, int dest);
void printGraph(struct Graph* graph);
void calculateIndegree(struct Graph *graph, int *indegree);
void displayIndegree(struct Graph* graph, int* indegree);
void decrementPrerequisites(struct Node *temp, int *indegree);
void dispCourseSemester(struct Graph* graph, int *indegree, int N);
  
int main(){
	int N, i, j;
    
    // Gets the N: (number of courses)
    getN(&N);
    
    // create a NxN matrix filled with zeros -> for adjacency matrix 
	int **matrix = (int **) calloc(N, sizeof(int *));
	if(matrix == NULL){
	    printf("Bellek yetersiz!");
	}
	
	for(i=0; i<N; i++){
	    matrix[i] = (int *) calloc(N, sizeof(int));
	    if(matrix[i] == NULL){
	        printf("Bellek yetersiz!");
	    }
	}
	
	readAdjMatrix(matrix);
	
	printAdjMatrix(matrix, N);
	
	// create the adjacency list according the adjacency matrix 
	struct Graph *graph = createGraph(N);
	for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (matrix[i][j] == 1) {
                addEdge(graph, i, j);
            }
        }
    }
	
	printf("\n");
    printGraph(graph);
    
    // Calculate the indegree of vertices -> o ders kaç dersin ön koþulu
    int indegree[N];
    for(i=0; i<N; i++) 
    	indegree[i] = 0;
    calculateIndegree(graph, indegree);
    
    // Display the indegree of vertices 
    printf("\nVerilen graf icin her dersin on sart sayisi soyledir:\n");
    displayIndegree(graph, indegree);
    printf("\n");
    
    dispCourseSemester(graph, indegree, N);
	
	// free the adjacency matrix 
	for(i=0; i<N; i++)
		free(matrix[i]);
	free(matrix);
	
	return 0;
}

// Gets the N: (number of courses) from the file
void getN(int *numVertices){
	const char *delimiter_characters = " ";
    const char *fname = "adjacency_matrix.txt";
	char buffer[ BUFFER_SIZE ];
    char *token;
	int i;
	
    FILE *fp = fopen(fname, "r");

	if( fp == NULL ){
    	fprintf( stderr, "Dosya acilamadi!\n");
    }
	else{
        // Read first line into the buffer
        if( fgets(buffer, BUFFER_SIZE, fp) != NULL ){
            
			i=0;
            //Gets each token
            token = strtok( buffer, delimiter_characters );
            while( token != NULL ){
                token = strtok( NULL, delimiter_characters );
                i++;
            }
            *numVertices = i; // Number of courses
        }
        else{
        	printf("Bir hata olustu!");
		}
	}
	fclose(fp);
}

// Reads the adjacency matrix from the file
void readAdjMatrix(int **matrix){
	const char *delimiter_characters = " ";
    const char *fname = "adjacency_matrix.txt";
	char buffer[ BUFFER_SIZE ];
    char *token;
    int i, j;
    
    FILE *fp = fopen(fname, "r");
    
	if( fp == NULL ){
    	printf("Dosya acilamadi!\n");
    }
	else{
		i=0;
        // Read each line into the buffer
        while( fgets(buffer, BUFFER_SIZE, fp) != NULL ){

            // Write the line to stdout
            //fputs( buffer, stdout );
            
			j=0;
            //Gets each token as a string and with atoi() assigning its int value to the matrix's elemnts
            token = strtok( buffer, delimiter_characters );
            while( token != NULL ){
                matrix[i][j] = atoi(token);
                token = strtok( NULL, delimiter_characters );
                j++;
            }
            i++;
        }
	}
	fclose(fp);
}

// Prints the adjacency matrix 
void printAdjMatrix(int **matrix, int N){
	int i, j;
	printf("\nKomsuluk matrisi:\n");
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			printf("%d ",matrix[i][j]);
		}
		printf("\n");
	}
}

// Function to create a new node
struct Node *createNode(int value) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with a given number of vertices
struct Graph *createGraph(int vertices) {
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjacencyList = malloc(vertices * sizeof(struct Node*));

    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjacencyList[i] = NULL;
    }

    return graph;
}

// Function to add an edge to the directed graph
void addEdge(struct Graph *graph, int src, int dest) {
    struct Node *newNode = createNode(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;
}

void printGraph(struct Graph *graph) {
    int v;
    for (v = 0; v < graph->numVertices; v++) {
        struct Node *temp = graph->adjacencyList[v];
        printf("Course-%d icin Komsuluk Listesi:\n", v+1); //Adjacency list of Course-%d
        while (temp) {
            printf("Course-%d -> ", (temp->data+1));
            temp = temp->next;
        }
        printf("NULL\n\n");
    }
}


// Function to calculate the indegree of vertices in a directed graph
void calculateIndegree(struct Graph *graph, int *indegree) {
    int v;
    for (v = 0; v < graph->numVertices; v++) {
        struct Node *temp = graph->adjacencyList[v];
        while (temp) {
            indegree[temp->data]++;
            temp = temp->next;
        }
    }
}

// Function to display the indegree of vertices in the graph
void displayIndegree(struct Graph* graph, int* indegree) {
    int v;
    for (v = 0; v < graph->numVertices; v++) {
        printf("Course-%d: %d\t", v+1, indegree[v]);
    }
}

// Decreases prerequisites for fulfilled courses.
void decrementPrerequisites(struct Node *temp, int *indegree) {
    while (temp){
    	indegree[temp->data]--;
        temp = temp->next;
	} 
}

// Displays which courses you can take in which semester
void dispCourseSemester(struct Graph* graph, int *indegree, int N){
	int i, j, k;
	int selected = 0;
	
	// Bir dönemde seçilen dersleri tutacaðým array
    int selectedArr[N]; 
    for(i=0; i<N; i++) 
    	selectedArr[i] = -1;
    	
    k=0;	
    while(selected != N){
    	
    	j=0;
    	printf("\nDonem-%d: ",k+1);
	    for(i=0; i<N; i++){	
	    	if(indegree[i] == 0){
	    		selectedArr[j] = i;
	    		j++;
	    		
	    		indegree[i] = -1; // burada bu kursun artýk alýndýðýný bir daha alýnamayacaðýný deðerine -1 vererek saðlýyorum.
	    		selected++;
				printf("Course-%d ",i+1);
			}
		}
		j=0;
		while(selectedArr[j] != -1){
    		decrementPrerequisites(graph->adjacencyList[selectedArr[j]], indegree);
    		selectedArr[j] = -1;
    		j++;
		}
		
		k++;
	}
	printf("\nOgrenci bolumu %d donemde bitirir.\n",k);
}
