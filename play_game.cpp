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
int player_count;   //������� ��������ƫСֻ����ʾ��8
IMAGE dice_1[6], dice_2[6];     //����ͼƬ
struct player {
    string name;
    int point[6];   //�������ӽ��
    int count[7];   //1-6����1-6�ļ�����0�����Զ�����������
    string rank;
} players[10];

//����ͼƬ����
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

/*�����ҵ�wchar_tתstring*/
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

/*�����ҵ�stringתwchar_t*/
wchar_t* stringToWchar_t(string str) {
    string temp = str;
    int len = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)temp.c_str(), -1, NULL, 0);
    wchar_t* wszUtf8 = new wchar_t[len + 1];
    memset(wszUtf8, 0, len * 2 + 2);
    MultiByteToWideChar(CP_ACP, 0, (LPCSTR)temp.c_str(), -1, (LPWSTR)wszUtf8, len);
    return wszUtf8;
}
//��ʼ�����������
void PrintTitle() {
    TCHAR s[] = _T("��  ��  ��  ��");
    LOGFONT f;
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = 110;						// ��������߶�Ϊ 110
    wcscpy_s(f.lfFaceName, _T("���ⳬ�ֺ�_CNKI"));		// ��������Ϊ�����ⳬ�ֺ�_CNKI��
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    settextstyle(&f);						// ����������ʽ
    settextcolor(set_title_yellow);//����������ɫ
    outtextxy(125, 50, s);
}

//��ʫ�ʸ�ʽ�������
void PrintPoem() {
    TCHAR a[] = _T("��Ը�˳���");
    TCHAR b[] = _T("ǧ�ﹲ濾�");
    LOGFONT f;
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = 25;						// ��������߶�Ϊ 25
    wcscpy_s(f.lfFaceName, _T("�����п�_CNKI"));		// ��������Ϊ�������п�_CNKI��
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    settextstyle(&f);						// ����������ʽ
    settextcolor(RGB(245, 154, 35));//����������ɫ
    outtextxy(10, 390, a);
    outtextxy(50, 430, b);
}

