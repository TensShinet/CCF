#include <stdio.h>
#include <malloc.h>
// 用链表存, 每次只取第一个.
// 我在存数据的时候就进行插入排序
struct ArcNode {
    int v;
    struct ArcNode* next;
};
struct VerNode {
    struct ArcNode* first;
};
struct GraphStruct {
    int vexnum, arcnum;
    struct VerNode List[10001];
};
typedef struct GraphStruct* Graph;
typedef struct ArcNode* Arc;

Graph G = (Graph)malloc(sizeof(struct GraphStruct));
int visite[10000];
int Path[20000];
int addArc = 0;

void insertList(int v1, int v2);
void DFS();
void addVisite(int v1, int v2);
int visitedPath(int v1, int v2);
int computedNum(int v1, int v2);
void swap(int* p1, int* p2);
void test_data();

int main(void) {
    int i;
    int v1, v2;
    FILE* fp = fopen("SHnum.txt", "r");
    fscanf(fp, "%d %d\n", &G->vexnum, &G->arcnum);
    // 初始化first
    for(i = 0; i < G->vexnum; i++) {
        G->List[i].first = NULL;
    }
    // 输入数据
    fp = fopen("SHdata.txt", "r");
    for(i = 0; i < G->arcnum; i++) {
        fscanf(fp, "%d %d", &v1, &v2);
        // 这是一个双向图
        // 我不用数组, 是为了提高速度
        insertList(v1, v2);
        insertList(v2, v1);
    }
    // 深搜图;
    // test_data();
    DFS();
    // // 没报错, 也没进入死循环, 有点慌
    if(addArc == G->arcnum) {
        for(i = 0; i <= addArc; i++) {
            printf("%d ", Path[i]);
        }
    }
    else {
        printf("-1");
    }
    return 0;
}
void insertList(int v1, int v2) {
    // 插入排序
    // 最小的在最前面
    // 三种情况
    // 开头, 中间, 结尾, 我先写中间的, 看满不满足, 开头和结尾
    Arc last = (Arc)malloc(sizeof(struct ArcNode));
    last = G->List[v1].first;
    Arc n = G->List[v1].first;
    Arc node = (Arc)malloc(sizeof(struct ArcNode));
    node->next = NULL;
    node->v = v2;
    if(n == NULL) {
        G->List[v1].first = node;
        return;
    }

    while (n) {
        if(v2 < n->v) { break; }
        last = n;
        n = n->next;
    }
    // 循环出来 1. n == NULL 2. v2 < n->v
    last->next = node;
    node->next = n;
}
void DFS() {
    // 从1开始 开始addArc
    // 条件是什么, 从最小的开始, 且原来没有访问过
    // 什么时候退出
    // 1. addArc == G->arcnum 2. 当前的节点不能再加边, 且addArc < G->arcnum
    Arc freeNode = (Arc)malloc(sizeof(struct ArcNode));
    Arc n = G->List[1].first;
    int v1 = 1;
    Path[0] = 1;
    int v2;
    while (1) {
        // 先取出来, 再说
        // 可能需要一个记录Path的数组
        while(n) {
            v2 = n->v;
            if(!visitedPath(v1, v2)) {
                break;
            }
            freeNode = n;
            n = n->next;
            // 反正访问过的路径就不会访问了, 直接删掉就好了(优化)
            G->List[v1].first = n;
            free(freeNode);
        }
        // 1. n == NULL, 2. 找到了没有访问过的路径
        if(n == NULL) {
            // if(addArc == G->arcnum) {
            //     // 可以完成, 就差一个Path(还不知道怎么做)
            //     break;
            // }
            // else {
            //     // 不可以完成, 输出-1；(还不知道该怎么做)
            //     // 反正也要退出循环.
            //     break;
            // }
            // 直接break;
            break;
        } else {
            // 找到一条没有访问过的路径
            addVisite(v1, v2);
            addArc++;
            Path[addArc] = v2;
            // 更新v1
            v1 = v2;
            n = G->List[v1].first;
        }
    }
}

void addVisite(int v1, int v2) {
    int num;
    //
    num = computedNum(v1, v2);
    visite[num] = 1;

}
int visitedPath(int v1, int v2) {
    int num = computedNum(v1, v2);
    if(visite[num] == 1) { return 1; }
    return 0;
}
int computedNum(int v1, int v2) {
    if(v1 < v2) {
        swap(&v1, &v2);
    }
    // 比如 (2, 1) 就是0
    v1--;
    int num = ((v1-1) * v1) / 2 + v2 - 1;
    return num;
}
void swap(int* p1, int* p2) {
    int c = *p2;
    *p2 = *p1;
    *p1 = c;
}
void test_data() {
    int i = 0;
    Arc n;
    for(i = 0; i < G->vexnum; i++) {
        n = G->List[i+1].first;
        printf("%d: ", i+1);
        while (n) {
            printf("%d ", n->v);
            n = n->next;
        }
        printf("\n");
    }
}
