#pragma once
#include <time.h>
#include "GameMap.h"
namespace game_framework {
class CGameMap2
{
    public:
        CGameMap2();
        void LoadBitmap();
        void OnMove();
        void OnShow();
        void gotoxy(int x, int y);
        int map[23][10];
        bool check = true;
        bool precheck = false;
        bool switchz = true;
        bool GameOverCheck = false;
        int block0[4][4] = { { 0, 3, 3, 0 }, { 0, 0, 3, 0 }, { 0, 0, 3, 0 }, { 0, 0, 0, 0 } }; // 7 個方塊 用數組表示 正「7」
        int block1[4][4] = { { 0, 4, 4, 0 }, { 0, 4, 0, 0 }, { 0, 4, 0, 0 }, { 0, 0, 0, 0 } }; // 反「7」
        int block2[4][4] = { { 0, 0, 0, 0 }, { 0, 0, 5, 5 }, { 0, 5, 5, 0 }, { 0, 0, 0, 0 } }; // 反「z」
        int block3[4][4] = { { 0, 0, 0, 0 }, { 6, 6, 0, 0 }, { 0, 6, 6, 0 }, { 0, 0, 0, 0 } }; // 正「z」
        int block4[4][4] = { { 0, 0, 0, 0 }, { 0, 7, 0, 0 }, { 7, 7, 7, 0 }, { 0, 0, 0, 0 } }; // 倒「T」
        int block5[4][4] = { { 0, 0, 0, 0 }, { 0, 8, 8, 0 }, { 0, 8, 8, 0 }, { 0, 0, 0, 0 } }; // 正方形
        int block6[4][4] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 9, 9, 9, 9 }, { 0, 0, 0, 0 } }; // 直條
        int BLOCK[4][4];//正在下落的方塊
        int block[4][4];//提示區的方塊
        int preblock[4][4] { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }; //預知看到的方塊
        int holdBlock[4][4] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }; //先留住的方塊
        int tem[4][4];
        int randomm[7] = { 0, 0, 0, 0, 0, 0, 0 };
        int ri = 0;
        int point = 0;
        int start = 0;
        void OnKeyDown(UINT nChar);
        void OnKeyUp(UINT nChar);
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
        void SetMovingDown(bool flag);	// 設定是否正在往下移動
        void SetMovingLeft(bool flag);	// 設定是否正在往左移動
        void SetMovingRight(bool flag); // 設定是否正在往右移動
        void SetMovingUp(bool flag);	// 設定是否正在往上移動
    protected:
        CMovingBitmap gray1, gray2, blue, green, lightblue, orange, purple, red, yellow, black;
        time_t t;
        const int X, Y;
        const int MW, MH;
        bool isMovingDown;			// 是否正在往下移動
        bool isMovingLeft;			// 是否正在往左移動
        bool isMovingRight;			// 是否正在往右移動
        bool isMovingUp;			// 是否正在往上移動
};

class ShowNext2
{
    public:
        ShowNext2();
        int map[4][4];
        void LoadBitmap();
        void OnShow();
        void OnMove(CGameMap2& gamemap2);
    protected:
        CMovingBitmap back, blue, green, lightblue, orange, purple, red, yellow;
        const int X, Y;
        const int MW, MH;
    private:
};

class Score2
{
    public:
        Score2();
        int map[1][6];
        void LoadBitmap();
        void OnShow();
        void OnMove(CGameMap2& gamemap2);
        int score = 0;
    protected:
        CMovingBitmap zero, one, two, three, four, five, six, seven, eight, nine;
        const int X, Y;
        const int MW, MH;

};
class Hold2
{
    public:
        Hold2();
        int map[4][4];
        void LoadBitmap();
        void OnShow();
        void OnMove(CGameMap2& gamemap2);
    private:
        CMovingBitmap back, blue, green, lightblue, orange, purple, red, yellow;
        const int X, Y;
        const int MW, MH;
};

}