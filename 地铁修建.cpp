// 看不懂原来的代码, wocao
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define INFINITY 10000000

struct ArcCell {
    int v1, v2, dist;
};
struct GraphStruct {
    int vexnum, arcnum;
    struct ArcCell a[10000];
};
typedef struct GraphStruct* Graph;

Graph G = (Graph)malloc(sizeof(struct GraphStruct));
int Deep[10001];
int Parent[10001];
// functions
void inputData();
void quickSort(int s, int f);
int Partition(int s, int f);
int RandPartition(int s, int f);
int Kruskal();
int findRoot(int v);
int unionNode(int v1, int v2);
void swap(int n1, int n2);

int main(void) {

    int minDay = 0;
    inputData();
    quickSort(0, G->arcnum-1);

    minDay = Kruskal();
    printf("%d\n", minDay);

    return 0;
}
void inputData() {
    FILE* fp = fopen("dtxjNum.txt", "r");
    int vexnum, arcnum;
    fscanf(fp, "%d %d", &vexnum, &arcnum);
    G->vexnum = vexnum;
    G->arcnum = arcnum;
    // inputData
    fp = fopen("dtxjData.txt", "r");
    int i = 0, v1, v2, dist;
    for(i = 0; i < arcnum; i++) {
        fscanf(fp, "%d %d %d", &v1, &v2, &dist);
        G->a[i].v1 = v1;
        G->a[i].v2 = v2;
        G->a[i].dist = dist;
    }
}
void quickSort(int s, int f) {
    if(s >= f) {
        return;
    }
    int m = RandPartition(s, f);
    quickSort(s, m-1);
    quickSort(m+1, f);
}
int Partition(int s, int f) {
    int x = G->a[f].dist;
    int i = s-1, j;

    for(j = s; j < f; j++) {
        if(G->a[j].dist < x) {
            i++;
            swap(i, j);
        }
    }
    i++;
    swap(i, f);
    return i;
}
int RandPartition(int s, int f) {
    int r = rand() % (f-s) + s;
    swap(r, f);
    return Partition(s, f);
}
void swap(int n1, int n2) {
    struct ArcCell b = G->a[n1];
    G->a[n1] = G->a[n2];
    G->a[n2] = b;
}
int Kruskal() {
    // 什么时候不存在最小生成树呢?
    int i = 0;
    int v1, v2, dist = -INFINITY;
    for(i = 1; i <= G->vexnum; i++) {
        Parent[i] = i;
        Deep[i] = 0;
    }
    for(i = 0; i < G->arcnum; i++) {
        // 不断选取最小边
        // 如果不在一个集合里面, 就是我们要的节点, 如果在一个节点里面
        v1 = G->a[i].v1;
        v2 = G->a[i].v2;

        if(findRoot(v1) != findRoot(v2)) {
            if(dist < G->a[i].dist) {
                dist = G->a[i].dist;
            }
            unionNode(v1, v2);
        }
        if(findRoot(1) == findRoot(G->vexnum)) {
            break;
        }
    }
    return dist;
}
int findRoot(int v) {
    int p = Parent[v], lastP;
    while(p != Parent[p]) {
        lastP = p;
        p = Parent[p];
    }
    // 并查集要压缩路径
    Parent[v] = p;
    return p;
}
int unionNode(int v1, int v2) {
    int r1 = findRoot(v1);
    int r2 = findRoot(v2);

    if(Deep[r1] > Deep[r2]) {
        Parent[r2] = r1;
    } else {
        Parent[r1] = r2;
        if(Deep[r1] == Deep[r2]) {
            Deep[r2]++;
        }
    }
}
