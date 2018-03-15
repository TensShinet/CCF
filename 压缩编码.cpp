#include<stdio.h>

#define INIF 999999999

int n;
int sum[1001][1001];
int dp[1001][1001] = { 0 };
int num[1001];

void runDp();

int main(void) {
    int i;
    scanf("%d", &n);
    // 输入数据
    for(i = 1; i <= n; i++) {
        scanf("%d", &num[i]);
    }
    // 动态规划解决问题
    runDp();
    return 0;
}

void runDp() {
    int i, j, k, t, min;
    // 先初始化sum[][]
    // 使sum[][], 存着, 合并的值, 由合并的方法确定的值, 才是关键
    for (i = 1; i <= n; i++) {
        sum[i][i] = num[i];
        for(j = i+1; j <= n; j++) {
            sum[i][j] = sum[i][j-1] + num[j];
        }
    }
    // 由长度开始
    for(j = 2; j <= n; j++) {
        // 从后往前
        for(i = j-1; i > 0; i--) {
            // 从 i 到 j 多种情况, 每种情况, 得到的dp值是不一样的
            // 要找到最小的dp值
            min = dp[i][j] = INIF;
            for(k = i; k < j; k++) {
                 t = dp[i][k] + dp[k+1][j] + sum[i][j];
                 if(t < min){ min = t; }
            }
            dp[i][j] = min;
        }
    }
    printf("%d", dp[1][n]);
}
