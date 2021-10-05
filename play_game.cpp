#include<iostream>
#include<string>
#include<stdlib.h>
#include <time.h> 
using namespace std;
struct player {
    string name;
    int point[6];   //�������ӽ��
    int count[7];   //1-6����1-6�ļ�����0�����Զ�����������
    string rank;
}players[10];//���֧��10����ң��ٴ������ƵĽ��治�����ˣ�
//�����������
void CinPlayer(struct player a) {
    memset(&a, 0, sizeof(a));
    //cin >> a.name;
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
        cout << a[i].rank << endl;
        /*����*/
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