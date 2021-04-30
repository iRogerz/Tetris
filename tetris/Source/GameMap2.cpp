#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameMap2.h"
#include <time.h>
namespace game_framework {
CGameMap2::CGameMap2()
    : X(544), Y(38), MW(30), MH(30)
{
    int map_init[23][10] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };

    for (int i = 0; i < 23; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            map[i][j] = map_init[i][j];
        }
    }

    isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
}
void CGameMap2::LoadBitmap()
{
    black.LoadBitmap(IDB_cube_black);
    gray1.LoadBitmap(IDB_GRAY1);
    gray2.LoadBitmap(IDB_gray2, RGB(255, 255, 255));
    blue.LoadBitmap(IDB_BLOCKBLUE);
    green.LoadBitmap(IDB_BLOCKGREEN);
    lightblue.LoadBitmap(IDB_BLOCKLIGHTBLUE);
    orange.LoadBitmap(IDB_BLOCKORANGE);
    purple.LoadBitmap(IDB_BLOCKPURPLE);
    red.LoadBitmap(IDB_BLOCKRED);
    yellow.LoadBitmap(IDB_BLOCKYELLOW);
}
void CGameMap2::OnMove()
{
    if (GameOverCheck == false)
    {
        if (check)
        {
            if (start == 0)
            {
                random();
            }

            srand((unsigned)time(&t));
            int i, j;

            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    BLOCK[i][j] = block[i][j];//將提示區的方塊數組傳到下落的方塊數組
                }
            }

            random();
            x = 0;   //陣列位置X軸
            y = 3;   //陣列位置Y軸
            start++;
            check = false;
            precheck = false;

            for (int i = 0; i < 23; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    if (map[i][j] == 1)
                    {
                        map[i][j] = 0;
                    }
                }
            }
        }

        if (isMovingLeft)
        {
            if (true == check)
            {
                return;
            }

            if (blockSleep == 0)
            {
                BlockLeft();
            }

            if (blockSleep > 6)
            {
                BlockLeft();
            }

            blockSleep++;
        }

        if (isMovingDown)
        {
            if (true == check)
            {
                return;//不能下落直接不執行
            }

            if (blockSleep == 0)
            {
                BlockDown();
            }

            if (blockSleep > 6)
            {
                BlockDown();
            }

            blockSleep++;
        }

        /*if (isMovingUp)
        {

        BlockSpin();
        Sleep(100);
        }*/
        if (isMovingRight)
        {
            if (true == check)
            {
                return;//不能下落直接不執行
            }

            if (blockSleep == 0)
            {
                BlockRight();
            }

            if (blockSleep > 6)
            {
                BlockRight();
            }

            blockSleep++;
            //delay(300);
        }

        if (0 == ++t % 20)
        {
            BlockDown();
        }
    }

    //BlockDown();
}
void CGameMap2::OnShow()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            switch (map[j][i])
            {
                case 0:
                    black.SetTopLeft(X + (MW * i), Y + (MH * j));
                    black.ShowBitmap();
                    break;

                case 1:
                    gray2.SetTopLeft(X + (MW * i), Y + (MH * j));
                    gray2.ShowBitmap();
                    break;

                case 2:
                    gray1.SetTopLeft(X + (MW * i), Y + (MH * j));
                    gray1.ShowBitmap();
                    break;

                case 3:
                    blue.SetTopLeft(X + (MW * i), Y + (MH * j));
                    blue.ShowBitmap();
                    break;

                case 4:
                    green.SetTopLeft(X + (MW * i), Y + (MH * j));
                    green.ShowBitmap();
                    break;

                case 5:
                    lightblue.SetTopLeft(X + (MW * i), Y + (MH * j));
                    lightblue.ShowBitmap();
                    break;

                case 6:
                    orange.SetTopLeft(X + (MW * i), Y + (MH * j));
                    orange.ShowBitmap();
                    break;

                case 7:
                    purple.SetTopLeft(X + (MW * i), Y + (MH * j));
                    purple.ShowBitmap();
                    break;

                case 8:
                    red.SetTopLeft(X + (MW * i), Y + (MH * j));
                    red.ShowBitmap();
                    break;

                case 9:
                    yellow.SetTopLeft(X + (MW * i), Y + (MH * j));
                    yellow.ShowBitmap();
                    break;

                default:
                    ASSERT(0);
            }
        }
    }
}
void CGameMap2::gotoxy(int x, int y)
{
    this->x = x;
    this->y = y;
}
void CGameMap2::BlockDown() {
    int i, j;
    gotoxy(x, y);

    for (i = 3; i >= 0; i--)//檢測該方格還能不能下落
    {
        for (j = 0; j <= 3; j++)
        {
            if (BLOCK[i][j] != 0)
            {
                if (x + j > 21)
                {
                    if ((map[x + j + 1][y + i] == 1 && j == 3) || (j < 3 && map[x + j + 1][y + i] == 1 && BLOCK[i][j + 1] == 0))
                    {
                        break;
                    }
                    else
                    {
                        clear();
                        check = true;
                        switchz = true;
                        return;
                    }
                }
                else if ((map[x + j + 1][y + i] != 0 && j == 3) || (j < 3 && map[x + j + 1][y + i] != 0 && BLOCK[i][j + 1] == 0))
                {
                    if ((map[x + j + 1][y + i] == 1 && j == 3) || (j < 3 && map[x + j + 1][y + i] == 1 && BLOCK[i][j + 1] == 0))
                    {
                        break;
                    }
                    else
                    {
                        clear();
                        check = true;
                        switchz = true;
                        return;
                    }
                }
            }
        }
    }

    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            if (BLOCK[i][j] != 0)
            {
                map[x + j][y + i] = 0;
                //能下落，擦除以前的方格
            }

    x++;

    for (i = 0; i < 4; i++)  //方塊塗進map
    {
        for (j = 0; j < 4; j++)
        {
            if (BLOCK[i][j] != 0)
            {
                map[x + j][y + i] = BLOCK[i][j];
            }
        }
    }

    x1 = x + 1;
    y1 = y;

    while (precheck == false)
    {
        Preview();
    }
}
void CGameMap2::BlockLeft()
{
    int i, j;
    gotoxy(x, y);

    for (i = 0; i < 4; i++)//檢測該方格還能不能下落
    {
        for (j = 0; j < 4; j++)
        {
            if (BLOCK[i][j] != 0)
            {
                if (y + i < 1)
                {
                    return;
                }
                else if ((map[x + j][y + i - 1] != 0 && i == 0) || (i > 0 && map[x + j][y + i - 1] != 0 && BLOCK[i - 1][j] == 0))
                {
                    return;
                }
            }
        }
    }

    for (int i = 0; i < 23; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (map[i][j] == 1)
            {
                map[i][j] = 0;
            }
        }
    }

    precheck = false;

    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            if (BLOCK[i][j] != 0)
            {
                map[x + j][y + i] = 0;
                //能下落，擦除以前的方格
            }

    y -= 1;

    for (i = 0; i < 4; i++)  //方塊塗進map
    {
        for (j = 0; j < 4; j++)
        {
            if (BLOCK[i][j] != 0)
            {
                map[x + j][y + i] = BLOCK[i][j];
            }
        }
    }

    x1 = x;
    y1 = y;

    while (precheck == false)
    {
        Preview();
    }
}
void CGameMap2::BlockRight()
{
    int i, j;
    gotoxy(x, y);

    for (i = 3; i > 0; i--)//檢測該方格還能不能下落
    {
        for (j = 0; j < 4; j++)
        {
            if (BLOCK[i][j] != 0)
            {
                if (y + i > 8)
                {
                    return;
                }
                else if ((map[x + j][y + i + 1] != 0 && i == 3) || (i < 3 && map[x + j][y + i + 1] != 0 && BLOCK[i + 1][j] == 0))
                {
                    return;
                }
            }
        }
    }

    for (int i = 0; i < 23; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (map[i][j] == 1)
            {
                map[i][j] = 0;
            }
        }
    }

    precheck = false;

    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            if (BLOCK[i][j] != 0)
            {
                map[x + j][y + i] = 0;
                //能下落，擦除以前的方格
            }

    y += 1;

    for (i = 0; i < 4; i++)  //方塊塗進map
    {
        for (j = 0; j < 4; j++)
        {
            if (BLOCK[i][j] != 0)
            {
                map[x + j][y + i] = BLOCK[i][j];
            }
        }
    }

    x1 = x;
    y1 = y;

    while (precheck == false)
    {
        Preview();
    }
}
void CGameMap2::BlockSpin()
{
    int i, j;
    gotoxy(x, y);

    for (int i = 0; i < 23; i++)  //把預覽落下刪掉
    {
        for (int j = 0; j < 10; j++)
        {
            if (map[i][j] == 1)
            {
                map[i][j] = 0;
            }
        }
    }

    precheck = false;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            tem[i][j] = BLOCK[i][j];
        }
    }

    for (i = 0; i < 4; i++)//順時針轉
    {
        for (j = 0; j < 4; j++)
        {
            BLOCK[3 - j][i] = tem[i][j];
        }
    }

    //以上為旋轉。
    //下面為防止旋轉後超出框架範圍
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            if (tem[i][j] != 0)
            {
                map[x + j][y + i] = 0;
                //能旋轉，擦除以前的方格
            }

    for (j = 0; j < 2; j++)
    {
        for (i = 0; i < 4; i++)
        {
            if (BLOCK[i][j] != 0 && y < 0)
            {
                y += 1;
            }
            else if (BLOCK[i][3 - j] != 0 && y > 6)
            {
                y -= 1;
            }
        }
    }

    for (i = 0; i < 4; i++)  //方塊塗進map
    {
        for (j = 0; j < 4; j++)
        {
            if (BLOCK[i][j] != 0)
            {
                map[x + j][y + i] = BLOCK[i][j];
            }
        }
    }

    x1 = x;
    y1 = y;

    while (precheck == false)
    {
        Preview();
    }
}
void CGameMap2::BlockSwitch()
{
    gotoxy(x, y);

    if (switchz)
    {
        for (int i = 0; i < 23; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (map[i][j] == 1)
                {
                    map[i][j] = 0;
                }
            }
        }

        precheck = false;
        int count = 0;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (holdBlock[i][j] != 0)
                {
                    count++;
                }
            }
        }

        if (count == 0)
        {
            int i, j;

            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    holdBlock[i][j] = BLOCK[i][j];
                }
            }

            for (i = 0; i < 4; i++)
                for (j = 0; j < 4; j++)
                    if (BLOCK[i][j] != 0)
                    {
                        map[x + j][y + i] = 0;
                        //能下落，擦除以前的方格
                    }

            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    BLOCK[i][j] = block[i][j];//將提示區的方塊數組傳到下落的方塊數組
                }
            }

            for (i = 0; i < 4; i++)  //方塊塗進map
            {
                for (j = 0; j < 4; j++)
                {
                    if (BLOCK[i][j] != 0)
                    {
                        map[x + j][y + i] = BLOCK[i][j];
                    }
                }
            }

            random();
            switchz = false;
        }
        else
        {
            int tempBlock[4][4], i, j;

            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    tempBlock[i][j] = BLOCK[i][j];
                    //方塊存進暫存區
                }
            }

            for (i = 0; i < 4; i++)
                for (j = 0; j < 4; j++)
                    if (BLOCK[i][j] != 0)
                    {
                        map[x + j][y + i] = 0;
                        //能下落，擦除以前的方格
                    }

            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    BLOCK[i][j] = holdBlock[i][j];
                }
            }

            for (i = 0; i < 4; i++)  //方塊塗進map
            {
                for (j = 0; j < 4; j++)
                {
                    if (BLOCK[i][j] != 0)
                    {
                        map[x + j][y + i] = BLOCK[i][j];
                    }
                }
            }

            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    holdBlock[i][j] = tempBlock[i][j];
                }
            }

            switchz = false;
        }

        x1 = x;
        y1 = y;

        while (precheck == false)
        {
            Preview();
        }
    }
}
void CGameMap2::Preview()
{
    if (true == precheck)
    {
        return;//不能下落直接不執行
    }

    int i, j, k, l;

    for (i = 3; i >= 0; i--)//檢測該方格還能不能下落
    {
        for (j = 0; j <= 3; j++)
        {
            if (BLOCK[i][j] != 0)
            {
                if (x1 + j > 21)
                {
                    for (k = 0; k < 4; k++)  //方塊塗進map
                    {
                        for (l = 0; l < 4; l++)
                        {
                            if (BLOCK[k][l] != 0)
                            {
                                if (map[x1 + l][y1 + k] == 0)
                                {
                                    map[x1 + l][y1 + k] = 1;
                                }
                            }
                        }
                    }

                    precheck = true;
                    return;
                }
                else if ((map[x1 + j + 1][y1 + i] != 0 && j == 3) || (j < 3 && map[x1 + j + 1][y1 + i] != 0 && BLOCK[i][j + 1] == 0))
                {
                    for (k = 0; k < 4; k++)  //方塊塗進map
                    {
                        for (l = 0; l < 4; l++)
                        {
                            if (BLOCK[k][l] != 0)
                            {
                                if (map[x1 + l][y1 + k] == 0)
                                {
                                    map[x1 + l][y1 + k] = 1;
                                }
                            }
                        }
                    }

                    precheck = true;
                    return;
                }
            }
        }
    }

    x1++;
}
void CGameMap2::SetMovingDown(bool flag)
{
    isMovingDown = flag;
}
void CGameMap2::SetMovingLeft(bool flag)
{
    isMovingLeft = flag;
}
void CGameMap2::SetMovingRight(bool flag)
{
    isMovingRight = flag;
}
void CGameMap2::SetMovingUp(bool flag)
{
    isMovingUp = flag;
}
void CGameMap2::OnKeyDown(UINT nChar)
{
    const char LEFT2 = 0x61; // keyboard左箭頭
    const char UP2 = 0x65; // keyboard上箭頭
    const char RIGHT2 = 0x63; // keyboard右箭頭
    const char DOWN2 = 0x62; // keyboard下箭頭
    const char P = 0x50;
    const char O = 0x4F;

    if (nChar == O)
    {
        BlockSwitch();
    }

    if (nChar == P)
    {
        while (check == false)
        {
            BlockDown();
        }
    }

    if (nChar == LEFT2)
    {
        SetMovingLeft(true);
    }

    if (nChar == RIGHT2)
    {
        SetMovingRight(true);
    }

    if (nChar == UP2)
    {
        BlockSpin();
    }

    if (nChar == DOWN2)
    {
        SetMovingDown(true);
    }
}

