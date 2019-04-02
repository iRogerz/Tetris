

#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap logo;								// csie的logo
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////
	class CGameMap
	{
	public:
		CGameMap();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void GetY();
		void gotoxy(int x,int y);
		int map[20][10];
		bool check = false;
		int block0[4][4] = { { 0,3,3,0 },{ 0,0,3,0 },{ 0,0,3,0 },{ 0,0,0,0 } };// 7 個方塊 用數組表示 正「7」
		int block1[4][4] = { { 0,4,4,0 },{ 0,4,0,0 },{ 0,4,0,0 },{ 0,0,0,0 } };// 反「7」
		int block2[4][4] = { { 0,0,0,0 },{ 0,0,5,5 },{ 0,5,5,0 },{ 0,0,0,0 } };// 反「z」
		int block3[4][4] = { { 0,0,0,0 },{ 6,6,0,0 },{ 0,6,6,0 },{ 0,0,0,0 } };// 正「z」
		int block4[4][4] = { { 0,0,0,0 },{ 0,7,0,0 },{ 7,7,7,0 },{ 0,0,0,0 } };// 倒「T」
		int block5[4][4] = { { 0,0,0,0 },{ 0,8,8,0 },{ 0,8,8,0 },{ 0,0,0,0 } };// 正方形
		int block6[4][4] = { { 0,0,0,0 },{ 0,0,0,0 },{ 9,9,9,9 },{ 0,0,0,0 } };// 直條
		int BLOCK[4][4];//正在下落的方塊
		int block[4][4];//提示區的方塊
		int tem[4][4];//用4*4的方格來控制方塊的操作和顯示
		int scope[25][34] = { 0 };//操作的範圍 這裡要注意，一個方格是占兩個橫坐標單位的
		void OnKeyDown(UINT);
		void random();
		void clear();
	protected:
		CMovingBitmap gray1, gray2,blue,green,lightblue,orange,purple,red,yellow;
		int x=0, y=4;
		const int X, Y;
		const int MW, MH;
	};
	class CGameMap2
	{
	public:
		CGameMap2();
		void LoadBitmap();
		void OnShow();
	protected:
		CMovingBitmap gray10, gray20;
		int map[20][10];
		const int X, Y;
		const int MW, MH;
	};
	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);    // 處理滑鼠的動作
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CGameMap  gamemap;
		CGameMap2 gamemap2;
		const int		NUMBALLS;	// 球的總數
		CMovingBitmap   practice;
		int picX, picY;
		CMovingBitmap	background;	// 背景圖
		CMovingBitmap	help;		// 說明圖
		CBall			*ball;		// 球的陣列
		CMovingBitmap	corner;		// 角落圖
		CMovingBitmap	corner2;	// 角落圖
		CEraser			eraser;		// 拍子
		CInteger		hits_left;	// 剩下的撞擊數
		CBouncingBall   bball;		// 反覆彈跳的球
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
	};

}