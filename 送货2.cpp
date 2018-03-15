#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

// stack
struct StackStruct {
    int top;
    int a[10001];
};
// queue
struct QueueStruct {
    int r, f;
    int a[10001];
};
// ArcNode
struct ArcNode {
    int v;
    struct ArcNode* next;
};
struct ArcCell {
    struct ArcNode* first;
};
struct GraphStruct {
    int vexnum, arcnum;
    struct ArcCell a[10001];
};

typedef struct QueueStruct* Queue;
typedef struct StackStruct* Stack;
typedef struct GraphStruct* Graph;
typedef struct ArcNode* Arc;

Graph G = (Graph)malloc(sizeof(struct GraphStruct));
Queue q = (Queue)malloc(sizeof(struct QueueStruct));
Stack sk = (Stack)malloc(sizeof(struct StackStruct));

int du[10001];
int visite[10001];
int Path[100000];
int allElements = 0;
int enterNum = 0;

void inputData();
void insertList(int v1, int v2);
int judgedOuLa();
int connectedGraph(int s);
void DFS(int s);
void OuLa();
void push(int v);
int top();
int pop();
void deleteEdges(int v1, int v2);
void deleteOneEdge(int v1, int v2);


void test_data();

int main(void) {
    int i;
    inputData();
    // test_data();
    if(!judgedOuLa()) {
        printf("-1\n");
        return 0;
    }
    // initialize Stack
    sk->top = -1;
    OuLa();

    for(i = enterNum-1; i > -1; i--) {
        printf("%d ", Path[i]);
    }

    return 0;
}
void inputData() {
    int vexnum, arcnum;
    scanf("%d %d", &vexnum, &arcnum);
    G->vexnum = vexnum;
    G->arcnum = arcnum;
    // inputData
    int i = 0, v1, v2;

    for(i = 1; i <= G->vexnum; i++) {
        G->a[i].first = NULL;

    }
    for(i = 1; i <= G->arcnum; i++) {
        scanf("%d %d", &v1, &v2);
        insertList(v1, v2);
        insertList(v2, v1);
        du[v1]++;
        du[v2]++;
    }
}
void insertList(int v1, int v2) {
    Arc n, lastN;
    Arc newNode = (Arc)malloc(sizeof(struct ArcNode));
    newNode->v = v2;
    newNode->next = NULL;
    lastN = n = G->a[v1].first;
    // insert Sort
    while(n) {
        if(n->v > v2) { break; }
        lastN = n;
        n = n->next;
    }
    // n == NULL or breakOut
    if(n == lastN) {
        G->a[v1].first = newNode;
        // firstElement
        newNode->next = n;
        return;
    }
    lastN->next = newNode;
    newNode->next = n;
}
int judgedOuLa() {
    int i, o = 0;
    for(i = 1; i <= G->vexnum; i++) {
        if(du[i] % 2 == 1) {
            o++;
        }
    }
    if(o == 2 && du[1] % 2 == 0) {
        return 0;
    }
    if(o > 2) {

        return 0;
    }
    if(!connectedGraph(1)) {

        return 0;
    }
    return 1;
}
int connectedGraph(int s) {
    visite[s] = 1;
    allElements++;
    DFS(s);
    // int i;
    // for(i = 1; i <= G->vexnum; i++) {
    //     printf("%d %d\n", i, visite[i]);
    // }
    // printf("%d\n", allElements);
    return allElements == G->vexnum;
}
void DFS(int s) {
    int v;
    Arc n = G->a[s].first;
    while(n) {
        v = n->v;
        if(!visite[v]) {
            allElements++;
            visite[v] = 1;
            DFS(v);
        }
        n = n->next;
    }
}
void OuLa() {
    Arc n;
    int v1, v2, v3;
    push(1);

    while(sk->top > -1) {
        v1 = top();
        n = G->a[v1].first;
        if(n == NULL) {
            v3 = pop();
            Path[enterNum++] = v3;
        } else {
            v2 = n->v;
            deleteEdges(v1, v2);
            push(v2);
        }
    }
}
void push(int v) {
    sk->top++;
    sk->a[sk->top] = v;
}
int top() {
    return sk->a[sk->top];
}
int pop() {
    int e = sk->a[sk->top];
    sk->top--;
    return e;
}
void deleteEdges(int v1, int v2) {
    deleteOneEdge(v1, v2);
    deleteOneEdge(v2, v1);
}
void deleteOneEdge(int v1, int v2) {
    Arc n = G->a[v1].first;
    Arc lastN = n;
    Arc freeNode;
    int v;
    while(n) {
        v = n->v;
        if(v2 == v) { break; }
        lastN = n;
        n = n->next;
    }
    if(lastN == n) {
        // n不会是NULL
        freeNode = n;
        n = n->next;
        G->a[v1].first = n;
        free(freeNode);
        return;
    }
    freeNode = n;
    n = n->next;
    lastN->next = n;
    free(freeNode);
}
void test_data() {
    int i = 0;
    Arc n;
    for(i = 1; i <= G->vexnum; i++) {
        n = G->a[i].first;
        printf("%d ", i);
        while(n) {
            printf("%d ", n->v);
            n = n->next;
        }
        printf("\n");
    }
}