void CGameMap2::OnKeyUp(UINT nChar)
{
    const char LEFT2 = 0x61; // keyboard左箭頭
    const char UP2 = 0x65; // keyboard上箭頭
    const char RIGHT2 = 0x63; // keyboard右箭頭
    const char DOWN2 = 0x62; // keyboard下箭頭

    if (nChar == LEFT2)
    {
        blockSleep = 0;
        SetMovingLeft(false);
    }

    if (nChar == RIGHT2)
    {
        blockSleep = 0;
        SetMovingRight(false);
    }

    if (nChar == UP2)
    {
        blockSleep = 0;
        SetMovingUp(false);
    }

    if (nChar == DOWN2)
    {
        blockSleep = 0;
        SetMovingDown(false);
    }
}

void CGameMap2::random()
{
    int i, j;

    if (randomm[0] == 0)
    {
        for (int i = 0; i < 7; i++)
        {
            randomm[i] = i + 1;
        }

        for (int i = 0; i < 7; i++)
        {
            int j = rand() % 7;
            int t = randomm[i];
            randomm[i] = randomm[j];
            randomm[j] = t;
        }
    }

    switch (randomm[ri])
    {
        case 7:
            for (i = 0; i < 4; i++)
                for (j = 0; j < 4; j++)
                    block[i][j] = block0[i][j];

            break;

        case 1:
            for (i = 0; i < 4; i++)
                for (j = 0; j < 4; j++)
                    block[i][j] = block1[i][j];

            break;

        case 2:
            for (i = 0; i < 4; i++)
                for (j = 0; j < 4; j++)
                    block[i][j] = block2[i][j];

            break;

        case 3:
            for (i = 0; i < 4; i++)
                for (j = 0; j < 4; j++)
                    block[i][j] = block3[i][j];

            break;

        case 4:
            for (i = 0; i < 4; i++)
                for (j = 0; j < 4; j++)
                    block[i][j] = block4[i][j];

            break;

        case 5:
            for (i = 0; i < 4; i++)
                for (j = 0; j < 4; j++)
                    block[i][j] = block5[i][j];

            break;

        case 6:
            for (i = 0; i < 4; i++)
                for (j = 0; j < 4; j++)
                    block[i][j] = block6[i][j];

            break;

        default:
            ;
    }

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            tem[i][j] = block[i][j];
        }
    }

    switch (rand() % 4)//再設置隨機旋轉的方向
    {
        case 0:
            break;

        case 1:
            for (i = 0; i < 4; i++)//順時針90度
            {
                for (j = 0; j < 4; j++)
                {
                    block[j][3 - i] = tem[i][j];
                }
            }

            break;

        case 2:
            for (i = 0; i < 4; i++)//順180度
            {
                for (j = 0; j < 4; j++)
                {
                    block[3 - i][3 - j] = tem[i][j];
                }
            }

            break;

        case 3:
            for (i = 0; i < 4; i++)//順270度
            {
                for (j = 0; j < 4; j++)
                {
                    block[3 - j][i] = tem[i][j];
                }
            }

            break;

        default:
            ;
    }

    ri++;

    if (ri == 7)
    {
        for (int i = 0; i < 7; i++)
        {
            randomm[i] = 0;
        }

        ri = 0;
    }
}

