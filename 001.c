#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SIZE 15     // 棋盘尺寸
#define EMPTY ' '   // 空位置
#define PLAYER1 'O' // 玩家1棋子
#define PLAYER2 'X' // 玩家2棋子

// 初始化棋盘
void init_board(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
}

// 打印棋盘
void print_board(char board[SIZE][SIZE]) {
    system("cls"); // 清屏（Windows系统）

    // 打印列号
    printf("   ");
    for (int j = 0; j < SIZE; j++) {
        printf("%2d ", j + 1);
    }
    printf("\n");

    // 打印棋盘内容
    for (int i = 0; i < SIZE; i++) {
        printf("%2d ", i + 1); // 行号
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("│"); // 列分隔线
        }
        printf("\n");

        // 打印行分隔线
        if (i < SIZE - 1) {
            printf("   ");
            for (int j = 0; j < SIZE; j++) {
                printf("───");
                if (j < SIZE - 1) printf("┼");
            }
            printf("\n");
        }
    }
}

// 检查是否获胜
int check_win(char board[SIZE][SIZE], int x, int y, char player) {
    // 定义4个检查方向（横、竖、斜、反斜）
    int dx[] = { 1, 0, 1, -1 };
    int dy[] = { 0, 1, 1, 1 };

    for (int i = 0; i < 4; i++) {
        int count = 1;

        // 正向检查
        int cx = x + dx[i], cy = y + dy[i];
        while (cx >= 0 && cx < SIZE && cy >= 0 && cy < SIZE &&
            board[cx][cy] == player) {
            count++;
            cx += dx[i];
            cy += dy[i];
        }

        // 反向检查
        cx = x - dx[i], cy = y - dy[i];
        while (cx >= 0 && cx < SIZE && cy >= 0 && cy < SIZE &&
            board[cx][cy] == player) {
            count++;
            cx -= dx[i];
            cy -= dy[i];
        }

        if (count >= 5) return 1;
    }
    return 0;
}

int main() {
    char board[SIZE][SIZE];
    int current_player = 0; // 当前玩家（0-玩家1，1-玩家2）
    int x, y;

    init_board(board);

    while (1) {
        print_board(board);
        printf("\n当前玩家：%c\n", current_player ? PLAYER2 : PLAYER1);
        printf("请输入落子坐标（行 列，范围1-%d）：", SIZE);

        // 获取输入并验证有效性
        if (scanf("%d %d", &x, &y) != 2 ||
            x < 1 || x > SIZE || y < 1 || y > SIZE) {
            printf("输入格式错误，请重新输入！\n");
            while (getchar() != '\n'); // 清空输入缓冲区
            continue;
        }

        // 转换为数组索引
        x--; y--;

        // 查验位置是否被占用
        if (board[x][y] != EMPTY) {
            printf("该位置已有棋子！\n");
            continue;
        }

        // 放置棋子
        board[x][y] = current_player ? PLAYER2 : PLAYER1;

        // 检查胜利条件
        if (check_win(board, x, y, board[x][y])) {
            print_board(board);
            printf("玩家 %c 获胜！\n", board[x][y]);
            break;
        }

        // 检查平局
        int is_full = 1;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    is_full = 0;
                    break;
                }
            }
            if (!is_full) break;
        }
        if (is_full) {
            print_board(board);
            printf("平局！\n");
            break;
        }

        // 切换玩家
        current_player = 1 - current_player;
    }

    return 0;
}
