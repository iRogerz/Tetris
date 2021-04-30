/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include <time.h>
#include<stdlib.h>
#include<Windows.h>

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame* g)
    : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
    //
    // 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
    //     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
    //
    ShowInitProgress(0);	// 一開始的loading進度為0%
    //
    // 開始載入資料
    //
    logo.LoadBitmap(IDB_Start);
    keyboard.LoadBitmap(IDB_KEYBOARD);
	instruction.LoadBitmap(IDB_instruction);
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
    //
    // 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
    //
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_ESC = 27;
    const char KEY_SPACE = ' ';

    if (nChar == KEY_SPACE)
        GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
    else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
        PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
    //GetCursorPos(&aPos);
    if (point.x > 310 && point.x < 610)
    {
        if (point.y > 300 && point.y < 400)
        {
            GotoGameState(GAME_STATE_RUN);
        }
        else if (point.y > 450 && point.y < 600)
        {
			IfInstruction = true;
        }
        else if (point.y > 580 && point.y < 680)
        {
            PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
        }
    }
	if (point.x > 824 && point.x < 1024)
	{
		if (point.y > 0 && point.y < 100)
		{
			if (IfInstruction == true)
			{
				IfInstruction = false;
				IfKeyboard = true;
			}

		}
	} 
    if (point.x > 0 && point.x < 200)
    {
        if (point.y > 0 && point.y < 100)
        {
			if (IfInstruction == false && IfKeyboard == true)
			{
				IfInstruction = true;
				IfKeyboard = false;
			}
			else
			{
				IfInstruction = false;
			}       
        }
    }

    // 切換至GAME_STATE_RUN
}


void CGameStateInit::OnShow()
{
    //
    // 貼上logo
    //
    //logo.SetTopLeft((SIZE_X - logo.Width()) / 2, SIZE_Y / 8);
    logo.SetTopLeft(0, 0);
    logo.ShowBitmap();

    if (IfKeyboard)
    {
        keyboard.SetTopLeft(0, 0);
        keyboard.ShowBitmap();
    }
	if (IfInstruction)
	{
		instruction.SetTopLeft(0, 0);
		instruction.ShowBitmap();
	}

    //
    // Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
    //
    /*CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
    fp = pDC->SelectObject(&f);					// 選用 font f
    pDC->SetBkColor(RGB(0, 0, 0));
    pDC->SetTextColor(RGB(255, 255, 0));
    pDC->TextOut(120, 220, "Please click mouse or press SPACE to begin.");
    pDC->TextOut(5, 395, "Press Ctrl-F to switch in between window mode and full screen mode.");
    if (ENABLE_GAME_PAUSE)
    	pDC->TextOut(5, 425, "Press Ctrl-Q to pause the Game.");
    pDC->TextOut(5, 455, "Press Alt-F4 or ESC to Quit.");
    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC*/
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame* g)
    : CGameState(g)
{
}
void CGameStateOver::OnMove()
{
    counter--;

    if (counter < 0)
    {
        GotoGameState(GAME_STATE_INIT);
    }
}

void CGameStateOver::OnBeginState()
{
    counter = 30 * 3; // 3 seconds
}

