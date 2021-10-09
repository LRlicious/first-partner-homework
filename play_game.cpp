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
int player_count;   //玩家数量 因界面设计偏小只能显示到8
IMAGE dice_1[6], dice_2[6];     //骰子图片
struct player {
    string name;
    int point[6];   //储存骰子结果
    int count[7];   //1-6储存1-6的计数，0储存自定义排名依据
    string rank;
} players[10];

//骰子图片输入
void InputDice() {
    loadimage(&dice_1[0], _T(".\\photo\\1.png"), 40, 40, true);
    loadimage(&dice_1[1], _T(".\\photo\\2.png"), 40, 40, true);
    loadimage(&dice_1[2], _T(".\\photo\\3.png"), 40, 40, true);
    loadimage(&dice_1[3], _T(".\\photo\\4.png"), 40, 40, true);
    loadimage(&dice_1[4], _T(".\\photo\\5.png"), 40, 40, true);
    loadimage(&dice_1[5], _T(".\\photo\\6.png"), 40, 40, true);
    loadimage(&dice_2[0], _T(".\\photo\\1.png"), 30, 30, true);
    loadimage(&dice_2[1], _T(".\\photo\\2.png"), 30, 30, true);
    loadimage(&dice_2[2], _T(".\\photo\\3.png"), 30, 30, true);
    loadimage(&dice_2[3], _T(".\\photo\\4.png"), 30, 30, true);
    loadimage(&dice_2[4], _T(".\\photo\\5.png"), 30, 30, true);
    loadimage(&dice_2[5], _T(".\\photo\\6.png"), 30, 30, true);
}

/*网上找的wchar_t转string*/
string wchar_tToString(wchar_t* wchar) {
    string szDst;
    wchar_t* wText = wchar;
    DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);
    char* psText;
    psText = new char[dwNum];
    WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);
    szDst = psText;
    delete[]psText;
    return szDst;
}

/*网上找的string转wchar_t*/
wchar_t* stringToWchar_t(string str) {
    string temp = str;
    int len = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)temp.c_str(), -1, NULL, 0);
    wchar_t* wszUtf8 = new wchar_t[len + 1];
    memset(wszUtf8, 0, len * 2 + 2);
    MultiByteToWideChar(CP_ACP, 0, (LPCSTR)temp.c_str(), -1, (LPWSTR)wszUtf8, len);
    return wszUtf8;
}
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

//古诗词格式设置输出
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

//开始按钮绘制和反馈
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

