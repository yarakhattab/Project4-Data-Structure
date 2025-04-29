//yara khattab 1210520
//sec 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROUTERS 100
#define MAX_ROUTERS_LEN 50
#define INFINITY 99999

// structure for the graph by using the adjacency Matrix
typedef struct graph {
    int numberofrouters; //number of the routers
    char routers[MAX_ROUTERS][MAX_ROUTERS_LEN];//array to hold the names of routers
    int adjacencymatrix[MAX_ROUTERS][MAX_ROUTERS];//2D array to represent the graph
} myGraph;

//define the struct for the queue
struct node;
typedef struct node* Node;
struct node {
    int data;//the elemet
    Node next;//pointer to next node
};

typedef Node myqueue;


//define min heap node
typedef struct heapnode {
    int router;
    int cost;
} minheapnode;

//define the struct for the min heap
typedef struct heap {
    minheapnode* nodes[MAX_ROUTERS];
    int heapsize;
} MINheap;

// Min-Heap functions
MINheap* createtheminheap();
void swapheapnodes(minheapnode** a, minheapnode** b);
void heapify(MINheap* heap, int current);
void insertMinHeap(MINheap* heap, int router, int cost);
minheapnode* extractMin(MINheap* heap);
int isHeapEmpty(MINheap* heap);

//queue functions
myqueue createmyqueue();
int isEmpty(myqueue q);
Node createnewnode(int data);
void enqueue(myqueue q, int data);
int dequeue(myqueue q);
void freeQueue(myqueue Q);

void createmygraph(myGraph* graph);
int ADDaRouter(myGraph* graph, char* router);
void ADDanEdge(myGraph* graph, char* source, char* destination, int cost);
void dijkstraalgo(myGraph* graph, char* source, char* destination, FILE* outputFile) ;
void bfsalgorthim(myGraph* graph, char* source, char* destination, FILE* outputFile);

//implementation heap functions
//function to create the min heap
MINheap* createtheminheap() {
    MINheap* heap = (MINheap*)malloc(sizeof(MINheap));//allocate the memory
    heap->heapsize = 0;
    return heap;
}

//function to swap nodes in the heap
void swapheapnodes(minheapnode** a, minheapnode** b) {
    minheapnode* temp = *a; //put the first node in a temp node
    *a = *b;//swap nodes
    *b = temp;//put the temp on the other node
}

// function to ensures that the subtree rooted at a given index
void heapify(MINheap* heap, int current) {
    int smallest = current;  // assume the smallest element is current
    int left = 2 * current + 1;  // left child index of the node
    int right = 2 * current + 2; // right child index of the node

    // check if the left child exists and is smaller than the current
    if (left < heap->heapsize && heap->nodes[left]->cost < heap->nodes[smallest]->cost) {
        smallest = left;  // update smallest to the left child
    }

    // check if the right child exists and is smaller than the current
    if (right < heap->heapsize && heap->nodes[right]->cost < heap->nodes[smallest]->cost) {
        smallest = right;  // update smallest to the right child
    }

    if (smallest != current) { //check if the current is not the smallest
        // swap the current node with the smallest node
        swapheapnodes(&heap->nodes[current], &heap->nodes[smallest]);
        heapify(heap, smallest);
    }
}

//function to insert to the min heap
void insertMinHeap(MINheap* heap, int router, int cost) {
    minheapnode* node = (minheapnode*)malloc(sizeof(minheapnode));//alocate memory
    node->router = router;
    node->cost = cost;

    heap->nodes[heap->heapsize] = node;//put the new element in the end of the heap
    int current = heap->heapsize;
    heap->heapsize++;//increment the heap size

    //while loop to put the new node in it's correct position in the heap
    while (current != 0 && heap->nodes[(current - 1) / 2]->cost > heap->nodes[current]->cost) {
        swapheapnodes(&heap->nodes[(current - 1) / 2], &heap->nodes[current]);
        current = (current - 1) / 2;
    }
}

// function to extract the minimum node from the min-heap
minheapnode* extractMin(MINheap* heap) {
    // Check if the heap is empty
    if (heap->heapsize == 0)
        return NULL;

    // Save the root node (minimum value) to return later
    minheapnode* root = heap->nodes[0];

    // Move the last node in the heap to the root position
    heap->nodes[0] = heap->nodes[heap->heapsize - 1];

    heap->heapsize--;// Decrease the heap size
    heapify(heap, 0);

    // Return the original root node (the one with the minimum value)
    return root;
}