void CGameMap2::clear()
{
    int i = 0, j = 0, k = 0, i2 = 0, j2 = 0, checkline = 0;

    if (x == 20)
    {
        x = x - 1;
    }

    for (int i = 22; i >= 0; i--)
    {
        for (int j = 0; j < 10; j++)
        {
            if (map[i][j] == 0)
            {
                break;
            }

            k++;
        }

        if (k == 10)
        {
            for (int i2 = i; 0 < i2; i2--)
            {
                for (int j = 0; j < 10; j++)
                {
                    map[i2][j] = map[i2 - 1][j];
                }
            }

            i = i + 1;
            checkline++;
        }

        k = 0;
    }

    switch (checkline)
    {
	case 0:
		combo = 0;
		break;

	case 1:
		combo++;
		point += 40;
		point += 40 * (combo - 1) * 4;
		break;

	case 2:
		combo++;
		point += 100;
		point += 100 * (combo - 1) * 3;
		break;

	case 3:
		combo++;
		point += 300;
		point += 300 * (combo - 1) * 2;
		break;

	case 4:
		combo++;
		point += 1200 * combo;
		break;

        default:
            break;
    }
}

ShowNext2::ShowNext2()
    : X(886), Y(74), MW(30), MH(30)
{
    int map_init[4][4] = { { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    };

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            map[j][i] = map_init[i][j];
        }
    }
}
void ShowNext2::LoadBitmap()
{
    //back.LoadBitmap(IDB_cube_black));
    back.LoadBitmap(IDB_GRAY1);
    //gray2.LoadBitmap(IDB_gray2);
    blue.LoadBitmap(IDB_BLOCKBLUE);
    green.LoadBitmap(IDB_BLOCKGREEN);
    lightblue.LoadBitmap(IDB_BLOCKLIGHTBLUE);
    orange.LoadBitmap(IDB_BLOCKORANGE);
    purple.LoadBitmap(IDB_BLOCKPURPLE);
    red.LoadBitmap(IDB_BLOCKRED);
    yellow.LoadBitmap(IDB_BLOCKYELLOW);
}
void ShowNext2::OnShow()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            switch (map[j][i])
            {
                case 0:
                    //back.SetTopLeft(X + (MW*i), Y + (MH*j));
                    //back.ShowBitmap();
                    break;

                case 1:
                    back.SetTopLeft(X + (MW * i), Y + (MH * j));
                    back.ShowBitmap();
                    break;

                case 2:
                    back.SetTopLeft(X + (MW * i), Y + (MH * j));
                    back.ShowBitmap();
                    break;

                case 3:
                    blue.SetTopLeft(X + (MW * i), Y + (MH * j));
                    blue.ShowBitmap();
                    break;

                case 4:
                    green.SetTopLeft(X + (MW * i), Y + (MH * j));
                    green.ShowBitmap();
                    break;

                case 5:
                    lightblue.SetTopLeft(X + (MW * i), Y + (MH * j));
                    lightblue.ShowBitmap();
                    break;

                case 6:
                    orange.SetTopLeft(X + (MW * i), Y + (MH * j));
                    orange.ShowBitmap();
                    break;

                case 7:
                    purple.SetTopLeft(X + (MW * i), Y + (MH * j));
                    purple.ShowBitmap();
                    break;

                case 8:
                    red.SetTopLeft(X + (MW * i), Y + (MH * j));
                    red.ShowBitmap();
                    break;

                case 9:
                    yellow.SetTopLeft(X + (MW * i), Y + (MH * j));
                    yellow.ShowBitmap();
                    break;

                default:
                    ASSERT(0);
            }
        }
    }
}
void ShowNext2::OnMove(CGameMap2& gamemap2)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            map[j][i] = gamemap2.block[i][j];
        }
    }
}
Score2::Score2()
    : X(902), Y(480), MW(14), MH(28)
{
    int map_init[1][6] = { { 0, 0, 0, 0, 0, 0 } };

    for (int i = 0; i < 6; i++)
    {
        map[0][i] = map_init[0][i];
    }
}
void Score2::LoadBitmap()
{
    //zero.LoadBitmap(IDB_0,RGB(0,0,0));
    zero.LoadBitmap(IDB_0);
    one.LoadBitmap(IDB_1);
    two.LoadBitmap(IDB_2);
    three.LoadBitmap(IDB_3);
    four.LoadBitmap(IDB_4);
    five.LoadBitmap(IDB_5);
    six.LoadBitmap(IDB_6);
    seven.LoadBitmap(IDB_7);
    eight.LoadBitmap(IDB_8);
    nine.LoadBitmap(IDB_9);
}
void Score2::OnShow()
{
    for (int i = 0; i < 6; i++)
    {
        switch (map[0][i])
        {
            case 0:
                zero.SetTopLeft(X + (MW * i), Y + (MH * 0));
                zero.ShowBitmap();
                break;

            case 1:
                one.SetTopLeft(X + (MW * i), Y + (MH * 0));
                one.ShowBitmap();
                break;

            case 2:
                two.SetTopLeft(X + (MW * i), Y + (MH * 0));
                two.ShowBitmap();
                break;

            case 3:
                three.SetTopLeft(X + (MW * i), Y + (MH * 0));
                three.ShowBitmap();
                break;

            case 4:
                four.SetTopLeft(X + (MW * i), Y + (MH * 0));
                four.ShowBitmap();
                break;

            case 5:
                five.SetTopLeft(X + (MW * i), Y + (MH * 0));
                five.ShowBitmap();
                break;

            case 6:
                six.SetTopLeft(X + (MW * i), Y + (MH * 0));
                six.ShowBitmap();
                break;

            case 7:
                seven.SetTopLeft(X + (MW * i), Y + (MH * 0));
                seven.ShowBitmap();
                break;

            case 8:
                eight.SetTopLeft(X + (MW * i), Y + (MH * 0));
                eight.ShowBitmap();
                break;

            case 9:
                nine.SetTopLeft(X + (MW * i), Y + (MH * 0));
                nine.ShowBitmap();
                break;

            default:
                ASSERT(0);
        }
    }
}
void Score2::OnMove(CGameMap2& gamemap2)
{
    score = gamemap2.point;

    for (int i = 5; i >= 0; i--)
    {
        map[0][i] = score % 10;
        score /= 10;
    }
}
Hold2::Hold2()
    : X(886), Y(264), MW(30), MH(30)
{
    int map_init[4][4] = { { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    };

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            map[j][i] = map_init[i][j];
        }
    }
}
void Hold2::LoadBitmap()
{
    back.LoadBitmap(IDB_GRAY1);
    //gray2.LoadBitmap(IDB_gray2);
    blue.LoadBitmap(IDB_BLOCKBLUE);
    green.LoadBitmap(IDB_BLOCKGREEN);
    lightblue.LoadBitmap(IDB_BLOCKLIGHTBLUE);
    orange.LoadBitmap(IDB_BLOCKORANGE);
    purple.LoadBitmap(IDB_BLOCKPURPLE);
    red.LoadBitmap(IDB_BLOCKRED);
    yellow.LoadBitmap(IDB_BLOCKYELLOW);
}
void Hold2::OnShow()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            switch (map[j][i])
            {
                case 0:
                    //back.SetTopLeft(X + (MW*i), Y + (MH*j));
                    //back.ShowBitmap();
                    break;

                case 1:
                    back.SetTopLeft(X + (MW * i), Y + (MH * j));
                    back.ShowBitmap();
                    break;

                case 2:
                    back.SetTopLeft(X + (MW * i), Y + (MH * j));
                    back.ShowBitmap();
                    break;

                case 3:
                    blue.SetTopLeft(X + (MW * i), Y + (MH * j));
                    blue.ShowBitmap();
                    break;

                case 4:
                    green.SetTopLeft(X + (MW * i), Y + (MH * j));
                    green.ShowBitmap();
                    break;

                case 5:
                    lightblue.SetTopLeft(X + (MW * i), Y + (MH * j));
                    lightblue.ShowBitmap();
                    break;

                case 6:
                    orange.SetTopLeft(X + (MW * i), Y + (MH * j));
                    orange.ShowBitmap();
                    break;

                case 7:
                    purple.SetTopLeft(X + (MW * i), Y + (MH * j));
                    purple.ShowBitmap();
                    break;

                case 8:
                    red.SetTopLeft(X + (MW * i), Y + (MH * j));
                    red.ShowBitmap();
                    break;

                case 9:
                    yellow.SetTopLeft(X + (MW * i), Y + (MH * j));
                    yellow.ShowBitmap();
                    break;

                default:
                    ASSERT(0);
            }
        }
    }
}
void Hold2::OnMove(CGameMap2& gamemap2)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            map[j][i] = gamemap2.holdBlock[i][j];
        }
    }
}
}