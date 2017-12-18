#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 * C program to implement stack. Stack is a LIFO data structure.
 * Stack operations: PUSH(insert operation), POP(Delete operation)
 * and Display stack.
 */
#define MAXSIZE 10

struct stack
{
    int stk[MAXSIZE];
    int top;
};
typedef struct stack STACK;

/*  Function to add an element to the stack */
void pushStack (STACK *s ,int num)
{
    if (s->top == (MAXSIZE - 1))
    {
        printf ("   Stack is Full\n");
        return;
    }
    else
    {

        s->top = s->top + 1;
        s->stk[s->top] = num;
        printf ("   Pushed element is = %d\n", s->stk[s->top]);

    }
    return;
}
/*  Function to delete an element from the stack */
int popStack (STACK *s)
{
    int num;
    if (s->top == - 1)
    {
        printf ("   Stack is Empty\n");
        return (s->top);
    }
    else
    {
        num = s->stk[s->top];
        printf ("   Poped element is = %d\n", s->stk[s->top]);
        s->top = s->top - 1;
    }
    return(num);
}
/*  Function to display the status of the stack */
void displayStack (STACK *s)
{
    int i;
    if (s->top == -1)
    {
        printf ("   Stack is empty\n");
        return;
    }
    else
    {
        printf ("\n   The status of the stack is \n");
        for (i = s->top; i >= 0; i--)
        {
            printf ("\n    | %d |", s->stk[i]);
        }
    }
    printf ("\n    |---|\n");
}

// A structure to represent an adjacency list node
struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};

// A structure to represent an adjacency list
struct AdjList
{
    struct AdjListNode *head;// pointer to head node of list
    int isVisited ;
    int color ;
};

// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};

// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;

    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest)
{
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    graph->array[src].color=-1;
    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
    graph->array[dest].color = -1;
}

// A utility function to print the adjacency list representation of graph
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

int findSmallestUnvisitedNodeFromAdjacentList(struct Graph* graph, struct AdjListNode* adjacentList ,char *coursesNamesList[6]){

    char starterPointString[16] ;
    strcpy(starterPointString,"ZZZZZZZZZZZZZZZ");
    int starterPoint= -1;
    while (adjacentList)
        {
            if (strcmp(coursesNamesList[adjacentList->dest],starterPointString)  < 0  && graph->array[adjacentList->dest].isVisited != 1 ){ //We are trying to find the smallest course name value to set the starting point.

                strcpy(starterPointString,coursesNamesList[adjacentList->dest]);
                starterPoint = adjacentList->dest;


            }
            adjacentList = adjacentList->next;
        }




        return starterPoint;



}


void colorTheNode(struct Graph* graph,char *coursesNamesList[6],int currentNodeIndexOfGraph,struct AdjListNode* adjacentList){

    int colorList[6];
    colorList[0]=0;
    colorList[1]=0;
    colorList[2]=0;
    colorList[3]=0;
    colorList[4]=0;
    colorList[5]=0;

    printf("\n   Coloring Algorithm is Starting for %s... \n",coursesNamesList[currentNodeIndexOfGraph]);
    while (adjacentList)
    {
        if ( graph->array[adjacentList->dest].color > -1){ //If there is a color assigned before.

            colorList[graph->array[adjacentList->dest].color] = 1; //We add this color to the colorList array so we can later traverse it to find the smallest color we can color the currentNode.
            printf("   Color %d is now in adjacent colors of the %s. Because of the node %s\n",
                   graph->array[adjacentList->dest].color, coursesNamesList[currentNodeIndexOfGraph],coursesNamesList[adjacentList->dest]);

        }
        adjacentList = adjacentList->next;
    }
    int foundSmallestColorIndex = 0;
    int index = 0 ;
    while(foundSmallestColorIndex == 0){

        if(colorList[index] != 1){
            graph->array[currentNodeIndexOfGraph].color = index; //We color the current node with the first empty color index from adjacents.
            printf("   %s is colored to the %d color.\n",coursesNamesList[currentNodeIndexOfGraph],graph->array[currentNodeIndexOfGraph].color);
            foundSmallestColorIndex=1;
        }

        index++;


    }


}