//��ʼ��ť���ƺͷ���
void DrawRect_1() {
    RECT r = { 320, 310, 480, 375 };
    int r1[4] = { 320, 310, 480, 375 };
    setfillcolor(set_button_yellow);
    solidrectangle(320, 310, 480, 375);
    TCHAR a[] = _T("��ʼ��Ϸ");
    LOGFONT f;
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = 35;						// ��������߶�Ϊ 25
    f.lfWeight = 1000;						//���������ϸ
    wcscpy_s(f.lfFaceName, _T("����"));		// ��������Ϊ�������п�_CNKI��
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    settextstyle(&f);						// ����������ʽ
    settextcolor(set_button_word_orange);//����������ɫ
    setbkmode(TRANSPARENT);				//���ñ���Ϊ�����
    drawtext(a, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    ExMessage m;//���ָ��
    int flag = 1;
    while (flag) {
        m = getmessage(EM_MOUSE);//��ȡһ�������Ϣ
        if (m.x > r1[0] && m.x<r1[2] && m.y>r1[1] && m.y < r1[3] && m.message == WM_LBUTTONDOWN) {
            //�������Ƿ�������
            flag = 0;
        }
    }
}

//����2����������
void PrintPage2() {
    TCHAR s[] = _T("���������������������8��");
    LOGFONT f;
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = 45;						// ��������߶�Ϊ 45
    wcscpy_s(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    settextstyle(&f);						// ����������ʽ
    settextcolor(set_title_yellow);//����������ɫ
    outtextxy(100, 100, s);

    RECT r = { 320, 310, 480, 375 };
    int r1[4] = { 320, 310, 480, 375 };
    setfillcolor(set_button_yellow);
    solidrectangle(320, 310, 480, 375);
    TCHAR a[] = _T("��������");
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = 35;						// ��������߶�Ϊ 35
    f.lfWeight = 1000;						//���������ϸ
    wcscpy_s(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    settextstyle(&f);						// ����������ʽ
    settextcolor(set_button_word_orange);//����������ɫ
    setbkmode(TRANSPARENT);				//���ñ���Ϊ�����
    drawtext(a, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    ExMessage m;//���ָ��
    int flag = 1;
    while (flag) {
        m = getmessage(EM_MOUSE);//��ȡһ�������Ϣ
        if (m.x > r1[0] && m.x<r1[2] && m.y>r1[1] && m.y < r1[3] && m.message == WM_LBUTTONDOWN)
            flag = 0;
    }
    wchar_t x[10];
    InputBox(x, 10, L"����������");		//�������
    player_count = _wtoi(x);
    cleardevice();  //����
}

//����3�������������
void PrintPage3() {
    TCHAR s[] = _T("�������������");
    LOGFONT f;
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = 45;						// ��������߶�Ϊ 45
    wcscpy_s(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    settextstyle(&f);						// ����������ʽ
    settextcolor(set_title_yellow);//����������ɫ
    outtextxy(230, 100, s);

    RECT r = { 320, 310, 480, 375 };
    int r1[4] = { 320, 310, 480, 375 };
    setfillcolor(set_button_yellow);
    solidrectangle(320, 310, 480, 375);
    TCHAR a[] = _T("��������");
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = 35;						// ��������߶�Ϊ 35
    f.lfWeight = 1000;						//���������ϸ
    wcscpy_s(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    settextstyle(&f);						// ����������ʽ
    settextcolor(set_button_word_orange);//����������ɫ
    setbkmode(TRANSPARENT);				//���ñ���Ϊ�����
    drawtext(a, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    ExMessage m;//���ָ��
    int flag = 1;
    while (flag) {
        //��ť�ж�
        m = getmessage(EM_MOUSE);//��ȡһ�������Ϣ
        if (m.x > r1[0] && m.x<r1[2] && m.y>r1[1] && m.y < r1[3] && m.message == WM_LBUTTONDOWN)
            flag = 0;
    }
    for (int i = 0; i < player_count; i++) {
        wchar_t x[30];
        InputBox(x, 30, L"����������");		//�������
        players[i].name = wchar_tToString(x);
    }
    cleardevice();  //����
}

//����4���ܣ������Ӱ�ť�ж�
void Page4Button() {
    int flag = 1;
    int r1[4] = { 470, 185, 635, 250 };
    ExMessage m;//���ָ��
    while (flag) {
        m = getmessage(EM_MOUSE);//��ȡһ�������Ϣ
        if (m.x > r1[0] && m.x<r1[2] && m.y>r1[1] && m.y < r1[3] && m.message == WM_LBUTTONDOWN)
            flag = 0;
    }
    flushmessage;
}

//����4����������
void DrawRank(int times) {
    LOGFONT f;
    //������
    setfillcolor(RGB(255, 255, 128));
    solidrectangle(0, 0, 280, 500);
    //������
    TCHAR a[] = _T("��    ��");
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = 40;
    f.lfWeight = 1000;						//���������ϸ
    wcscpy_s(f.lfFaceName, _T("����"));
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    settextstyle(&f);						// ����������ʽ
    settextcolor(RGB(217, 0, 27));//����������ɫ
    setbkmode(TRANSPARENT);				//���ñ���Ϊ�����
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

//����4�������������Ӷ����ͽ��
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

//����4 �����ұ߽���
void PrintPage4() {
    TCHAR a[] = _T("�� �� �� ��");
    LOGFONT f;
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = 76;						// ��������߶�Ϊ 76
    wcscpy_s(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    settextstyle(&f);						// ����������ʽ
    settextcolor(set_title_yellow);//����������ɫ
    outtextxy(340, 15, a);
    //��Բ
    setfillcolor(WHITE);
    fillcircle(550, 300, 190);
    //����ť
    setfillcolor(set_button_yellow);
    solidrectangle(470, 185, 635, 250);
    RECT o = { 470, 185, 635, 250 };
    TCHAR b[] = _T("��ʼ��Ϸ");
    gettextstyle(&f);
    f.lfHeight = 35;
    f.lfWeight = 1000;
    wcscpy_s(f.lfFaceName, _T("����"));
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    settextstyle(&f);						// ����������ʽ
    settextcolor(set_button_word_orange);//����������ɫ
    setbkmode(TRANSPARENT);				//���ñ���Ϊ�����
    drawtext(b, &o, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    DrawRank(0);
    //���Ƴ�ʼ����
    putimage(470, 290, &dice_1[0]);
    putimage(530, 290, &dice_1[0]);
    putimage(590, 290, &dice_1[0]);
    putimage(470, 350, &dice_1[0]);
    putimage(530, 350, &dice_1[0]);
    putimage(590, 350, &dice_1[0]);
}

//��������
player CreatePoint(struct player a) {
    for (int i = 0; i < 6; i++) {
        a.point[i] = rand() % 6+1;
        a.count[a.point[i]] += 1;
    }
    return a;
}

//����ж�
player Judge(struct player a) {
    if (a.count[4] == 4 && a.count[1] == 2) {
        a.count[0] = 130;
        a.rank = "���";
    }
    else if (a.count[4] == 6) {
        a.count[0] = 120;
        a.rank = "���ú�";
    }
    else if (a.count[1] == 6) {
        a.count[0] = 110;
        a.rank = "��ؽ�";
    }
    else if (a.count[6] == 6) {
        a.count[0] = 103;
        a.rank = "������";
    }
    else if (a.count[5] == 6) {
        a.count[0] = 102;
        a.rank = "������";
    }
    else if (a.count[3] == 6) {
        a.count[0] = 101;
        a.rank = "������";
    }
    else if (a.count[2] == 6) {
        a.count[0] = 100;
        a.rank = "������";
    }
    else if (a.count[4] == 5) {
        a.count[0] = 90 + a.count[1] * 1 + a.count[2] * 2 + a.count[3] * 3 + a.count[5] * 5 + a.count[6] * 6;
        a.rank = "���";
    }
    else if (a.count[6] == 5) {
        a.count[0] = 80 + a.count[1] * 1 + a.count[2] * 2 + a.count[3] * 3 + a.count[4] * 4 + a.count[5] * 5;
        a.rank = "���ӵǿ�";
    }
    else if (a.count[5] == 5) {
        a.count[0] = 80 + a.count[1] * 1 + a.count[2] * 2 + a.count[3] * 3 + a.count[4] * 4 + a.count[6] * 6;
        a.rank = "���ӵǿ�";
    }
    else if (a.count[3] == 5) {
        a.count[0] = 80 + a.count[1] * 1 + a.count[2] * 2 + a.count[6] * 6 + a.count[4] * 4 + a.count[5] * 5;
        a.rank = "���ӵǿ�";
    }
    else if (a.count[2] == 5) {
        a.count[0] = 80 + a.count[1] * 1 + a.count[6] * 6 + a.count[3] * 3 + a.count[4] * 4 + a.count[5] * 5;
        a.rank = "���ӵǿ�";
    }
    else if (a.count[1] == 5) {
        a.count[0] = 80 + a.count[6] * 6 + a.count[2] * 2 + a.count[3] * 3 + a.count[4] * 4 + a.count[5] * 5;
        a.rank = "���ӵǿ�";
    }
    else if (a.count[4] == 4) {
        a.count[0] = 60 + a.count[1] * 1 + a.count[2] * 2 + a.count[3] * 3 + a.count[5] * 5 + a.count[6] * 6;
        a.rank = "״Ԫ";
    }
    else if (a.count[1] == 1 && a.count[2] == 1 && a.count[3] == 1 && a.count[4] == 1 && a.count[5] == 1 && a.count[6] == 1) {
        a.count[0] = 50;
        a.rank = "����";
    }
    else if (a.count[4] == 3) {
        a.count[0] = 40;
        a.rank = "̽��";
    }
    else if (a.count[2] == 4) {
        a.count[0] = 30;
        a.rank = "��ʿ";
    }
    else if (a.count[4] == 2) {
        a.count[0] = 20;
        a.rank = "����";
    }
    else if (a.count[4] == 1) {
        a.count[0] = 10;
        a.rank = "���";
    }
    else {
        a.count[0] = 0;
        a.rank = "��";
    }
    return a;
}

//��Ϸ����
void GameRunning(struct player a[10], int count) {
    PrintPage4();
    DrawRank(0);
    for (int i = 0; i < count; i++) {
        a[i] = CreatePoint(a[i]);
        a[i] = Judge(a[i]);
        Page4Button();
        DrawDice(i);

        for (int j = i; j > 0; j--) {//����
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
    
    initgraph(800, 500);//��Ϸ���ڴ�С���壬��ʼ��ͼ�񻷾�
    HWND hWnd = GetHWnd(); // ��ô��ھ��
    SetWindowText(hWnd, TEXT("���ﲩ��"));
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
