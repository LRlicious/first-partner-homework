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
    int point[6];   //�������ӽ��
    int count[7];   //1-6����1-6�ļ�����0�����Զ�����������
    string rank;
} players[100];
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
//��ʫ�ʸ�ʽ����
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
//�����������
player CinPlayer() {
    struct player a;
    memset(&a, 0, sizeof(a));
    //cin >> a.name;
    return a;
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
    for (int i = 0; i < count; i++) {
        a[i] = CreatePoint(a[i]);
        a[i] = Judge(a[i]);
        /*����*/
        printf("��%d��\n", i);
        for (int j = 0; j < 6; j++) {
            cout << " " << a[i].point[j]<<" ";
        }
        cout << a[i].rank<<a[i].count[0] << endl;
        
        /*����*/
        for (int j = i; j > 0; j--) {//����
            if (a[j].count[0] > a[j - 1].count[0]) {
                swap(a[j], a[j - 1]);
            }
        }
    }
}



int main() {
    srand((unsigned)time(NULL));
    /*
    initgraph(800, 500);//��Ϸ���ڴ�С���壬��ʼ��ͼ�񻷾�
    HWND hWnd = GetHWnd(); // ��ô��ھ��
    SetWindowText(hWnd, TEXT("���ﲩ��"));
    setbkcolor(RGB(182, 46, 63));
    cleardevice();
    PrintTitle();
    PrintPoem();
    DrawRect_1();
    cleardevice();
    getchar();
    */
    
    /*��ע�͵���������*/
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
