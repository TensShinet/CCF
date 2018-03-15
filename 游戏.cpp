#include <stdio.h>
#include <stdlib.h>

struct queueRecord{
    int c, r, t;
};
struct danStruct{
    int s, f;
};
struct queueStruct {
    int f, r;
    struct queueRecord q[10001];
};
int n, m, t;
struct danStruct dan[10000];
struct queueStruct queue;
int data[101][101] = { 0 };

int computeNum(int a, int b);
int Equal(int c, int r, int time);
void BFS();
void push(int c, int r, int time);
struct queueRecord pop();
int isDangerous(int c, int r, int time);

int main(void) {
    queue.f = queue.r = 0;
    // printf("queue: %d %d %d\n", queue.f, queue.r, sizeof(queue.q));
    int i, x, y, s, f, danXY;
    scanf("%d %d %d", &n, &m, &t);
    // printf("Output YXnum:%d %d %d\n", n, m, t);
    // 输入数据
    for(i = 0; i < 10000; i++) {
        dan[i].s = -1;
    }
    for(i = 0; i < t; i++) {
        scanf("%d %d %d %d", &x, &y, &s, &f);
        // printf("Output YXdata:%d %d %d %d\n", dan[i].x, dan[i].y, dan[i].s, dan[i].f);
        // 从0 开始计数 , 对吧, 比如 x = 1, y = 1 应该存在0处
        danXY = (x-1) * m + y-1;
        dan[danXY].s = s;
        dan[danXY].f = f;
    }

    BFS();
    // 测试isDangerous()
    // test_iD();
    // 测试push()
    return 0;
}
void BFS() {
    // 先把第一个元素放进去
    // time 用来 记录, 最后一个元素进去的时间
    int time = 0;
    data[1][1] = -1;
    push(1, 1, 0);
    struct queueRecord q;
    // 条件是, 最后一个元素被放入队列, break;
    // printf("f e: %d %d %d\n", queue.q[queue.r].c, queue.q[queue.r].r, queue.q[queue.r].t);
    while (1) {
        // 把队首元素取出来
        q = pop();
        // 加入元素, 如果是最后一个元素, break;
        // c是列, r 是行
        // m是列, n 是行
        // 先放 列再放 行
        // 这样写完全是鬼畜
        // 但我不知道怎么加条件
        // printf("Output q: %d %d %d\n", q.c, q.r, q.t);
        time = q.t + 1;
        if(q.c == m && q.r+1 == n) {
            break;
        }
        push(q.c, q.r+1, time);
        if(q.c == m && q.r+1 == n) {
            break;
        }
        push(q.c, q.r-1, time);
        if(q.c+1 == m && q.r == n) {
            break;
        }
        push(q.c+1, q.r, time);
        if(q.c+1 == m && q.r == n) {
            break;
        }
        push(q.c-1, q.r, time);
    }
    // 输出t;
    printf("%d\n", time);
}
void push(int c, int r, int time) {
    if((c < 1 || c > m) || (r < 1 || r > n)) {
        // printf("OUTline!\n");
        return;
    }
    if(isDangerous(c, r, time) || Equal(c, r, time)) { return; }

    // 时间相等的时候就不用入队了
    data[c][r] = time;
    queue.r = (queue.r + 1) % 10000;
    queue.q[queue.r].c = c;
    queue.q[queue.r].r = r;
    queue.q[queue.r].t = time;
    // printf("push() %d %d \n", queue.r, queue.f);
}
struct queueRecord pop() {

    struct queueRecord q;
    queue.f = (queue.f + 1) % 10000;
    q.c = queue.q[queue.f].c;
    q.r = queue.q[queue.f].r;
    q.t = queue.q[queue.f].t;
    return q;
}

int isDangerous(int c, int r, int time) {
    int i;
    int XY = (c-1) * m + r-1;
    // 这个可以优化
    if(dan[XY].s == -1) {
        return 0;
    } else {
        int risk = (time - dan[XY].s) * (time - dan[XY].f);
        return risk <= 0;
    }
}
int Equal(int c, int r, int time) {
    if(data[c][r] == time) { return 1; }
    return 0;
}


void test_iD() {
    if(isDangerous(2, 1, 1)) {
        printf("Y\n");
    }
    if(isDangerous(2, 2, 2)) {
        printf("Y\n");
    }
    if(isDangerous(2, 2, 3)) {
        printf("Y\n");
    }
    if(isDangerous(1, 3, 2)) {
        printf("Y\n");
    }
    if(isDangerous(1, 3, 3)) {
        printf("Y\n");
    }
    if(!isDangerous(1, 2, 1)) {
        printf("Y\n");
    }
}
// 要运行程序了, 我好紧张。
