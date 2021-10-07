#include<graphics.h>
#include<iostream>
#include<string>
#include<stdlib.h>
#include <time.h> 
#include <string.h>
#include <tchar.h>
#include <windows.h>
using namespace std;
COLORREF set_title_yellow = RGB(255, 255, 0);
COLORREF set_button_yellow = RGB(255, 255, 128);
COLORREF set_button_word_orange = RGB(220, 133, 31);
int player_count;
struct player {
    string name;
    int point[6];   //储存骰子结果
    int count[7];   //1-6储存1-6的计数，0储存自定义排名依据
    string rank;
} players[100];
//开始界面标题设置
void PrintTitle() {
    TCHAR s[] = _T("中  秋  博  饼");
    LOGFONT f;
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = 110;						// 设置字体高度为 110
    wcscpy_s(f.lfFaceName, _T("华光超粗黑_CNKI"));		// 设置字体为“华光超粗黑_CNKI”
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    settextstyle(&f);						// 设置字体样式
    settextcolor(set_title_yellow);//设置字体颜色
    outtextxy(125, 50, s);
}
//古诗词格式设置
void PrintPoem() {
    TCHAR a[] = _T("但愿人长久");
    TCHAR b[] = _T("千里共婵娟");
    LOGFONT f;
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = 25;						// 设置字体高度为 25
    wcscpy_s(f.lfFaceName, _T("华光行楷_CNKI"));		// 设置字体为“华光行楷_CNKI”
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    settextstyle(&f);						// 设置字体样式
    settextcolor(RGB(245, 154, 35));//设置字体颜色
    outtextxy(10, 390, a);
    outtextxy(50, 430, b);
}
void DrawRect_1() {
    RECT r = { 320, 310, 480, 375 };
    int r1[4] = { 320, 310, 480, 375 };
    setfillcolor(set_button_yellow);
    solidrectangle(320, 310, 480, 375);
    TCHAR a[] = _T("开始游戏");
    LOGFONT f;
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = 35;						// 设置字体高度为 25
    f.lfWeight = 1000;						//设置字体粗细
    wcscpy_s(f.lfFaceName, _T("宋体"));		// 设置字体为“华光行楷_CNKI”
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    settextstyle(&f);						// 设置字体样式
    settextcolor(set_button_word_orange);//设置字体颜色
    setbkmode(TRANSPARENT);				//设置背景为无填充
    drawtext(a, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    ExMessage m;//鼠标指针
    int flag = 1;
    while (flag) {
        m = getmessage(EM_MOUSE);//获取一条鼠标消息
        if (m.x > r1[0] && m.x<r1[2] && m.y>r1[1] && m.y < r1[3] && m.message == WM_LBUTTONDOWN) {
            //检查鼠标是否点击方框
            flag = 0;
        }
    }
}
//玩家名称输入
player CinPlayer() {
    struct player a;
    memset(&a, 0, sizeof(a));
    //cin >> a.name;
    return a;
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
        cout << a[i].rank<<a[i].count[0] << endl;
        
        /*测试*/
        for (int j = i; j > 0; j--) {//排名
            if (a[j].count[0] > a[j - 1].count[0]) {
                swap(a[j], a[j - 1]);
            }
        }
    }
}



int main() {
    srand((unsigned)time(NULL));
    /*
    initgraph(800, 500);//游戏窗口大小定义，初始化图像环境
    HWND hWnd = GetHWnd(); // 获得窗口句柄
    SetWindowText(hWnd, TEXT("中秋博饼"));
    setbkcolor(RGB(182, 46, 63));
    cleardevice();
    PrintTitle();
    PrintPoem();
    DrawRect_1();
    cleardevice();
    getchar();
    */
    
    /*先注释掉来检查界面*/
    cin >> player_count;
    for (int i = 0; i < player_count; i++) {
        players[i]= CinPlayer();
    }
    GameRunning(players, player_count);
    for (int i = 0; i < player_count; i++) {
        for (int j = 0; j < 6; j++) {
            cout << " " << players[i].point[j] << " ";
        }
        cout << players[i].rank << endl;
    }
    /**/
    return 0;
}