void DFS(struct Graph* graph, char *coursesNamesList[6], STACK *stackForDFS, int currentNodeIndexOfGraph){

    printf("\nDFS is running for %s\n",coursesNamesList[currentNodeIndexOfGraph]);
    if(graph->array[currentNodeIndexOfGraph].isVisited == 1){ //If the currentNode is visited.


        int popResponse = popStack(stackForDFS);
        displayStack(stackForDFS);

        if(popResponse == -1 || stackForDFS->top == -1){ //If stack is empty already or we just made it empty.
            return;
        }else{

            DFS(graph,coursesNamesList,stackForDFS,stackForDFS->stk[stackForDFS->top]);

        }


    }else{

        graph->array[currentNodeIndexOfGraph].isVisited = 1;//Mark as visited.
        pushStack(stackForDFS,currentNodeIndexOfGraph);//Push the stack.
        displayStack(stackForDFS);

        int smallestUnvisitedNodeIndex = findSmallestUnvisitedNodeFromAdjacentList(graph,graph->array[currentNodeIndexOfGraph].head,coursesNamesList);
        colorTheNode(graph,coursesNamesList,currentNodeIndexOfGraph,graph->array[currentNodeIndexOfGraph].head);

        if(smallestUnvisitedNodeIndex == -1){ //If there is no adjacent un-visited node.

            popStack(stackForDFS); //Pop the last element in the stack.
            displayStack(stackForDFS);

            DFS(graph,coursesNamesList,stackForDFS,stackForDFS->stk[stackForDFS->top]);

        }
        else{

            DFS(graph,coursesNamesList,stackForDFS,smallestUnvisitedNodeIndex); //Recall the DFS algorithm.
        }

    }





}


// Driver program to test above functions
int main()
{


    char *studentNameList[4] ;
    studentNameList[0] = "Ayse Kara";
    studentNameList[1] = "Efe Anil";
    studentNameList[2] = "Suat Ali Barut";
    studentNameList[3] = "Nil Girgin";


    char *coursesNamesList[6] ;
    coursesNamesList[0] = "MATH101";
    coursesNamesList[1] = "CSE100";
    coursesNamesList[2] = "MATH259";
    coursesNamesList[3] = "BLAW203";
    coursesNamesList[4] = "STAT253";
    coursesNamesList[5] = "HIST111";







    // create the graph given in above figure
    int V = 6;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 0, 3);
    addEdge(graph, 2, 5);
    addEdge(graph, 2, 4);
    addEdge(graph, 4, 5);
    addEdge(graph, 3, 2);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 5);
    addEdge(graph, 3, 5);
    addEdge(graph, 0, 4);
    addEdge(graph, 5, 2);


    printGraph(graph);



    STACK *stackForDFS; //Created a stack for store the LIFO actions during DFS traversal of nodes. We will push every vertex that we visited.
    stackForDFS = malloc(sizeof(STACK));
    stackForDFS->top = -1;



    DFS(graph,coursesNamesList,stackForDFS,3);



    int biggesColorIndex = -1;
    for (int k = 0; k < graph->V; ++k) { //Try to find biggestColorIndex for later use in the output.
        if (graph->array[k].color>biggesColorIndex){
            biggesColorIndex = graph->array[k].color;
        }

    }

    int scheduleList[biggesColorIndex+1];


    for (int l = 0; l < biggesColorIndex + 1; ++l) { //Assign 0 to all the period array's elements.


        scheduleList[l] = 0;


    }

    for (int j = 0; j < biggesColorIndex+1; ++j) {

        printf("\nFinal Exam Period %d => ", j+1);

        for (int i = 0; i < graph->V; ++i) {

            if(graph->array[i].color == j){

                printf(" %-10s",coursesNamesList[i]);

            }
        }
    }


    return 0;
}