void CGameStateOver::OnInit()
{
    //
    // 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
    //     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
    //
    ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
    //
    // 開始載入資料
    //
    Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
    //
    // 最終進度為100%
    //
    ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
    CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
    fp = pDC->SelectObject(&f);					// 選用 font f
    pDC->SetBkColor(RGB(0, 0, 0));
    pDC->SetTextColor(RGB(255, 255, 0));
    char str[80];								// Demo 數字對字串的轉換
    sprintf(str, "Game is over~ back to the main screen ^_^ (%d)", counter / 30 + 1);
    pDC->TextOut(240, 210, str);
    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////
CGameStateRun::CGameStateRun(CGame* g)
    : CGameState(g), NUMBALLS(28)
{
    picX = picY = 0;
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
    CAudio::Instance()->Play(AUDIO_LAKE, true);			// 撥放 WAVE
    CAudio::Instance()->Play(AUDIO_DING, false);		// 撥放 WAVE
    CAudio::Instance()->Play(AUDIO_NTUT, true);			// 撥放 MIDI

    for (int i = 0; i < 23; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            gamemap.map[i][j] = 0;
        }
    }

    for (int i = 0; i < 23; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            gamemap2.map[i][j] = 0;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            shownext.map[i][j] = 0;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            shownext2.map[i][j] = 0;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            hold.map[i][j] = 0;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            hold2.map[i][j] = 0;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gamemap.BLOCK[i][j] = 0;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gamemap2.BLOCK[i][j] = 0;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gamemap.block[i][j] = 0;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gamemap2.block[i][j] = 0;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gamemap.holdBlock[i][j] = 0;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gamemap2.holdBlock[i][j] = 0;
        }
    }

    gamemap.start = 0;
    gamemap2.start = 0;
    gamemap.point = 0;
    gamemap2.point = 0;
    gamemap.x = 0;
    gamemap.y = 3;
    gamemap2.x = 0;
    gamemap2.y = 3;
    gamemap.GameOverCheck = false;
    gamemap2.GameOverCheck = false;
    gamemap.check = true;
    gamemap.precheck = false;
    gamemap.switchz = true;
    gamemap2.check = true;
    gamemap2.precheck = false;
    gamemap2.switchz = true;
    gamemap.randomm[0] = 0;
    gamemap.ri = 0;
    gamemap2.randomm[0] = 0;
    gamemap2.ri = 0;
	gamemap.combo = 0;
	gamemap2.combo = 0;
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
    //
    // 如果希望修改cursor的樣式，則將下面程式的commment取消即可
    //
    // SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
    //
    // 移動背景圖的座標
    //
    int checkline = 0;
    background.SetTopLeft(0, 0);
    gamemap.OnMove();
    gamemap2.OnMove();
    backgroundcut.SetTopLeft(192, 0);

	
	

    if (gamemap.point > gamemap2.point)
    {
        counter2++;

        if (counter2 % 90 == 0)
        {
            for (int  i = 4; i < 23; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    gamemap2.map[i - 1][j] = gamemap2.map[i][j];
                }
            }

            for (int i = 0; i < 10; i++)
            {
                gamemap2.map[22][i] = 2;
            }

            gamemap2.map[22][rand() % 9] = 0;
            gamemap2.x--;
        }
    }

    if (gamemap.point < gamemap2.point)
    {
        counter2++;

        if (counter2 % 90 == 0)
        {
            for (int i = 4; i < 23; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    gamemap.map[i - 1][j] = gamemap.map[i][j];
                }
            }

            for (int i = 0; i < 10; i++)
            {
                gamemap.map[22][i] = 2;
            }

            gamemap.map[22][rand() % 9] = 0;
            gamemap.x--;
        }
    }

    if (gamemap.GameOverCheck == false)
    {
        if (gamemap.check)
        {
            if (gamemap.start > 0)
            {
                if (gamemap.map[3][4] != 0 || gamemap.map[3][5] != 0 || gamemap.map[3][3] != 0 || gamemap.map[3][6] != 0)
                {
                    if (gamemap.map[3][4] != 1 || gamemap.map[3][5] != 1 || gamemap.map[3][3] != 1 || gamemap.map[3][6] != 1)
                    {
                        for (int i = 22; i >= 0; i--)
                        {
                            if (gamemap.map[i][0] == 2 || gamemap.map[i][1] == 2)
                            {
                                for (int i2 = i; 0 < i2; i2--)
                                {
                                    for (int j = 0; j < 10; j++)
                                    {
                                        gamemap.map[i2][j] = gamemap.map[i2 - 1][j];
                                    }
                                }

                                i = i + 1;
                                checkline++;
                            }
                        }

                        if (checkline > 0)
                        {
                            gamemap2.point += checkline * 200;
                            checkline = 0;
                        }
                        else
                        {
                            gamemap.GameOverCheck = true;

                            for (int i = 0; i < 23; i++)
                            {
                                for (int j = 0; j < 10; j++)
                                {
                                    gamemap.map[i][j] = 2;
                                }
                            }
                        }

                        gamemap.x = 0;   //陣列位置X軸
                        gamemap.y = 3;   //陣列位置Y軸
                    }
                }
            }
        }
    }

    if (gamemap2.GameOverCheck == false)
    {
        if (gamemap2.check)
        {
            if (gamemap2.start > 0)
            {
                if (gamemap2.map[3][4] != 0 || gamemap2.map[3][5] != 0 || gamemap2.map[3][3] != 0 || gamemap2.map[3][6] != 0)
                {
                    if (gamemap2.map[3][4] != 1 || gamemap2.map[3][5] != 1 || gamemap2.map[3][3] != 1 || gamemap2.map[3][6] != 1)
                    {
                        for (int i = 22; i >= 0; i--)
                        {
                            if (gamemap2.map[i][0] == 2 || gamemap2.map[i][1] == 2)
                            {
                                for (int i2 = i; 0 < i2; i2--)
                                {
                                    for (int j = 0; j < 10; j++)
                                    {
                                        gamemap2.map[i2][j] = gamemap2.map[i2 - 1][j];
                                    }
                                }

                                i = i + 1;
                                checkline++;
                            }
                        }

                        if (checkline > 0)
                        {
                            gamemap.point += checkline * 200;
                            checkline = 0;
                        }
                        else
                        {
                            gamemap2.GameOverCheck = true;

                            for (int i = 0; i < 23; i++)
                            {
                                for (int j = 0; j < 10; j++)
                                {
                                    gamemap2.map[i][j] = 2;
                                }
                            }
                        }

                        gamemap2.x = 0;   //陣列位置X軸
                        gamemap2.y = 3;   //陣列位置Y軸
                    }
                }
            }
        }
    }

    if (gamemap.GameOverCheck && gamemap.point < gamemap2.point)
    {
        gamemap2.GameOverCheck = true;
    }
    else if (gamemap2.GameOverCheck && gamemap.point > gamemap2.point)
    {
        gamemap.GameOverCheck = true;
    }

    shownext.OnMove(gamemap);
    score.OnMove(gamemap);
    hold.OnMove(gamemap);
    shownext2.OnMove(gamemap2);
    score2.OnMove(gamemap2);
    hold2.OnMove(gamemap2);
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
    //
    // 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
    //     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
    //
    gamemap.LoadBitmap();
    gamemap2.LoadBitmap();
    shownext.LoadBitmap();
    score.LoadBitmap();
    hold.LoadBitmap();
    shownext2.LoadBitmap();
    score2.LoadBitmap();
    hold2.LoadBitmap();
    background.LoadBitmap(IDB_BK2);					// 載入背景的圖形
    backgroundcut.LoadBitmap(IDB_bgcut);
    player1win.LoadBitmap(IDB_p1win);
    player2win.LoadBitmap(IDB_p2win);
	tie.LoadBitmap(IDB_tie);
    combo1.LoadBitmap(IDB_combo1, RGB(0, 0, 0));
	combo2.LoadBitmap(IDB_combo2, RGB(0, 0, 0));
	combo3.LoadBitmap(IDB_combo3, RGB(0, 0, 0));
	combo4.LoadBitmap(IDB_combo4, RGB(0, 0, 0));
	combo5.LoadBitmap(IDB_combo5, RGB(0, 0, 0));
	combo6.LoadBitmap(IDB_combo6, RGB(0, 0, 0));
	combo7.LoadBitmap(IDB_combo7, RGB(0, 0, 0));
	combo8.LoadBitmap(IDB_combo8, RGB(0, 0, 0));
	combo9.LoadBitmap(IDB_combo9, RGB(0, 0, 0));
	combo10.LoadBitmap(IDB_combo10, RGB(0, 0, 0));
	combo11.LoadBitmap(IDB_combo11, RGB(0, 0, 0));
	combo12.LoadBitmap(IDB_combo12, RGB(0, 0, 0));
    ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
    //
    // 開始載入資料
    //
    Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
    //
    // 繼續載入其他資料
    CAudio::Instance()->Load(AUDIO_DING, "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
    CAudio::Instance()->Load(AUDIO_LAKE, "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
    CAudio::Instance()->Load(AUDIO_NTUT, "sounds\\main.mp3");	// 載入編號2的聲音main.mp3
    //
    // 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
    //
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT = 0x25; // keyboard左箭頭
    const char KEY_UP = 0x26; // keyboard上箭頭
    const char KEY_RIGHT = 0x27; // keyboard右箭頭
    const char KEY_DOWN = 0x28; // keyboard下箭頭
    const char LEFT = 0x43; // keyboard左箭頭
    const char UP = 0x46; // keyboard上箭頭
    const char RIGHT = 0x42; // keyboard右箭頭
    const char DOWN = 0x56; // keyboard下箭頭
    const char W = 0x57;
    const char Q = 0x51;
    const char LEFT2 = 0x61; // keyboard左箭頭
    const char UP2 = 0x65; // keyboard上箭頭
    const char RIGHT2 = 0x63; // keyboard右箭頭
    const char DOWN2 = 0x62; // keyboard下箭頭
    const char P = 0x50;
    const char O = 0x4F;
	const char KEY_ESC = 27;

	if (nChar == KEY_ESC)
		GotoGameState(GAME_STATE_OVER);
    gamemap.OnKeyDown(nChar);
    gamemap2.OnKeyDown(nChar);
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT = 0x25; // keyboard左箭頭
    const char KEY_UP = 0x26; // keyboard上箭頭
    const char KEY_RIGHT = 0x27; // keyboard右箭頭
    const char KEY_DOWN = 0x28; // keyboard下箭頭
    const char LEFT = 0x43; // keyboard左箭頭
    const char UP = 0x46; // keyboard上箭頭
    const char RIGHT = 0x42; // keyboard右箭頭
    const char DOWN = 0x56; // keyboard下箭頭
    const char W = 0x57;
    const char Q = 0x51;
    const char LEFT2 = 0x61; // keyboard左箭頭
    const char UP2 = 0x65; // keyboard上箭頭
    const char RIGHT2 = 0x63; // keyboard右箭頭
    const char DOWN2 = 0x62; // keyboard下箭頭
    const char P = 0x50;
    const char O = 0x4F;
    /*if (nChar == KEY_LEFT)
    	eraser.SetMovingLeft(false);
    if (nChar == KEY_RIGHT)
    	eraser.SetMovingRight(false);
    if (nChar == KEY_UP)
    	eraser.SetMovingUp(false);
    if (nChar == KEY_DOWN)
    	eraser.SetMovingDown(false);*/
    gamemap.OnKeyUp(nChar);
    gamemap2.OnKeyUp(nChar);
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
    if (gamemap.GameOverCheck == true && gamemap2.GameOverCheck == true)
    {
        GotoGameState(GAME_STATE_OVER);
    }
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
    // 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
    //
    //  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
    //        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
    //        說，Move負責MVC中的Model，Show負責View，而View不應更動Model  。
    //
    //
    //  貼上背景圖、撞擊數、球、擦子、彈跳的球
    //
    background.ShowBitmap();// 貼上背景圖
    gamemap.OnShow();
    gamemap2.OnShow();
    shownext.OnShow();
    score.OnShow();
    hold.OnShow();
    shownext2.OnShow();
    score2.OnShow();
    hold2.OnShow();
    backgroundcut.ShowBitmap();
		
    if (gamemap.combo == 1)
    {
		combo1.SetTopLeft(248, 200);
        combo1.ShowBitmap();
    }
	else if (gamemap.combo == 2)
	{
		combo2.SetTopLeft(248, 200);
		combo2.ShowBitmap();
	}
	else if (gamemap.combo == 3)
	{
		combo3.SetTopLeft(248, 200);
		combo3.ShowBitmap();
	}
	else if (gamemap.combo == 4)
	{
		combo4.SetTopLeft(248, 200);
		combo4.ShowBitmap();
	}
	else if (gamemap.combo == 5)
	{
		combo5.SetTopLeft(248, 200);
		combo5.ShowBitmap();
	}
	else if (gamemap.combo == 6)
	{
		combo6.SetTopLeft(248, 200);
		combo6.ShowBitmap();
	}
	else if (gamemap.combo == 7)
	{
		combo7.SetTopLeft(248, 200);
		combo7.ShowBitmap();
	}
	else if (gamemap.combo == 8)
	{
		combo8.SetTopLeft(248, 200);
		combo8.ShowBitmap();
	}
	else if (gamemap.combo == 9)
	{
		combo9.SetTopLeft(248, 200);
		combo9.ShowBitmap();
	}
	else if (gamemap.combo == 10)
	{
		combo10.SetTopLeft(248, 200);
		combo10.ShowBitmap();
	}
	else if (gamemap.combo == 11)
	{
		combo11.SetTopLeft(248, 200);
		combo11.ShowBitmap();
	}
	else if (gamemap.combo == 12)
	{
		combo12.SetTopLeft(248, 200);
		combo12.ShowBitmap();
	}


	if (gamemap2.combo == 1)
	{
		combo1.SetTopLeft(598, 200);
		combo1.ShowBitmap();
	}
	else if (gamemap2.combo == 2)
	{
		combo2.SetTopLeft(598, 200);
		combo2.ShowBitmap();
	}
	else if (gamemap2.combo == 3)
	{
		combo3.SetTopLeft(598, 200);
		combo3.ShowBitmap();
	}
	else if (gamemap2.combo == 4)
	{
		combo4.SetTopLeft(598, 200);
		combo4.ShowBitmap();
	}
	else if (gamemap2.combo == 5)
	{
		combo5.SetTopLeft(598, 200);
		combo5.ShowBitmap();
	}
	else if (gamemap2.combo == 6)
	{
		combo6.SetTopLeft(598, 200);
		combo6.ShowBitmap();
	}
	else if (gamemap2.combo == 7)
	{
		combo7.SetTopLeft(598, 200);
		combo7.ShowBitmap();
	}
	else if (gamemap2.combo == 8)
	{
		combo8.SetTopLeft(598, 200);
		combo8.ShowBitmap();
	}
	else if (gamemap2.combo == 9)
	{
		combo9.SetTopLeft(598, 200);
		combo9.ShowBitmap();
	}
	else if (gamemap2.combo == 10)
	{
		combo10.SetTopLeft(598, 200);
		combo10.ShowBitmap();
	}
	else if (gamemap2.combo == 11)
	{
		combo11.SetTopLeft(598, 200);
		combo11.ShowBitmap();
	}
	else if (gamemap2.combo == 12)
	{
		combo12.SetTopLeft(598, 200);
		combo12.ShowBitmap();
	}

    if (gamemap.GameOverCheck == true  && gamemap2.GameOverCheck == true)
    {
        if (gamemap.point > gamemap2.point)
        {
            player1win.ShowBitmap();
        }
        else if (gamemap.point < gamemap2.point)
        {
            player2win.ShowBitmap();
        }
		else
		{
			tie.ShowBitmap();
		}
    }
}


}