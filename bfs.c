#include <stdio.h>
#include <stdlib.h>
#define SIZE 40

struct queue {
    int items[SIZE];
    int front;
    int rear;
};

struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
void display(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);

struct node {
    int vertex;
    int cost;
    struct node* next;
};

struct node* createNode(int, int);

struct Graph {
  int numVertices;
  struct node** adjLists;
  int* costLists;
  int* visited;
};

struct node* createNode(int v, int cst) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->cost = cst;
  newNode->next = NULL;
  return newNode;
}

// Creating a graph
struct Graph* createGraph(int vertices) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  graph->adjLists = malloc(vertices * sizeof(struct node*));
  graph->visited = malloc(vertices * sizeof(int));
  graph->costLists = malloc(vertices * sizeof(int));

  int i;
  for (i = 0; i < vertices; i++) {
    graph->adjLists[i] = NULL;
    graph->visited[i] = 0;
    graph->costLists[i] = 0;
  }

  return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int cst) {
  // Add edge from src to dest
  struct node* newNode = createNode(dest,cst);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;

  // Add edge from dest to src
  newNode = createNode(src,cst);
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
}

// Create a queue
struct queue* createQueue() {
  struct queue* q = malloc(sizeof(struct queue));
  q->front = -1;
  q->rear = -1;
  return q;
}

// Check if the queue is empty
int isEmpty(struct queue* q) {
  if (q->rear == -1)
    return 1;
  else
    return 0;
}

// Adding elements into queue
void enqueue(struct queue* q, int value) {
  if (q->rear == SIZE - 1)
    printf("\nQueue is Full!!");
  else {
    if (q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
  }
}

// Removing elements from queue
int dequeue(struct queue* q) {
  int item;
  if (isEmpty(q)) {
    printf("Queue is empty");
    item = -1;
  } else {
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
      printf("Resetting queue ");
      q->front = q->rear = -1;
    }
  }
  return item;
}

// Print the queue
void printQueue(struct queue* q) {
  int i = q->front;

  if (isEmpty(q)) {
    printf("Queue is empty");
  } else {
    printf("\nQueue contains \n");
    for (i = q->front; i < q->rear + 1; i++) {
      printf("%d ", q->items[i]);
    }
  }
}

// BFS
void bfs(struct Graph* graph, int startVertex, int endVertex) {
  struct queue* q = createQueue();

  graph->visited[startVertex] = 1;
  enqueue(q, startVertex);

  while (!isEmpty(q)) {
    printQueue(q);
    int currentVertex = dequeue(q);
    printf("Visited %d\n", currentVertex);

    struct node* temp = graph->adjLists[currentVertex];
    int tcst = 0;
    int depth = 1;
    while (temp) {
      int adjVertex = temp->vertex;
      int c = temp->cost;
      tcst = c + tcst;
    
      if (graph->visited[adjVertex] == 0) {
        graph->visited[adjVertex] = 1;
        depth = depth + 1;
        enqueue(q, adjVertex);
      }
      if (adjVertex == endVertex){
        printf("total cost : %d \n", tcst);
        printf("depth : %d \n", depth);
        return;    
      }
      temp = temp->next;
    }
  }
}

int main() {
  int a, b;
  struct Graph* graph = createGraph(20);
  addEdge(graph, 0, 1, 71);
  addEdge(graph, 0, 2, 151);
  addEdge(graph, 1, 3, 75);
  addEdge(graph, 3, 2, 140);
  addEdge(graph, 3, 4, 118);
  addEdge(graph, 4, 5, 111);
  addEdge(graph, 5, 6, 70);
  addEdge(graph, 6, 7, 75);
  addEdge(graph, 7, 8, 120);
  addEdge(graph, 2, 9, 80);
  addEdge(graph, 9, 8, 146);
  addEdge(graph, 9, 10, 97);
  addEdge(graph, 2, 11, 99);
  addEdge(graph, 10, 12, 101);
  addEdge(graph, 11, 12, 211);
  addEdge(graph, 12, 13, 90);
  addEdge(graph, 12, 14, 85);
  addEdge(graph, 14, 15, 98);
  addEdge(graph, 15, 16, 86);
  addEdge(graph, 14, 17, 142);
  addEdge(graph, 17, 18, 92);
  addEdge(graph, 18, 19, 87);
  printf("Enter start and end vertex: \n");
  scanf("%d %d", &a, &b);
  bfs(graph, a, b);
    
  return 0;
}