//界面2，输入人数
void PrintPage2() {
    TCHAR s[] = _T("请输入参与人数（不超过8）");
    LOGFONT f;
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = 45;						// 设置字体高度为 45
    wcscpy_s(f.lfFaceName, _T("黑体"));		// 设置字体为“黑体”
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    settextstyle(&f);						// 设置字体样式
    settextcolor(set_title_yellow);//设置字体颜色
    outtextxy(100, 100, s);

    RECT r = { 320, 310, 480, 375 };
    int r1[4] = { 320, 310, 480, 375 };
    setfillcolor(set_button_yellow);
    solidrectangle(320, 310, 480, 375);
    TCHAR a[] = _T("输入人数");
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = 35;						// 设置字体高度为 35
    f.lfWeight = 1000;						//设置字体粗细
    wcscpy_s(f.lfFaceName, _T("宋体"));		// 设置字体为“宋体”
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    settextstyle(&f);						// 设置字体样式
    settextcolor(set_button_word_orange);//设置字体颜色
    setbkmode(TRANSPARENT);				//设置背景为无填充
    drawtext(a, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    ExMessage m;//鼠标指针
    int flag = 1;
    while (flag) {
        m = getmessage(EM_MOUSE);//获取一条鼠标消息
        if (m.x > r1[0] && m.x<r1[2] && m.y>r1[1] && m.y < r1[3] && m.message == WM_LBUTTONDOWN)
            flag = 0;
    }
    wchar_t x[10];
    InputBox(x, 10, L"请输入人数");		//输入界面
    player_count = _wtoi(x);
    cleardevice();  //清屏
}

//界面3，输入玩家名称
void PrintPage3() {
    TCHAR s[] = _T("请输入玩家名称");
    LOGFONT f;
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = 45;						// 设置字体高度为 45
    wcscpy_s(f.lfFaceName, _T("黑体"));		// 设置字体为“黑体”
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    settextstyle(&f);						// 设置字体样式
    settextcolor(set_title_yellow);//设置字体颜色
    outtextxy(230, 100, s);

    RECT r = { 320, 310, 480, 375 };
    int r1[4] = { 320, 310, 480, 375 };
    setfillcolor(set_button_yellow);
    solidrectangle(320, 310, 480, 375);
    TCHAR a[] = _T("输入名称");
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = 35;						// 设置字体高度为 35
    f.lfWeight = 1000;						//设置字体粗细
    wcscpy_s(f.lfFaceName, _T("宋体"));		// 设置字体为“宋体”
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    settextstyle(&f);						// 设置字体样式
    settextcolor(set_button_word_orange);//设置字体颜色
    setbkmode(TRANSPARENT);				//设置背景为无填充
    drawtext(a, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    ExMessage m;//鼠标指针
    int flag = 1;
    while (flag) {
        //按钮判定
        m = getmessage(EM_MOUSE);//获取一条鼠标消息
        if (m.x > r1[0] && m.x<r1[2] && m.y>r1[1] && m.y < r1[3] && m.message == WM_LBUTTONDOWN)
            flag = 0;
    }
    for (int i = 0; i < player_count; i++) {
        wchar_t x[30];
        InputBox(x, 30, L"请输入名称");		//输入界面
        players[i].name = wchar_tToString(x);
    }
    cleardevice();  //清屏
}

//界面4功能，掷骰子按钮判定
void Page4Button() {
    int flag = 1;
    int r1[4] = { 470, 185, 635, 250 };
    ExMessage m;//鼠标指针
    while (flag) {
        m = getmessage(EM_MOUSE);//获取一条鼠标消息
        if (m.x > r1[0] && m.x<r1[2] && m.y>r1[1] && m.y < r1[3] && m.message == WM_LBUTTONDOWN)
            flag = 0;
    }
    flushmessage;
}

//界面4，绘制排名
void DrawRank(int times) {
    LOGFONT f;
    //画背景
    setfillcolor(RGB(255, 255, 128));
    solidrectangle(0, 0, 280, 500);
    //画标题
    TCHAR a[] = _T("排    名");
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = 40;
    f.lfWeight = 1000;						//设置字体粗细
    wcscpy_s(f.lfFaceName, _T("宋体"));
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    settextstyle(&f);						// 设置字体样式
    settextcolor(RGB(217, 0, 27));//设置字体颜色
    setbkmode(TRANSPARENT);				//设置背景为无填充
    settextstyle(&f);
    outtextxy(45, 0, a);
    f.lfHeight = 20;
    settextstyle(&f);
    for (int i = 0; i < times; i++) {
        wchar_t* b[30], * c[30];
        *b = stringToWchar_t(players[i].name);
        *c = stringToWchar_t(players[i].rank);
        outtextxy(10, 50 + 55 * i, *b);
        outtextxy(110, 50 + 55 * i, *c);
        for (int j = 0; j < 6; j++) {
            putimage(10 + 45 * j, 75 + 55 * i, &dice_2[players[i].point[j]-1]);
        }
    }
}

//界面4，绘制碗里骰子动画和结果
void DrawDice(int no) {
    for (int i = 0; i < 8; i++) {
        putimage(470, 290, &dice_1[rand() % 6]);
        putimage(530, 290, &dice_1[rand() % 6]);
        putimage(590, 290, &dice_1[rand() % 6]);
        putimage(470, 350, &dice_1[rand() % 6]);
        putimage(530, 350, &dice_1[rand() % 6]);
        putimage(590, 350, &dice_1[rand() % 6]);
        Sleep(200);
    }
    putimage(470, 290, &dice_1[players[no].point[0]-1]);
    putimage(530, 290, &dice_1[players[no].point[1]-1]);
    putimage(590, 290, &dice_1[players[no].point[2]-1]);
    putimage(470, 350, &dice_1[players[no].point[3]-1]);
    putimage(530, 350, &dice_1[players[no].point[4]-1]);
    putimage(590, 350, &dice_1[players[no].point[5]-1]);
}

//界面4 绘制右边界面
void PrintPage4() {
    TCHAR a[] = _T("中 秋 博 饼");
    LOGFONT f;
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = 76;						// 设置字体高度为 76
    wcscpy_s(f.lfFaceName, _T("黑体"));		// 设置字体为“黑体”
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    settextstyle(&f);						// 设置字体样式
    settextcolor(set_title_yellow);//设置字体颜色
    outtextxy(340, 15, a);
    //画圆
    setfillcolor(WHITE);
    fillcircle(550, 300, 190);
    //画按钮
    setfillcolor(set_button_yellow);
    solidrectangle(470, 185, 635, 250);
    RECT o = { 470, 185, 635, 250 };
    TCHAR b[] = _T("开始游戏");
    gettextstyle(&f);
    f.lfHeight = 35;
    f.lfWeight = 1000;
    wcscpy_s(f.lfFaceName, _T("宋体"));
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    settextstyle(&f);						// 设置字体样式
    settextcolor(set_button_word_orange);//设置字体颜色
    setbkmode(TRANSPARENT);				//设置背景为无填充
    drawtext(b, &o, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    DrawRank(0);
    //绘制初始骰子
    putimage(470, 290, &dice_1[0]);
    putimage(530, 290, &dice_1[0]);
    putimage(590, 290, &dice_1[0]);
    putimage(470, 350, &dice_1[0]);
    putimage(530, 350, &dice_1[0]);
    putimage(590, 350, &dice_1[0]);
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
    PrintPage4();
    DrawRank(0);
    for (int i = 0; i < count; i++) {
        a[i] = CreatePoint(a[i]);
        a[i] = Judge(a[i]);
        Page4Button();
        DrawDice(i);

        for (int j = i; j > 0; j--) {//排名
            if (a[j].count[0] > a[j - 1].count[0]) {
                swap(a[j], a[j - 1]);
            }
        }
        DrawRank(i+1);
    }
}



int main() {
    srand((unsigned)time(NULL));
    for (int i = 0; i < 10; i++) {
        memset(&players[i], 0, sizeof(player));
    }
    
    initgraph(800, 500);//游戏窗口大小定义，初始化图像环境
    HWND hWnd = GetHWnd(); // 获得窗口句柄
    SetWindowText(hWnd, TEXT("中秋博饼"));
    InputDice();
    setbkcolor(RGB(182, 46, 63));
    cleardevice();
    PrintTitle();
    PrintPoem();
    DrawRect_1();
    cleardevice();
    PrintPage2();
    PrintPage3();
    GameRunning(players, player_count);
    getchar();
    return 0;
}