//function to check if the heap is empty
int isHeapEmpty(MINheap* heap) {
    return heap->heapsize == 0;
}


// implementations queue functions
// function to create an empty queue
myqueue createmyqueue() {
    myqueue q = (myqueue)malloc(sizeof(struct node));//allocate memory
    if (q == NULL) {
        printf("QUEUE NOT CREATED\n");
        return NULL;
    }
    q->next = NULL; // Initialize the queue as empty
    return q;
}

// function to check if the queue is empty
int isEmpty(myqueue q) {
    if (q == NULL) {
        printf(" QUEUE NOT FOUND.\n");
        return 1;
    }
    return (q->next == NULL);
}


// function to create a new node in the queue
Node createnewnode(int data) {
    Node newNode = (Node)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("OUT OF MEMORY.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// function to add an element to the queue
void enqueue(myqueue q, int data) {
    if (q == NULL) {
        printf(" QUEUE NOT FOUND.\n");
        return;
    }

    Node newNode = createnewnode(data);//create new node
    if (newNode == NULL) // check memory allocation if failed

        return;

    Node temp = q; //temp node
    while (temp->next != NULL) {
        temp = temp->next; // move to the last node
    }
    temp->next = newNode; // add the new node at the end
}

//function to delete a node from the queue
int dequeue(myqueue q) {
    if (q == NULL) { //check if the queue exsit
        printf(" QUEUE NOT FOUND.\n");
        return -1;
    }
    if (isEmpty(q)) { // check if it empty
        printf("QUEUE IS EMPTY. NOTHING TO DEQUEUE.\n");
        return -1;
    }

    Node tempnode = q->next;
    int data = tempnode->data; // Store the data of the front node
    q->next = tempnode->next; // Update the front pointer
    free(tempnode); // Free the memory of the removed node

    return data; // Return the deleted value
}

//function to free the queue
void freeQueue(myqueue Q) {
    if (Q == NULL) {
        printf("QUEUE NOT FOUND.\n");
        return;
    }

    // Free all nodes in the queue
    Node current = Q->next;
    while (current != NULL) {
        Node temp = current;
        current = current->next;
        free(temp);
    }

    // Free the queue header node
    free(Q);
}

//for the graph functions
// function to create the graph using 2D array adjacency matrix
void createmygraph(myGraph* graph) {
    for (int i = 0; i < MAX_ROUTERS; i++) { //for loop go through the 2d array to build it
        for (int j = 0; j < MAX_ROUTERS; j++) {
            graph->adjacencymatrix[i][j] = INFINITY; // assining a null as initial value
        }
    }
}

// Add a router to the graph
int ADDaRouter(myGraph* graph, char* router) {
    for (int i = 0; i < graph->numberofrouters; i++) { //for loop to check if the router is exist
        if (strcmp(graph->routers[i], router) == 0) { //compare the given router with the routers from the graph
            return i; // Router already exists
        }
    }
    strcpy(graph->routers[graph->numberofrouters], router);//if dose not exist so add it
    return graph->numberofrouters++; // increment the number of routers
}

// Add an edge between two routers
void ADDanEdge(myGraph* graph, char* source, char* destination, int cost) {
    int srcIndex = ADDaRouter(graph, source);//get the index of the source router
    int destIndex = ADDaRouter(graph, destination);//get the index of the distination router
    // Assume undirected graph
    graph->adjacencymatrix[srcIndex][destIndex] = cost;
    graph->adjacencymatrix[destIndex][srcIndex] = cost;
}


// Dijkstra ahgorthim using min heap
void dijkstraalgo(myGraph* graph, char* source, char* destination, FILE* outputFile) {
    int numRouters = graph->numberofrouters;
    int dist[MAX_ROUTERS];//array to hold the distances
    int previous[MAX_ROUTERS];//array to hold the previous nodes
    int srcIndex = -1;//to hold the src index
    int destIndex = -1;//to hold the dist index

    // Initialize distances and previous
    for (int i = 0; i < numRouters; i++) {
        dist[i] = INFINITY;
        previous[i] = -1;
    }

    // Get source and destination indices
    for (int i = 0; i < numRouters; i++) {
        if (strcmp(graph->routers[i], source) == 0)
            srcIndex = i;
        if (strcmp(graph->routers[i], destination) == 0)
            destIndex = i;
    }

    //check if two src and dist are exists
    if (srcIndex == -1 || destIndex == -1) {
        printf("SOURCE OR DESTINATION ROUTER NOT FOUND.\n");
        fprintf(outputFile, "SOURCE OR DESTINATION ROUTER NOT FOUND.\n");
        return;
    }

    //create the min heap
    MINheap* minHeap = createtheminheap();
    insertMinHeap(minHeap, srcIndex, 0);//insert the src router to the min heap with cost 0
    dist[srcIndex] = 0;

    //while loop stop when the heap is empty
    while (!isHeapEmpty(minHeap)) {
        minheapnode* minNode = extractMin(minHeap);//get a node with smallest cost from the min heap
        int current = minNode->router; //get the index of the extracted node
        free(minNode);

        // for loop go through the graph to check the adjecent for the extracted node
        for (int i = 0; i < numRouters; i++) {
            if (graph->adjacencymatrix[current][i] != INFINITY) { //check if there an edge between i and the current node
                int newDist = dist[current] + graph->adjacencymatrix[current][i];//calculate the new cost
                if (newDist < dist[i]) { // check if the new cost is less than the old cost
                    dist[i] = newDist; // set the cost with the smallest value
                    previous[i] = current; // Update the previous router for the shortest path
                    insertMinHeap(minHeap, i, newDist);// Insert the updated router 'i' into the min-heap with the new cost
                }
            }
        }
    }

    // Print the shortest path and it's cost
    if (dist[destIndex] == INFINITY) { //check if there a path
        fprintf(outputFile, "NO PATH EXISTS FROM %s TO %s.\n", source, destination);
        printf("NO PATH EXISTS FROM %s TO %s.\n", source, destination);
    } else {
        fprintf(outputFile, "SHORTEST PATH FROM %s TO %s:\n", source, destination);
        printf("\nSHORTEST PATH FROM %s TO %s:\n", source, destination);


        int dijkpath[MAX_ROUTERS];//to store the path
        int lennpath = 0;//count the number of routers in the path
        //start from the distination router
        for (int y = destIndex; y != -1; y = previous[y]) {
            dijkpath[lennpath++] = y; // add the router to the path and increment the length
        }

        // Print the path in reverse order
        for (int i = lennpath - 1; i >= 0; i--) {
            fprintf(outputFile, "%s", graph->routers[dijkpath[i]]);
            printf("%s", graph->routers[dijkpath[i]]);
            if (i > 0) {
                fprintf(outputFile, " -> ");
                printf(" -> ");
            }
        }
        fprintf(outputFile, " \n WITH A TOTAL COST OF %d.\n", dist[destIndex]);
        printf("\nTOTAL COST: %d ms\n", dist[destIndex]);
    }

    free(minHeap);
}


// BFS algorthim using queue
void bfsalgorthim(myGraph* graph, char* source, char* destination, FILE* outputFile) {
    int numrouters = graph->numberofrouters; //get the number of routers in the graph
    int isroutervisited[MAX_ROUTERS] = {0}; // mark all nodes as not visited 0 (false) first
    int previous[MAX_ROUTERS]; // to Store the previous router in the shortest path
    int cost[MAX_ROUTERS] = {0}; // Store the cost of the path

    // Initialize previous array
    for (int i = 0; i < numrouters; i++) {
        previous[i] = -1;
    }

    // Get source and destination indices
    int srcIndex = -1;
    int destIndex = -1;
    for (int i = 0; i < numrouters; i++) {
        if (strcmp(graph->routers[i], source) == 0) {
            srcIndex = i;
        }
        if (strcmp(graph->routers[i], destination) == 0) {
            destIndex = i;
        }
    }

    if (srcIndex == -1 || destIndex == -1) {
        fprintf(outputFile, "SOURCE OR DESTINATION ROUTER NOT FOUND.\n");
        printf("SOURCE OR DESTINATION ROUTER NOT FOUND.\n");
        return;
    }

    // Create a queue
    myqueue* queue = createmyqueue(MAX_ROUTERS);
    isroutervisited[srcIndex] = 1;//mark the source router as visited
    enqueue(queue, srcIndex);//add the source to the queue

    // while loop stop if the queue is empty
    while (!isEmpty(queue)) {
        int current = dequeue(queue);//dequeue first node from the queue

        // If it is the destination so stop
        if (current == destIndex) {
            break;
        }

        // if not so Visit all adjacent nodes (routers)
        for (int i = 0; i < numrouters; i++) { //for loop go through all the nodes
            if (graph->adjacencymatrix[current][i] != INFINITY && !isroutervisited[i]) { // check if the router i have an egde with the current router (if two are neibour)
                isroutervisited[i] = 1;//mark it as visited
                previous[i] = current; // update the path
                cost[i] = cost[current] + graph->adjacencymatrix[current][i]; // calculate the cost
                enqueue(queue, i); // add i to the queue
            }
        }
    }

    // Free the queue
    freeQueue(queue);

    // Print the shortest path and it's cost
    if (!isroutervisited[destIndex]) {
        fprintf(outputFile, "NO PATH EXISTS FROM %s TO %s.\n", source, destination);
        printf("NO PATH EXISTS FROM %s TO %s.\n", source, destination);
    } else {
        fprintf(outputFile, "SHORTEST PATH FROM %s TO %s:\n ", source, destination);
        printf("\nSHORTEST PATH FROM %s TO %s:\n", source, destination);


        int bfspath[MAX_ROUTERS];//to store the path
        int lenpath = 0;//path length
        //start from destination
        for (int d = destIndex; d != -1; d = previous[d]) {
            bfspath[lenpath++] = d;//add the router to the path and increment the length
        }

        // Print the path in reverse order
        for (int i = lenpath - 1; i >= 0; i--) {
            fprintf(outputFile, "%s", graph->routers[bfspath[i]]);
            printf("%s", graph->routers[bfspath[i]]);
            if (i > 0) {
                fprintf(outputFile, " -> ");
                printf(" -> ");
            }
        }
        fprintf(outputFile, " \n WITH A TOTAL COST OF %d.\n", cost[destIndex]);
        printf("\nTOTAL COST: %d ms\n", cost[destIndex]);
    }
}


int main() {
    myGraph graph; // graph to hold the routers
    createmygraph(&graph);//create the graph using adjecency matrix
    char source[MAX_ROUTERS_LEN];//to hold the source router
    char destination[MAX_ROUTERS_LEN];//to hold the dist router
    int cost=0; //to hold the cost
    char line[100];// to hold the line from the file
    int myoption;

    // main menu
    while (1) {
        printf("\n------WELCOME TO THE NETWORK PACKET ROUTING SYSTEM------\n");
        printf("1. LOAD THE ROUTERS FROM THE INPUT FILE\n");
        printf("2. ENTER YOUR SOURCE ROUTER\n");
        printf("3. ENTER YOUR DESTINATION ROUTER\n");
        printf("4. EXIT FROM THE PROGRAM\n");
        printf("PLEASE ENTER YOUR CHOICE: ");
        scanf("%d", &myoption);

        //switch stetment to go through the menu
        switch (myoption) {
            case 1: {
                // Read input file
                FILE* inputfile = fopen("routers.txt", "r");
                if (!inputfile) {
                    printf("ERROR OPENING INPUT FILE.\n");
                    break;
                }

                while (fgets(line, sizeof(line), inputfile)) { // get line by line from the file
                    if (sscanf(line, "%[^-]-%[^-]-%d", source, destination, &cost) == 3) { // check if the line have all elements
                        ADDanEdge(&graph, source, destination, cost);//add the router to the graph
                    } else {
                        printf("INVALID LINE FORMAT: %s", line);
                    }
                }
                fclose(inputfile);

                printf("ROUTERS LOADED SUCCESSFULLY.\n");
                break;
            }
            case 2:
                //enter the source router
                printf("\nPLEASE ENTER SOURCE ROUTER: ");
                scanf("%s", source);
                break;


               case 3: {
                   //enter the dist router and print the results
                printf("\nPLEASE ENTER DESTINATION ROUTER: ");
                scanf("%s", destination);


                FILE* outputFile = fopen("shortest_distance.txt", "a");
                if (!outputFile) {
                    printf("ERROR OPENING OUTPUT FILE.\n");
                    break;
                }

                // Apply Dijkstra's algorithm and print results
                printf("\nDIJKSTRA'S ALGORITHM RESULT:\n");
                fprintf(outputFile, "\n DIJKSTRA'S ALGORITHM RESULT:\n");
                dijkstraalgo(&graph, source, destination, outputFile);

                // Apply BFS and print results
                printf("\nBREADTH-FIRST SEARCH (BFS) RESULT:\n");
                fprintf(outputFile, "\nBREADTH-FIRST SEARCH (BFS) RESULT:\n");
                bfsalgorthim(&graph, source, destination, outputFile);

                fclose(outputFile);
                break;
            }
            case 4:
                //print the result to output file and exit the program
                printf("\nRESULTS SAVED TO SHORTEST_DISTANCE.TXT\n");
                printf("\nEXITING THE PROGRAM.\n");
                return 0;

            default:
                printf("INVALID CHOICE. PLEASE TRY AGAIN.\n");
        }
    }
    return 0;
}
