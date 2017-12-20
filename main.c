#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 10
#define MAX_NUMBER_COURSES 10
#define MAX_NUMBER_STUDENTS 10

struct stack
{
    int stk[MAXSIZE];
    int top;
};
typedef struct stack STACK;

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

struct nodeStudent{

    char courseName[15];
    char studentName[30];
    struct coursesNamesofStudent *next;

};

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

int findSmallestUnvisitedNodeFromAdjacentList(struct Graph* graph, struct AdjListNode* adjacentList ,char *coursesNamesList[graph->V]){

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

    int colorList[graph->V];

    for (int i = 0; i < graph->V; ++i) { //Created a array of colors that is possible ( max color number is graph->v). And assigned them to the 0.
        colorList[i] = 0;
    }



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

void DFS(struct Graph* graph, char *coursesNamesList[graph->V], STACK *stackForDFS, int currentNodeIndexOfGraph){

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

char* concat(const char *s1, const char *s2){ //For string combining .
    char *result = malloc(strlen(s1)+strlen(s2)+strlen(" ")+1);//+1 for the null-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result," ");
    strcat(result, s2);
    return result;
}


void appendToLinkedList(struct nodeStudent** head_ref, char new_data[])
{
    /* 1. allocate node */
    struct nodeStudent* new_node = (struct nodeStudent*) malloc(sizeof(struct nodeStudent));

    struct nodeStudent* last;
    last = *head_ref;  /* used in step 5*/

    /* 2. put in the data  */
    strcpy(new_node->courseName,new_data);

    /* 3. This new node is going to be the last node, so make next of
          it as NULL*/
    new_node->next = NULL;

    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }

    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;

    /* 6. Change the next of last node */
    last->next = new_node;
    return;
}


int printList(struct nodeStudent *node)
{
    printf("  Printing the course names for %s : \n",node->studentName);
    int countNodes= -1;
    while (node != NULL)
    {
        printf(" %s ", node->courseName);
        node = node->next;
        countNodes++;
    }
    printf("\n");
    return countNodes;
}

//It will read one line of string and parse it to the get current student's name and courses he/she got.
//It will return the nodeStudent struct.
struct nodeStudent*  readLineAndReturnTheStudent(FILE *inputFile){ //Reads a line from the txt file and generates the student struct.

    if(feof(inputFile)){
        return NULL;
    }
    char* word;
    word = (char*) malloc(sizeof(char)*30);
    struct nodeStudent *newStudent;
    newStudent = (struct nodeStudent*) malloc(sizeof(struct nodeStudent));
    strcpy(newStudent->studentName,"");
    while (!feof(inputFile)) {

        fscanf(inputFile, "%s", word);
        if(strcmp(word,":") == 0){ //If it is a start of the courseNames.
            // Course Names are going to be read...
            fscanf(inputFile, "%s", word);

            while(strcmp(word,".") != 0){ //Till the end of the line.

                appendToLinkedList((&newStudent),word); //Append the courseName into the student Struct.
                fscanf(inputFile, "%s", word);
            }
            if (strcmp(word,".") == 0){
                break;
            }
        }else{//If this is a name word.

            strcpy(newStudent->studentName,concat(newStudent->studentName,word));
        }
    }
    return newStudent;
}

int main()
{

    char *coursesNamesList[MAX_NUMBER_COURSES] ; //Hold the courses names.

    for (int m = 0; m < MAX_NUMBER_COURSES; ++m) { // We assigned with a memory space.

        coursesNamesList[m] = malloc(10 * sizeof(char));

    }

    struct nodeStudent *nodeCourses = NULL; //Holds the nodes for courses.
    nodeCourses = (struct nodeStudent*) malloc(sizeof(struct nodeStudent));
    nodeCourses->next = NULL;
    strcpy(nodeCourses->studentName,"General Nodes");

    struct nodeStudent *nodeStudents[10] ; //Holds the entire students.
    for (int m = 0; m < MAX_NUMBER_STUDENTS; ++m) { //We assigned to the memory spaces.

        nodeStudents[m] = (struct nodeStudent*)malloc(sizeof(struct nodeStudent));

    }

    //Reading the file...

    FILE *inputFile;
    struct nodeStudent *newStudent;
    if((inputFile = fopen("/Users/mac/Desktop/Projects/Academic-C-Projects/ExamSchedulingUsingGraphColoringAlgorithm/input.txt","r")) == NULL){
        printf("Input File Could Not Be Opened!\n");
        return 0;
    }else{
        int currentStudentIndex = 0;


        while ((newStudent = readLineAndReturnTheStudent(inputFile)) != NULL){ //Scan the word.

            printf("\nNew Student's name: %s\n",newStudent->studentName);
            printList(newStudent);
            struct nodeStudent* tempStudentCourses;
            tempStudentCourses = newStudent;
            while(tempStudentCourses != NULL){//For every student's every course.

                struct nodeStudent* tempGeneralCourses;
                tempGeneralCourses = nodeCourses;


                //Investigate if the current course of the current student is already assigned, if its not append it to the generalList.
                while (tempGeneralCourses != NULL ){
                    if(strcmp(tempStudentCourses->courseName,tempGeneralCourses->courseName) == 0){

                        break; //If there is a word like this, break.
                    }

                    tempGeneralCourses = tempGeneralCourses->next ;

                }
                if(tempGeneralCourses == NULL){
                    //If temp is NULL , it means that we are at the end of the tempStudent list.

                    appendToLinkedList(&nodeCourses,tempStudentCourses->courseName);

                }
                tempStudentCourses = tempStudentCourses->next;
            }
            nodeStudents[currentStudentIndex] = newStudent;
            currentStudentIndex++;
        }
    }
    //End of reading the txt file !!


    fclose(inputFile);
    int V = printList(nodeCourses); //Linked list that holds the all the courses.

    // create the graph given in above figure
    struct Graph* graph = createGraph(V);

    int coursesIndex = 0;
    struct nodeStudent* tempCourses;
    tempCourses = nodeCourses->next;
    while (tempCourses != NULL){ //Assigning the courseNamesList with the data we collected as General Course Nodes.

        strcpy(coursesNamesList[coursesIndex],tempCourses->courseName);
        tempCourses = tempCourses->next;
        coursesIndex++;
    }

    //Starting to adding edges...
    for (int n = 0; n < 10; ++n) {

        if (strcmp(nodeStudents[n]->studentName,"") == 0){ // If the current student is not exists !
            break;
        }

        struct nodeStudent* tempBaseCourse;
        tempBaseCourse = nodeStudents[n]->next;

        while(tempBaseCourse != NULL){

            struct nodeStudent* tempDestCourse;
            tempDestCourse = tempBaseCourse->next;

            int tempBaseCourseIndex = 0;

            for (int i = 0; i < MAX_NUMBER_COURSES; ++i) { //Trying to find the base course's index.

                if(strcmp(coursesNamesList[i],tempBaseCourse->courseName) == 0){

                    tempBaseCourseIndex = i ;
                }
            }

            while(tempDestCourse != NULL){

                int tempDestCourseIndex = 0;

                for (int i = 0; i < MAX_NUMBER_COURSES; ++i) {//Trying to find the dest course's index.

                    if(strcmp(coursesNamesList[i],tempDestCourse->courseName) == 0){

                        tempDestCourseIndex = i ;
                    }

                }

                printf("\n-- Adding edge at (%d,%d) \n",tempBaseCourseIndex,tempDestCourseIndex);
                struct AdjListNode* adjacentListIterator ;
                adjacentListIterator = graph->array[tempBaseCourseIndex].head;
                int isAlreadyConnected = 0;

                while (adjacentListIterator){

                    if (adjacentListIterator->dest == tempDestCourseIndex){

                        isAlreadyConnected = 1;
                        break;

                    }else{

                        adjacentListIterator = adjacentListIterator->next;
                    }

                }

                if(isAlreadyConnected == 0){

                    addEdge(graph, tempBaseCourseIndex, tempDestCourseIndex);

                }else{

                    printf("\n%s and %s already connected.\n",coursesNamesList[tempBaseCourseIndex],coursesNamesList[tempDestCourseIndex]);
                }

                tempDestCourse = tempDestCourse->next;

            }

            tempBaseCourse = tempBaseCourse->next;

        }
    }

    //End of adding edges.

    printGraph(graph);

    STACK *stackForDFS; // Created a stack for store the LIFO actions during DFS traversal of nodes. We will push every vertex that we visited.
    stackForDFS = malloc(sizeof(STACK));
    stackForDFS->top = -1;

    DFS(graph,coursesNamesList,stackForDFS,3); //DFS traversal. It is also assigning the colors.

    int biggesColorIndex = -1;
    for (int k = 0; k < graph->V; ++k) { //Try to find biggestColorIndex for later use in the output.
        if (graph->array[k].color > biggesColorIndex){
            biggesColorIndex = graph->array[k].color;
        }

    }

    int scheduleList[biggesColorIndex+1];

    for (int l = 0; l < biggesColorIndex + 1; ++l) { //Assign 0 to all the period array's elements.

        scheduleList[l] = 0;

    }

    for (int j = 0; j < biggesColorIndex+1; ++j) { //Printing the Final Exam Periods.

        printf("\nFinal Exam Period %d => ", j+1);

        for (int i = 0; i < graph->V; ++i) {

            if(graph->array[i].color == j){

                printf(" %-10s",coursesNamesList[i]);

            }
        }
    }

    return 0;
}