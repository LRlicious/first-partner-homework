#include<iostream>
#include<string>
#include<stdlib.h>
#include <time.h> 
using namespace std;
struct player {
    string name;
    int point[6];   //储存骰子结果
    int count[7];   //1-6储存1-6的计数，0储存自定义排名依据
    string rank;
}players[10];//最大支持10名玩家（再大好像设计的界面不够用了）
//玩家名称输入
void CinPlayer(struct player a) {
    memset(&a, 0, sizeof(a));
    //cin >> a.name;
}

//骰子生成
player CreatePoint(struct player a) {
    for (int i = 0; i < 6; i++) {
        a.point[i] = rand() % 6+1;
        a.count[a.point[i]] += 1;
    }
    return a;
}

//结果判定
player Judge(struct player a) {
    if (a.count[4] == 4 && a.count[1] == 2) {
        a.count[0] = 130;
        a.rank = "插金花";
    }
    else if (a.count[4] == 6) {
        a.count[0] = 120;
        a.rank = "满堂红";
    }
    else if (a.count[1] == 6) {
        a.count[0] = 110;
        a.rank = "遍地锦";
    }
    else if (a.count[6] == 6) {
        a.count[0] = 103;
        a.rank = "黑六勃";
    }
    else if (a.count[5] == 6) {
        a.count[0] = 102;
        a.rank = "黑六勃";
    }
    else if (a.count[3] == 6) {
        a.count[0] = 101;
        a.rank = "黑六勃";
    }
    else if (a.count[2] == 6) {
        a.count[0] = 100;
        a.rank = "黑六勃";
    }
    else if (a.count[4] == 5) {
        a.count[0] = 90 + a.count[1] * 1 + a.count[2] * 2 + a.count[3] * 3 + a.count[5] * 5 + a.count[6] * 6;
        a.rank = "五红";
    }
    else if (a.count[6] == 5) {
        a.count[0] = 80 + a.count[1] * 1 + a.count[2] * 2 + a.count[3] * 3 + a.count[4] * 4 + a.count[5] * 5;
        a.rank = "五子登科";
    }
    else if (a.count[5] == 5) {
        a.count[0] = 80 + a.count[1] * 1 + a.count[2] * 2 + a.count[3] * 3 + a.count[4] * 4 + a.count[6] * 6;
        a.rank = "五子登科";
    }
    else if (a.count[3] == 5) {
        a.count[0] = 80 + a.count[1] * 1 + a.count[2] * 2 + a.count[6] * 6 + a.count[4] * 4 + a.count[5] * 5;
        a.rank = "五子登科";
    }
    else if (a.count[2] == 5) {
        a.count[0] = 80 + a.count[1] * 1 + a.count[6] * 6 + a.count[3] * 3 + a.count[4] * 4 + a.count[5] * 5;
        a.rank = "五子登科";
    }
    else if (a.count[1] == 5) {
        a.count[0] = 80 + a.count[6] * 6 + a.count[2] * 2 + a.count[3] * 3 + a.count[4] * 4 + a.count[5] * 5;
        a.rank = "五子登科";
    }
    else if (a.count[4] == 4) {
        a.count[0] = 60 + a.count[1] * 1 + a.count[2] * 2 + a.count[3] * 3 + a.count[5] * 5 + a.count[6] * 6;
        a.rank = "状元";
    }
    else if (a.count[1] == 1 && a.count[2] == 1 && a.count[3] == 1 && a.count[4] == 1 && a.count[5] == 1 && a.count[6] == 1) {
        a.count[0] = 50;
        a.rank = "榜眼";
    }
    else if (a.count[4] == 3) {
        a.count[0] = 40;
        a.rank = "探花";
    }
    else if (a.count[2] == 4) {
        a.count[0] = 30;
        a.rank = "进士";
    }
    else if (a.count[4] == 2) {
        a.count[0] = 20;
        a.rank = "举人";
    }
    else if (a.count[4] == 1) {
        a.count[0] = 10;
        a.rank = "秀才";
    }
    else {
        a.count[0] = 0;
        a.rank = "无";
    }
    return a;
}

//游戏进行
void GameRunning(struct player a[10], int count) {
    for (int i = 0; i < count; i++) {
        a[i] = CreatePoint(a[i]);
        a[i] = Judge(a[i]);
        /*测试*/
        printf("第%d次\n", i);
        for (int j = 0; j < 6; j++) {
            cout << " " << a[i].point[j]<<" ";
        }
        cout << a[i].rank << endl;
        /*测试*/
    }
}



int main() {
    int player_count;
    srand((unsigned)time(NULL));
    cin >> player_count;
    for (int i = 0; i < player_count; i++) {
        CinPlayer(players[i]);
    }
    GameRunning(players, player_count);

}