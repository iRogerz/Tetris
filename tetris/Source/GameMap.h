#pragma once
#include <time.h>
#include "GameMap2.h"
namespace game_framework {
class CGameMap
{
    public:
        CGameMap();
        void LoadBitmap();
        void OnMove();
        void OnShow();
        void gotoxy(int x, int y);
        int map[23][10];
        bool check = true;
        bool precheck = false;
        bool switchz = true;
        bool GameOverCheck = false;
        int block0[4][4] = { { 0, 3, 3, 0 }, { 0, 0, 3, 0 }, { 0, 0, 3, 0 }, { 0, 0, 0, 0 } }; // 7 �Ӥ�� �μƲժ�� ���u7�v
        int block1[4][4] = { { 0, 4, 4, 0 }, { 0, 4, 0, 0 }, { 0, 4, 0, 0 }, { 0, 0, 0, 0 } }; // �ϡu7�v
        int block2[4][4] = { { 0, 0, 0, 0 }, { 0, 0, 5, 5 }, { 0, 5, 5, 0 }, { 0, 0, 0, 0 } }; // �ϡuz�v
        int block3[4][4] = { { 0, 0, 0, 0 }, { 6, 6, 0, 0 }, { 0, 6, 6, 0 }, { 0, 0, 0, 0 } }; // ���uz�v
        int block4[4][4] = { { 0, 0, 0, 0 }, { 0, 7, 0, 0 }, { 7, 7, 7, 0 }, { 0, 0, 0, 0 } }; // �ˡuT�v
        int block5[4][4] = { { 0, 0, 0, 0 }, { 0, 8, 8, 0 }, { 0, 8, 8, 0 }, { 0, 0, 0, 0 } }; // �����
        int block6[4][4] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 9, 9, 9, 9 }, { 0, 0, 0, 0 } }; // ����
        int BLOCK[4][4];//���b�U�������
        int block[4][4];//���ܰϪ����
        int preblock[4][4] { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }; //�w���ݨ쪺���
        int holdBlock[4][4] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }; //���d�����
        int tem[4][4];
        int randomm[7] = { 0, 0, 0, 0, 0, 0, 0 };
        int ri = 0;
        int point = 0;
        int start = 0;
        void OnKeyDown(UINT);
        void OnKeyUp(UINT);
        void BlockDown();
        void BlockLeft();
        void BlockRight();
        void BlockSpin();
        void BlockSwitch();
        void random();
        void clear();
        int combo = 0;
        void Preview();
        int x = 0, y = 3, x1 = 0, y1 = 0, blockSleep = 0;
        void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
        void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
        void SetMovingRight(bool flag); // �]�w�O�_���b���k����
        void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
    protected:
        CMovingBitmap gray1, gray2, blue, green, lightblue, orange, purple, red, yellow, black;
        time_t t;
        const int X, Y;
        const int MW, MH;
        bool isMovingDown;			// �O�_���b���U����
        bool isMovingLeft;			// �O�_���b��������
        bool isMovingRight;			// �O�_���b���k����
        bool isMovingUp;			// �O�_���b���W����
    private:
        //void setTimeout(auto function, int delay);
};

class ShowNext
{
    public:
        ShowNext();
        int map[4][4];
        void LoadBitmap();
        void OnShow();
        void OnMove(CGameMap& g);
    protected:
        CMovingBitmap back, blue, green, lightblue, orange, purple, red, yellow;
        const int X, Y;
        const int MW, MH;
    private:
};

class Score
{
    public:
        Score();
        int map[1][6];
        void LoadBitmap();
        void OnShow();
        void OnMove(CGameMap& gamemap);
        int score = 0;
    protected:
        CMovingBitmap zero, one, two, three, four, five, six, seven, eight, nine;
        const int X, Y;
        const int MW, MH;

};
class Hold
{
    public:
        Hold();
        int map[4][4];
        void LoadBitmap();
        void OnShow();
        void OnMove(CGameMap& gamemap);
    private:
        CMovingBitmap back, blue, green, lightblue, orange, purple, red, yellow;
        const int X, Y;
        const int MW, MH;
};
}